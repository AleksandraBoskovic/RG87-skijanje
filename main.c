#include <stdlib.h>
#include <GL/glut.h>


#define TIMER_ID 0
#define TIMER_INTERVAL 50

int animation_ongoing;
double animation_parameter;

float move;
struct zastavica {int x,y,z;};
typedef struct zastavica Zastavica;

Zastavica nizZastavica [20];

static void on_keyboard(unsigned char key,int x, int y);
static void on_reshape(int width,int height);
static void on_timer(int id);
static void on_display(void);
static void lights();
static void material(double valueX,double valueY,double valueZ);
static void postaviJelke();
static void napraviSkijasa();
static void napraviPrepreke();
static void postaviPrepreke();

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

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;}

    static void on_timer(int id)
{
if(TIMER_ID!=id)
return;

animation_parameter+=0.3;

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
    if(!animation_ongoing){
       animation_ongoing=1;
       glutTimerFunc(TIMER_INTERVAL,on_timer,TIMER_ID);
    }
    break;

    case 's':
    animation_ongoing=0;
    break;

    case 'd':
    move+=0.3;
    glutPostRedisplay();
    break;

    case 'a':
    move-=0.3;
    glutPostRedisplay();
    break;

    case 'r':
    move=0;
    animation_ongoing=0;
    animation_parameter=0;
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
    gluPerspective(60, (float) width / height, 1, 60);
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

    /*Kreira se ravan */

    material(1.0,1.0,1.0);
    glPushMatrix();
    glTranslated(0,0,animation_parameter);
    glScaled(50,1,120);
    glutSolidCube(1);
    glPopMatrix();

    
     
     
     napraviSkijasa();

     if(animation_parameter==0){
     postaviJelke();
     napraviPrepreke();
     postaviPrepreke();
     }
     else{
      glTranslated(0,0,animation_parameter);
      postaviJelke();
      postaviPrepreke();
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


static void napraviPrepreke(){

int k;
int kordinateZastavica[]={-10,-9,-8,-7,-6,-5,-4,-3,-2,0,10,9,8,7,6,5,4,3,2};
for(k=0;k<10;k++){

nizZastavica[k].x=kordinateZastavica[rand() % 19];
nizZastavica[k].y=2;
nizZastavica[k].z=(-60)+k*10;}

}

static void postaviPrepreke(){

int j;

for(j=0;j<10;j+=2)
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




