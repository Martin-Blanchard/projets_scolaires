# -*- coding: utf-8 -*-
"""
Created on Mon Dec 12 13:21:52 2016

@author: martin.blanchard
"""
from Tkinter import *
import random
import time
  
def deplacement(event):
    global PosX,RAYON,PosY,alien,photo3,missile,photo4,MX,MY,fin
    touche=event.keysym
    if touche=='Right':
        if PosX<958:
            PosX+=10
    if touche=='Left':
        if PosX>28:
            PosX-=10
    if touche=='space':
        if fin==1:
            MX=PosX
            MY=PosY-40
            alien.itemconfig(missile,image=photo4)
            alien.coords(missile,MX,MY)
            fin=0
    alien.coords(vaisseau,PosX,PosY)

def probabilite_ufo():
    global bonus,existence
    if existence==1:
        return
    a=random.randint(0,200)
    if a==40:
        L=[0,1,5,10,20]
        bonus=L[random.randint(0,4)]
        ufo()

def proba_tir():
    global tirAl
    if tirAl==0:
        a=random.randint(0,30)
        if a==20:
            tir_Alien()

def tir_Alien():
    global X,Y,tirAl,bombe,Xnuk,Ynuk
    tirAl=1
    tireur=random.randint(0,len(X)-1)
    Xnuk=X[tireur]
    Ynuk=Y[tireur]+20
    bombe=alien.create_image(Xnuk,Ynuk,image=nuke)

def ufo():
    global existence,soucoupe,X_ufo,Y_ufo,souc
    existence=1
    X_ufo=956
    Y_ufo=31
    souc=alien.create_image(X_ufo,Y_ufo,image=soucoupe)
    
def vaisseau_special(event):
    global menu_2,k
    if menu_2==1:
        k=6
        play(k)
    
def jouer_LV1(): 
    global X,Y,level,DX,DY,recommencer,LARGEUR,HAUTEUR,photo,tirAl,Xnuk,Ynuk,MX,MY,fin,alien1,existence,X_ufo,Y_ufo,souc,perdu
    level=1
    if perdu==1:
        alien.after_cancel(recommencer)
        defaite()
        return
    colision()
    probabilite_ufo()
    proba_tir()
    if len(alien1)==0:
        fin_LV1()
    for k in range(0,len(alien1)):
        if Y[k]>430:
            perdre_vie()
            for k in range(0,len(alien1)):
                Y[k]-=80
                alien.coords(alien1[k],X[k],Y[k])
            time.sleep(2)
        if X[k]+DX >LARGEUR:
            X[k]=2*(LARGEUR)-X[k]
            DX=-DX
            for i in range(0,len(alien1)):
                Y[i]+=20
        if X[k]+DX<0:
            X[k]=-X[k]
            DX=-DX
            for i in range(0,len(alien1)):
                Y[i]+=20
        if Y[k]+DY >HAUTEUR:
            Y[k]=2*(HAUTEUR)-Y[k]
            DY=-DY
        if Y[k]+DY<0:
            Y[k]=-Y[k]
            DY=-DY
        X[k]=X[k]+DX
        alien.coords(alien1[k],X[k],Y[k])
    if MY<0:
        fin=1 
    MY=MY-3
    if existence==1:
        if X_ufo<0:
            existence=0
            alien.delete(souc)
        X_ufo-=2
        alien.coords(souc,X_ufo,Y_ufo)
    if tirAl==1:
        if Ynuk>455:
            tirAl=0
            alien.delete(bombe)
        Ynuk+=2
        alien.coords(bombe,Xnuk,Ynuk)
    alien.coords(missile,MX,MY)
    recommencer=alien.after(5,jouer_LV1)
    return

def fin_LV1():
    jouer_LV2()    
    
def jouer_LV2():
    return

def colision():
    global alien,MY,MX,DX,Y,X,photo3,missile,score,alien1,PosX,PosY,bonus,Xnuk,Ynuk,tirAl
    global Xab,Yab,abris
    for k in range(0,len(alien1)):
        if X[k]-25<MX<X[k]+20 and Y[k]-16<MY-10<Y[k]+16:
            MY-=1000
            alien.coords(missile,MX,MY)
            alien.delete(alien1[k])
            score+=1
            Score.config(text='Score ='+str(score))
            del alien1[k]
            del X[k]
            del Y[k]
            DX=DX*1.01
            return
        for i in range(0,len(abris)):
            if X[k]-15<Xab[i]<X[k]+15 and Y[k]-10<Yab[i]<Y[k]+10:
                alien.delete(abris[i])
                del abris[i]
                del Xab[i]
                del Yab[i]
                return
    if X_ufo-30<MX<X_ufo+30 and Y_ufo-16<MY-10<Y_ufo+16:
            MY-=1000
            alien.delete(souc)
            alien.coords(missile,MX,MY)
            score+=bonus
            Score.config(text='Score ='+str(score))
            return
    if PosX-20<Xnuk<PosX+20 and PosY-20<Ynuk<PosY+20:
            perdre_vie()
            time.sleep(2)
            tirAl=0
            Xnuk=-1000
            Ynuk=-1000
            alien.coords(bombe,Xnuk,Ynuk)
    for k in range(0,len(abris)):
        if Xab[k]-4<MX-12<Xab[k]+4 and Yab[k]-4<MY-10<Yab[k]+4:
            MY-=1000
            alien.coords(missile,MX,MY)
            alien.delete(abris[k])
            del abris[k]
            del Xab[k]
            del Yab[k]
            return
        if Xab[k]-4<Xnuk-8<Xab[k]+4 and Yab[k]-4<Ynuk-10<Yab[k]+4:
            MY-=1000
            tirAl=0
            Xnuk=-1000
            Ynuk=-1000
            alien.coords(bombe,Xnuk,Ynuk)
            alien.delete(abris[k])
            del abris[k]
            del Xab[k]
            del Yab[k]
            return
        
    return
    
def perdre_vie():
    global Live,vie,alien,perdu
    if vie==0:
        perdu=1
        return
    vie-=1
    Live.config(text='Vies ='+str(vie))
    return

def defaite():
    global alien,vaisseau,missile,alien1,abris,souc,bombe,tirAl,existence,perdu
    alien.delete(vaisseau)
    alien.delete(missile)
    for k in range(0,len(alien1)):
        alien.delete(alien1[k])
    for k in range(0,len(abris)):
        alien.delete(abris[k])
    alien.delete(souc)
    alien.delete(bombe)
    rejouer()
    return

def rejouer():
    global game_over,alien,fond,gameover,p
    alien.itemconfig(fond,image=game_over)
    gameover=1
    play(p)
    return
    
    
def choix_vaisseau():
    global menu,choix,menu_1,menu_2,choix_soucoupe0,choix_soucoupe1,choix_soucoupe2,choix_soucoupe3,choix_soucoupe4,choix_soucoupe5,choix_soucoupe6
    alien.itemconfig(menu,image=choix_soucoupe0)
    menu_1=0
    menu_2=1
    return

def play(p):
    global fond,Xab,abris,perdu,Live,vie,DX,DY,Yab,alien1,photooo,missile,alien,vaisseau,photo1,photo2,photo3,photo,blocage,X,Y,PosX,PosY,photoo
    alien1=[]
    abris=[]
    vie=3
    Live.config(text='Vies ='+str(vie))
    blocage==1
    alien.delete(menu)
    fond=alien.create_image(0,0,anchor=NW,image=photo1)
    Xab=[350]
    Yab=[225]
    PosX=457
    PosY=454
    X=[]
    Y=[]
    DX=1
    DY=1
    perdu=0
    
    for k in range(5,15):
        X.append(3*k*20)
        Y.append(60)
        alien1.append(alien.create_image(X[-1],Y[-1],image=photo)) 
    for k in range(5,15):
        X.append(3*k*20)
        Y.append(100)
        alien1.append(alien.create_image(X[-1],Y[-1],image=photoo))
    for k in range(5,15):
        X.append(3*k*20)
        Y.append(140)
        alien1.append(alien.create_image(X[-1],Y[-1],image=photooo))
    for k in range(5,15):
        X.append(3*k*20)
        Y.append(180)
        alien1.append(alien.create_image(X[-1],Y[-1],image=photooo))
    for j in range(0,5):
        Xdep=j*170+120
        for i in range(0,2):
            Ydep=360+8*i
            for k in range(0,10):
                Xab.append(Xdep+8*k)
                Yab.append(Ydep)
                abris.append(alien.create_image(Xab[-1],Yab[-1],image=vert))
    vaisseau=alien.create_image(PosX,PosY,image=Liste_vaisseau[p])
    missile=alien.create_image(50,50,image=photo3)
    jouer_LV1()
    return
    
def clic(event):
    global alien,menu,blocage,rejouer,selection1,p,selection_1,menu1,menu_1,menu_2,k,attente
    x, y = event.x, event.y
    #print('{}, {}'.format(x, y))
    if menu_1==1:
        if blocage==1:
            return
        if 463<x<585 and 381<y<414:
            attente=1
            choix_vaisseau()
        if 475<x<550 and 513<y<588:
            mw.destroy()
    if menu_2==1 and attente==0:
        if 246<x<302 and 186<y<232:
            p=0
        if 497<x<549 and 188<y<234:
            p=1
        if 748<x<801 and 191<y<232:
            p=2
        if 250<x<299 and 358<y<402:
            p=3
        if 493<x<550 and 358<y<406:
            p=4
        if 752<x<800 and 364<y<406:
            p=5
        if p>=0:
            menu_2=0
            play(p)
    if gameover==1:
        return

def motion(event):
    global alien,selection_1,menu,rejouer,menu1,menu_1,menu_2,X,Y,attente,selection1,blocage,transition,selection_2
    if blocage==1:
        return
    x, y = event.x, event.y
    if menu_1==1:
        if 463<x<585 and 381<y<414:
            alien.itemconfig(menu,image=selection_1)
        else:
            alien.itemconfig(menu,image=menu1)
        if 437<x<623 and 447<y<485:
            alien.itemconfig(menu,image=selection_2)
        if 475<x<550 and 513<y<588:
            alien.itemconfig(menu,image=selection_3)
    if menu_2==1:
        attente=0
        if 246<x<302 and 186<y<232:
            alien.itemconfig(menu,image=choix_soucoupe1)
        else:
            alien.itemconfig(menu,image=choix_soucoupe0)
        if 497<x<549 and 188<y<234:
            alien.itemconfig(menu,image=choix_soucoupe2)
        if 748<x<801 and 191<y<232:
            alien.itemconfig(menu,image=choix_soucoupe3)
        if 250<x<299 and 358<y<402:
            alien.itemconfig(menu,image=choix_soucoupe4)
        if 493<x<550 and 358<y<406:
            alien.itemconfig(menu,image=choix_soucoupe5)
        if 752<x<800 and 364<y<406:
            alien.itemconfig(menu,image=choix_soucoupe6)
    if rejouer==1:
        return

recommencer=0
gameover=0
p=-1
perdu=0
menu_3=0
Xnuk=-1000
Ynuk=-1000    
tirAl=0       
vie=3
Xab=[350]
Yab=[225]
X_ufo=956
Y_ufo=31
blocage=0
menu_1=1
existence=0
selection1=0
PosX=457
PosY=454
MX=-100
MY=-100
X=[]
Y=[]
DX=1
DY=1
score=0
bonus=0
LARGEUR=1000
HAUTEUR=680
fin=1
menu_2=0
mw = Tk()
mw.title("Space Invaders")
Score=Label(mw,text='Score ='+str(score),fg="black",font=('Times',15,))
Score.config(bg='grey')
Score.pack()
Live=Label(mw,text='Vies ='+str(vie),fg="black",font=('Times',15,))
Live.config(bg='grey')
Live.pack()
alien = Canvas(mw, width=LARGEUR, height=HAUTEUR)
photo=PhotoImage(file='alien.gif')
photoo=PhotoImage(file='alien2.gif')
photooo=PhotoImage(file='alien3.gif')
photo1=PhotoImage(file='noir.gif')
photo3=PhotoImage(file='missile0.gif')
photo4=PhotoImage(file='missile.gif')
soucoupe=PhotoImage(file='ufo.gif')
vert=PhotoImage(file='carre.gif')
nuke=PhotoImage(file='nuke.gif')
menu1 = PhotoImage(file='menu_rien.gif')
game_over=PhotoImage(file='game_over.gif')
choix_soucoupe0= PhotoImage(file='choix0.gif')
choix_soucoupe1= PhotoImage(file='choix1.gif')
choix_soucoupe2= PhotoImage(file='choix2.gif')
choix_soucoupe3= PhotoImage(file='choix3.gif')
choix_soucoupe4= PhotoImage(file='choix4.gif')
choix_soucoupe5= PhotoImage(file='choix5.gif')
choix_soucoupe6= PhotoImage(file='choix6.gif')
vaisseau1=PhotoImage(file='vaisseau.gif')
vaisseau2=PhotoImage(file='vaisseau2.gif')
vaisseau3=PhotoImage(file='vaisseau3.gif')
vaisseau4=PhotoImage(file='vaisseau4.gif')
vaisseau5=PhotoImage(file='vaisseau5.gif')
vaisseau6=PhotoImage(file='vaisseau6.gif')
vaisseau_secret=PhotoImage(file='vaisseau_secret.gif')
game_over=PhotoImage(file='game_over.gif')
Liste_vaisseau=[vaisseau1,vaisseau2,vaisseau3,vaisseau4,vaisseau5,vaisseau6,vaisseau_secret]
menu=alien.create_image(20,40,anchor=NW,image=menu1)
selection_1=PhotoImage(file='selection_1.gif')
selection_2=PhotoImage(file='selection_2.gif')
selection_3=PhotoImage(file='selection_3.gif')
alien.pack()
mw.bind('<KeyPress>',deplacement)
mw.bind('<Button-1>', clic)
mw.bind('<Motion>',motion)
mw.bind('<Alt-Up>',vaisseau_special)
mw.mainloop()
