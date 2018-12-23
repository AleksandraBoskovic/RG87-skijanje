#include <stdlib.h>
#include <GL/glut.h>


#define TIMER_ID 0
#define TIMER_INTERVAL 50

int animation_ongoing;

float move;


static void on_keyboard(unsigned char key,int x, int y);
static void on_reshape(int width,int height);
static void on_timer(int id);
static void on_display(void);
static void lights();
static void material(int value);


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
     move=0;

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;}

    static void on_timer(int id)
{
if(TIMER_ID!=id)
return;

move+=0.01;

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

    }
}

static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 10);
}


static void lights(){

/* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 0, 3, 2, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);




}

static void material(int value){
/* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.3, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.3, 0.0, 0.0, 1 };

    diffuse_coeffs[value]=1.0;

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;

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
    gluLookAt(0,3.7,8, 0, 0, 0, 0, 1, 0);


    /* Kreira se kaciga. */
    material(2);
    glPushMatrix();
    glTranslatef(move,0,5);
    glutSolidSphere(0.6, 40, 40);
    glPopMatrix();

    /*Kreira se jelka*/

    int i=50;

    while(i>0){
     material(1);
    glPushMatrix();
    glTranslatef(5,-3,i);
    glRotatef(240,1,0,0);
    glutSolidCone(1.2,6,40,40);
    glPopMatrix();

     material(1);
    glPushMatrix();
    glTranslatef(5,-3,i-1);
    glRotatef(240,1,0,0);
    glutSolidCone(1.2,4.5,40,40);
    glPopMatrix();

     material(1);
    glPushMatrix();
    glTranslatef(-5,-3,i);
    glRotatef(240,1,0,0);
    glutSolidCone(1.2,6,40,40);
    glPopMatrix();

     material(1);
    glPushMatrix();
    glTranslatef(-5,-3,i-1);
    glRotatef(240,1,0,0);
    glutSolidCone(1.2,4.5,40,40);
    glPopMatrix();
    i--;
    
    }



    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}






