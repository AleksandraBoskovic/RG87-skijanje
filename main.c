/*
Dve ravni su postavljene tako da je prva po z osi gledano od -60 do 60 a druga od -60 do -180
Na obe ravni postavljeno je nekoliko redova jelki sa obe strane i za svaku ravan odredjen niz prepreka 
na njima.Figurica je postavljena na z osi na 45. Iluzija kretanja je definisana pomeranjem cele scene
ka figuri dok je ona staticna i moze levo ili desno da se krece. Kada predje duzinu prve ravni
ona se translira iza druge ravni i ponovo se biraju prpreke i iscrtavaju.Kada se predje i duzina 
druge ravni ona se translira iza prve i za nju se takodje prave nove prpreke.Nakon toga smo ponovo u 
pocetnoj situaciji prva ravan iza nje druga.
Kretanje figurice je ograniceno izmedju jelki.
Ograniceno da se plave prepreke oilaze sa leve strane a crvene sa desne. 

*/
#include <stdlib.h>
#include <GL/glut.h>


#define TIMER_ID 0
#define TIMER_INTERVAL 50

int animation_ongoing;
int animation_parameter;
int perioda_transacije;
/*Koristi se za deljenje u tri slucaja smenjivanja dve ravni*/
int korak;
/*x-kordinata skijasa*/
float move;
struct zastavica {int x,y,z;};
typedef struct zastavica Zastavica;
/*Nizovi zastavica prve i druge ravni*/
Zastavica nizZastavicaPrve [4];
Zastavica nizZastavicaDruge [4];

static void on_keyboard(unsigned char key,int x, int y);
static void on_reshape(int width,int height);
static void on_timer(int id);
static void on_display(void);
static void lights();
static void material(double valueX,double valueY,double valueZ);
static void postaviJelke();
static void napraviSkijasa();
static void napraviPreprekePrve();
static void napraviPreprekeDruge();
static void postaviPrepreke(Zastavica *nizZastavica);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

     animation_ongoing=0;  
     animation_parameter=0;
     move=0;
     korak=0;
     perioda_transacije=0;
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;}

    static void on_timer(int id)
{
if(TIMER_ID!=id)
return;

animation_parameter+=1;
/*Duzine obe ravni koje se smenjuju su 120.Svaki put kada se menja poredak ravni uvecava se korak
radi razlikovanja 3 situacije prva ravan i iza nje druga(korak%3==0)
translirana prva ravan iza druge (korak%3==1)i treci slucaj translacija druge ravni iza prve(korak%3==2)*/
if((animation_parameter % 120)==0)
{korak+=1;}

/*Perioda transkacije je uvek izmedju 0 i 240 jer je to ukupna duzina trajanja ova tri slucaja 
Nakon cega se ponovo vracamo u situaciju 1 pa sve iznova */

perioda_transacije+=1;

glutPostRedisplay();

if(animation_ongoing){

glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);}


}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'g':
    /*Pokretanje animacije*/
    if(!animation_ongoing){
       animation_ongoing=1;
       glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
    }
    break;

    case 's':
    /*zaustavljanje animacije*/
    animation_ongoing=0;
    break;

    case 'd':
    /*pomeranje po x osi figurice udesno*/
    move+=1;
    glutPostRedisplay();
    break;

    case 'a':
     /*pomeranje po x osi figurice ulevo*/
    move-=1;
    glutPostRedisplay();
    break;

    case 'r':
    /*Vracanje na pocetak*/
    korak=0;
    move=0;
    animation_ongoing=0;
    animation_parameter=0;
    perioda_transacije=0;
    glutPostRedisplay();
    break;

    }
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 120);
}


static void lights(){

/* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 0, 20, 60, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);



}


static void material(double valueX,double valueY,double valueZ){
/* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.0, 1 };
     
         diffuse_coeffs[0] = valueX;
         diffuse_coeffs[1] = valueY;
         diffuse_coeffs[2] = valueZ;
    

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 30;

/* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

static void on_display(void)
{
   

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lights();

    /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,15,60, 0, 0, 0, 0, 1, 0);


/*Ogranicava se kretanje figurice po x osi.Greskom kada se udari u jelke sa strane 
Vraca na pocetak*/

 if(move>=13 || move<=(-13)){
        korak=0;
        move=0;
        animation_parameter=0;
        animation_ongoing=0;
    }




napraviSkijasa();

/*Prosli smo kroz sva tri slucaja zamena ravni pa se vracamo na pocetni slucaj*/
if(perioda_transacije>240){
    perioda_transacije=0;
}



if(animation_parameter!=0){
glTranslated(0,0,perioda_transacije);}



/*Kreiramo prvu ravan*/
    
    material(1.0,1.0,1.0);
    glPushMatrix();

/*Kada je perioda translacije >120 nasu prvu ravan pomeramo iza druge ravni jer smo je celu presli */
    if(perioda_transacije>=120){
    glTranslated(0,0,-240);}

    glScaled(50,1,120);
    glutSolidCube(1);
    glPopMatrix();

glPushMatrix();
/*Takodje sa ravni transliramo i njenje jelke i prepreke*/
 if(perioda_transacije>=120){
    glTranslated(0,0,-240);}
/*Na pocetku animacije i u slucaju kada prvu ravan transliramo iza druge jer smo je presli
na nju postavljamo nove random prepreke*/
if(animation_parameter==0 || perioda_transacije==120){
     postaviJelke();
     napraviPreprekePrve();
     postaviPrepreke(nizZastavicaPrve);
     }
    else{
    postaviJelke();
    postaviPrepreke(nizZastavicaPrve);

     }
glPopMatrix();




/*Kreira se druga ravan*/

    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0,0,-120);
    glScaled(50,1,120);
    glutSolidCube(1);
    glPopMatrix();

/*Za drugu ravan kada predjemo 240 smo presli i nju transliramo je iza prve ravni i 
pozivamo pravljenje novih prepreki*/
 if(animation_parameter==0 || perioda_transacije==240){
     postaviJelke();
     napraviPreprekeDruge();
     glPushMatrix();
     glTranslated(0,0,-120);
     postaviJelke();
     postaviPrepreke(nizZastavicaDruge);
     glPopMatrix();
     }
     else{
    postaviJelke();
     glPushMatrix();
     glTranslated(0,0,-120);
     postaviJelke();
     postaviPrepreke(nizZastavicaDruge);
     glPopMatrix();
     
     }

/*Kada je perioda <120 prelazimo prepreke prve ravni.
Proveravamo da li je translacijom prepreka pomerena na z kordinatu figurice
Ako jeste plavu prepreku ako nismo obisli sa leve strane vraca nas na pocetak.Crvenu prepreku 
moramo obici sa desne strane.U nizu nizZastavicaPrve imamo zapamcenje tekuce kordinate zastavica  */
if(perioda_transacije<120){
int plave;
for(plave=1;plave<4;plave+=2){
if(nizZastavicaPrve[plave].z+perioda_transacije==45){
    if(nizZastavicaPrve[plave].x-1.9<move){
        animation_ongoing=0;
        animation_parameter=0;
        perioda_transacije=0;
        korak=0;
    }
}
}

int crvene;
for(crvene=0;crvene<4;crvene++){
    if(nizZastavicaPrve[crvene].x+perioda_transacije==45){
        if(nizZastavicaPrve[crvene].x+1.9>move){
        animation_ongoing=0;
        animation_parameter=0;
        perioda_transacije=0;
        korak=0;
        }
    }
}

}
/*U suprotnom prelazimo drugu ravan i gledamo prepreke druge ravni na isti nacin kao za prvu ravan*/
else{
int plave2;
for(plave2=1;plave2<4;plave2+=2){
if(nizZastavicaDruge[plave2].z-120+perioda_transacije==45){
    if(nizZastavicaDruge[plave2].x-1.9<move){
        animation_ongoing=0;
        animation_parameter=0;
        perioda_transacije=0;
        korak=0;
    }
}
}

int crvene2;
for(crvene2=0;crvene2<4;crvene2++){
    if(nizZastavicaDruge[crvene2].x-120+perioda_transacije==45){
        if(nizZastavicaDruge[crvene2].x+1.9>move){
        animation_ongoing=0;
        animation_parameter=0;
        perioda_transacije=0;
        korak=0;
        }
    }
}


}


    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

void postaviJelke(){

int k;

for(k=(-55);k<60;k+=5){

/* Desno cetiri reda jelki*/

 material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(15,-2,k);
    glRotatef(280,1,0,0);
    glutSolidCone(2.5,9,40,40);
    glPopMatrix();


material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(17,-2,k+2);
    glRotatef(280,1,0,0);
    glutSolidCone(2.5,9,40,40);
    glPopMatrix();

material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(19,-2,k+1);
    glRotatef(280,1,0,0);
    glutSolidCone(2,9,40,40);
    glPopMatrix();

material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(22,-2,k+3);
    glRotatef(280,1,0,0);
    glutSolidCone(2,9,40,40);
    glPopMatrix();


    /* Levo cetiri reda jelki*/

 material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(-15,-1.5,k);
    glRotatef(280,1,0,0);
    glutSolidCone(2.5,9,40,40);
    glPopMatrix();


material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(-17,-1.5,k+2);
    glRotatef(280,1,0,0);
    glutSolidCone(2.5,9,40,40);
    glPopMatrix();

material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(-19,-1.5,k+1);
    glRotatef(280,1,0,0);
    glutSolidCone(2,9,40,40);
    glPopMatrix();

material(0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(-22,-1.5,k+3);
    glRotatef(280,1,0,0);
    glutSolidCone(2,9,40,40);
    glPopMatrix();

}

}


static void napraviSkijasa(){


/* Kreira se kaciga. */
    material(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(move,4.5,45.5);
    glutSolidSphere(0.6, 40, 40.5);
    glPopMatrix();

 /* kreiram telo */
    material(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(move,3,45.5);
    glRotatef(280,1,0,0);
    glutSolidCone(0.6,1.5,40,40);
    glPopMatrix();


/* Kreiram noge*/
      material(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(move-0.20,1.5,45);
    glRotatef(280,1,0,0);
    glutSolidCone(0.3,1.5,40,40);
    glPopMatrix();



    material(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(move+0.20,1.5,45);
    glRotatef(280,1,0,0);
    glutSolidCone(0.3,1.5,40,40);
    glPopMatrix();

    /*Kreiram skije */

    material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(move+0.20,1,45);
    glScaled(0.6,0.4,3);
    glutSolidCube(1);
    glPopMatrix();

    material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(move-0.20,1,45.);
    glScaled(0.6,0.4,3);
    glutSolidCube(1);
    glPopMatrix();


}

/*Funkcija koja pravi kordinate prepreka prve ravni*/
static void napraviPreprekePrve(){

int k;
/*Definisem da plave prpreke stoje sa leve strane staze a crvene sa desne.
Jer cu crvene obilaziti sa desne strane a plave sa leve*/
int kordinateZastavicaCrvene[]={-1,0,7,6,5,4,3,2,1};
int kordinateZastavicaPlave[]={-7,-6,-5,-4,-3,-2-1,0,1};


for(k=0;k<4;k++){
if(k%2==0){
nizZastavicaPrve[k].x=kordinateZastavicaCrvene[rand() % 9];}
else{
nizZastavicaPrve[k].x=kordinateZastavicaPlave[rand() % 9];
}
nizZastavicaPrve[k].y=2;
nizZastavicaPrve[k].z=(-60)+k*30;}

}
/*Funkcija koja pravi kordinate prepreka druge ravni*/
static void napraviPreprekeDruge(){

int k;
int kordinateZastavicaCrvene[]={-1,0,7,6,5,4,3,2,1};
int kordinateZastavicaPlave[]={-7,-6,-5,-4,-3,-2-1,0,1};

for(k=0;k<4;k++){
if(k%2==0){
nizZastavicaDruge[k].x=kordinateZastavicaCrvene[rand() % 9];}
else{
nizZastavicaDruge[k].x=kordinateZastavicaPlave[rand() % 9];
}
nizZastavicaDruge[k].y=2;
nizZastavicaDruge[k].z=(-60)+k*30;}

}

static void postaviPrepreke(Zastavica *nizZastavica){

int j;

/*Prepreke sam postavila na rastojanju 30.Sad obezbedjujem da naizmenicno se iscrtavaju 
plave i crvene prepreke*/

for(j=0;j<3;j+=2)
{
 material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(nizZastavica[j].x,nizZastavica[j].y,nizZastavica[j].z);
    glScaled(3,1.5,1);
    glutSolidCube(1);
    glPopMatrix();

   material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(nizZastavica[j].x+1.5,1.5,nizZastavica[j].z);
    glScaled(0.2,3,0.2);
    glutSolidCube(1);
    glPopMatrix();


   material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(nizZastavica[j].x-1.5,1.5,nizZastavica[j].z);
    glScaled(0.2,3,0.2);
    glutSolidCube(1);
    glPopMatrix();



    material(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(nizZastavica[j+1].x,2,nizZastavica[j+1].z);
    glScaled(3,1.5,1);
    glutSolidCube(1);
    glPopMatrix();


 material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(nizZastavica[j+1].x+1.5,1.5,nizZastavica[j+1].z);
    glScaled(0.2,3,0.2);
    glutSolidCube(1);
    glPopMatrix();


   material(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(nizZastavica[j+1].x-1.5,1.5,nizZastavica[j+1].z);
    glScaled(0.2,3,0.2);
    glutSolidCube(1);
    glPopMatrix();




}






}




