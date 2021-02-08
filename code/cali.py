import cv2
import numpy as np
import matplotlib.pyplot
import matplotlib.image

#Distance focale	4.0 mm

#criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# cap = cv2.VideoCapture(0)
i=0
img1=matplotlib.pyplot.imread("image_rot.png")
img1=(img1 * 255).astype(np.uint8)
detect, chess = cv2.findChessboardCorners(img1, (7, 7))
print(chess)
img2=matplotlib.pyplot.imread("chess15cm.png")
img2=(img2 * 255).astype(np.uint8)
detect, chess2 = cv2.findChessboardCorners(img2, (7, 7))
print(chess2[:,0][:2,:2])
# write_name = 'corners_found'+str(idx)+'.jpg'
# cv2.imwrite(write_name, img)
cv2.imshow('img2', img2)
chess=np.concatenate((chess,chess2),axis=0)
#sens : haut a droite vers bas gauche par colonne
print(chess)

coord_mm=np.zeros((7*7*2,2))


k=0
N=49+49
while k<N:
    for i in range(8,1,-1):
        for j in range(1,8):
            coord_mm[k]=(i*2,j*2)
            k+=1
h,l=160,160

print(chess)#[:,0][:,0])
x1=coord_mm[:,0]*10.0

x2=coord_mm[:,1]*10.0
x3=np.concatenate((np.zeros((49,1)),15*np.ones((49,1))*10.0),axis=0)

u1=chess[:,0][:,0]-h/2
u2=chess[:,0][:,1]-l/2
A=np.zeros((N,7))
A[:,0]=np.multiply(u2,x1)
A[:,1]=np.multiply(u2,x2)
A[:,2] = np.multiply(u2,x3[:,0])
A[:,3]=u2
A[:,4]=-np.multiply(u1,x1)
A[:,5]=-np.multiply(u1,x2)
A[:,6]=-np.multiply(u1,x3[:,0])
L=np.dot(np.linalg.pinv(A),u1)
o2c=abs(1/np.sqrt(pow(L[4],2.0)+pow(L[5],2.0)+pow(L[6],2.0)))
print(o2c)

#o2c de signe negatif (selon la rotation)
beta=abs(o2c)*np.sqrt(pow(L[0],2.0)+pow(L[1],2.0)+pow(L[2],2.0))

o1c=L[3]*o2c/beta
r=np.zeros((3,3))
r[0,0]=L[0]*o2c/beta
r[0,1]=L[1]*o2c/beta
r[0,2]=L[2]*o2c/beta
r[1,0]=L[4]*o2c
r[1, 1] = L[5] * o2c
r[1, 2] = L[6] * o2c
r[2,0]=np.sqrt(1-pow(r[0,0],2.0)-pow(r[1,0],2.0))
r[2,1]=np.sqrt(1-pow(r[0,1],2.0)-pow(r[1,1],2.0))
r[2,2]=np.sqrt(1-pow(r[0,2],2.0)-pow(r[1,2],2.0))







print(r)

phi=-np.arctan(r[1,2]/r[2,2])
gamma=-np.arctan(r[0,1]/r[0,0])
omega=-np.arctan(r[0,2]/(-r[1,2]*np.sin(phi)+r[2,2]*np.cos(phi)))
print("angle")
B=np.zeros((N,2))
B[:,0]=u2
B[:, 1]=-(r[1,0]*x1+r[1,1]*x2+r[1,2]*x3[:,0]+o2c)
print(B)


R=-u2*(r[2,0]*x1+r[2,1]*x2+r[2,2]*x3[:,0])
R = np.reshape(R,(-1,1))

mat_finale = np.dot(np.linalg.pinv(B),R) # oc3 = 20 cm et f2 = 600 mm donc s2 = 0.006 mm / pixel

o3c = mat_finale[0]

f1 = np.mean(u1)*(r[2,0]*np.mean(x1)+r[2,1]*np.mean(x2)+r[2,2]*np.mean(x3)+o3c)/(r[0,0]*np.mean(x1)+r[0,1]*np.mean(x2)+r[0,2]*np.mean(x3)+o1c)
f2 = mat_finale[1]
print(f1)

s2 = 4/f2
s1 = 4/f1

size_capteurx = s1 * 1280
size_capteury = s2*720

print(size_capteurx)
print(size_capteury)

print(mat_finale)

#np.linalg.pinv()

#  corners2 = cv2.cornerSubPix(gray, chess, (11, 11), (-1, -1), criteria)

# Draw and display the corners
# img = cv2.drawChessboardCorners(gray, (7, 7), corners2, ret)
