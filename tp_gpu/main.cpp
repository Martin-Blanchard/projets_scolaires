#include <iostream>
#include <fstream>
#include <chrono>


#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "glhelper.h"
#include "mesh.h"
#include "camera.h"

#define TINYOBJLOADER_IMPLEMENTATION 
#include "external/tiny_obj_loader.h"

// main obj
GLuint program_id;
GLuint program_id2;
GLuint program_id3;
GLuint VAO;
GLuint tbo;
GLuint VAO_2;
GLuint n_elements;
GLuint n_elements2;
GLuint texture_id;
GLuint texture_id2;
GLuint frame_id;
GLuint renderbuffer;
GLuint m_vboID;

const GLchar* feedbackVaryings[] = { "outValue" };


// camera
Camera cam;

GLuint time_id;
std::chrono::high_resolution_clock::time_point t_start;

void init()
{
  // create main obj
  {
    std::cout << "Creation of main object" << std::endl; 

    //Creation de l'eau (programme)
    program_id = glhelper::create_program_from_file("shaders/simple.vs", "shaders/simple.fs");
    Mesh m = Mesh::create_grid(10);
    n_elements = m.size_element();
    VAO = m.load_to_gpu();
    texture_id = glhelper::load_texture("data/water-normal.png");


    // Creation TF

    // glTransformFeedbackVaryings(program_id2, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);


    //Creation Frankie programme
    program_id2 = glhelper::create_program_from_file("shaders/simple2.vs", "shaders/simple2.fs");

    // Creation frankie
    Mesh m2 = Mesh::load_from_file("data/Frankie/Frankie3.obj");
    m2.apply_matrix(glm::mat4(
          1., 0., 0., 0.,
          0., 1., 0., 0.,
          0., 0., 1., 0.,
          0., 0., 0., 1.));
    n_elements2=m2.size_element();
    VAO_2 = m2.load_to_gpu();
    texture_id2 = glhelper::load_texture("data/Frankie/flyingsquirrel_skin_col.png");

    /*Creation FBO
    */

    // On genere le FBO
    glGenFramebuffers(1,&frame_id);

    // On binde le buffer à un type précis
    glBindFramebuffer(GL_FRAMEBUFFER,frame_id);

    // On genere le buffer
    glGenRenderbuffers(1,&renderbuffer);

    // On lie le buffer a notre contexte
    glBindRenderbuffer(GL_RENDERBUFFER,renderbuffer);

    // On lui alloue de l'espace
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT16,cam.height(),cam.width());

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,renderbuffer);

    /* Fin creation FBO
     */

    // Test TF
    const GLchar* feedbackVaryings[] = { "outValue" };
    glTransformFeedbackVaryings(program_id3, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
    program_id3 = glhelper::create_program_from_file("shaders/simple3.vs", "shaders/simple3.fs");
    glUseProgram(program_id3);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    // Creation VBO pour TF
    GLfloat data[] = {0.0f,1.0f,3.0f};
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(float), data, GL_STATIC_READ);

    GLint inputAttrib = glGetAttribLocation(program_id3, "inValue");
    glEnableVertexAttribArray(inputAttrib);
    glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);

    t_start = std::chrono::high_resolution_clock::now();
  }

  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glEnable(GL_DEPTH_TEST);            
}

static void display_callback()
{
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  glm::mat4 mvp = cam.projection() * cam.view();

  // display obj
  {

    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, 3);
    glEndTransformFeedback();
    glFlush();
    GLfloat feedback[3];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
    printf("%f %f %f\n", feedback[0], feedback[1], feedback[2]);
    glDisable(GL_RASTERIZER_DISCARD);

    glUseProgram(program_id);
    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now-t_start).count();
    time_id=glGetUniformLocation(program_id,"TIME");
    glUniform1f(time_id,time);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, cam.width(), cam.height());
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBindVertexArray(VAO);
    GLint mvp_id = glGetUniformLocation(program_id, "MVP");
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]); 
    glDrawElements(GL_TRIANGLES, n_elements, GL_UNSIGNED_INT, 0); 


    glUseProgram(program_id2);
    time_id=glGetUniformLocation(program_id2,"TIME");
    glUniform1f(time_id,time);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, cam.width(), cam.height());

    glBindTexture(GL_TEXTURE_2D, texture_id2);
    glBindVertexArray(VAO_2);
    mvp_id = glGetUniformLocation(program_id2, "MVP");
    glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
    glDrawElements(GL_TRIANGLES, n_elements2, GL_UNSIGNED_INT, 0);
  }

  glBindVertexArray(0);
  glutSwapBuffers ();
}

static void keyboard_callback(unsigned char key, int, int)
{
  switch (key)
  {
    case 'q':
    case 'Q':
    case 27:
      glhelper::save_fbo_image("fbo.ppm",cam.width(),cam.height());
      exit(0);
  }
  glutPostRedisplay();
}

static void reshape_callback(int width, int height)
{
  cam.common_reshape(width,height);

  glViewport(0,0, width, height); 
  glutPostRedisplay();
}


static void mouse_callback (int button, int action, int x, int y)
{
  cam.common_mouse(button, action, x, y);

  glutPostRedisplay();
}

static void motion_callback(int x, int y)
{
  cam.common_motion(x, y);
  glutPostRedisplay();
}

static void timer_callback(int)
{
  glutTimerFunc(25, timer_callback, 0);
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInitContextVersion(3, 3); 
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(cam.width(), cam.height());
  glutCreateWindow("opengl");
  glutDisplayFunc(display_callback);
  glutMotionFunc(motion_callback);
  glutMouseFunc(mouse_callback);
  glutKeyboardFunc(keyboard_callback);
  glutReshapeFunc(reshape_callback);
  glutTimerFunc(25, timer_callback, 0);

  glewExperimental=true;
  glewInit();

  init();
  glutMainLoop();

  return 0;
}
