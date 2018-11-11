#include<GL/glut.h>
#include<stdlib.h>
#include<time.h>


double x_cur, y_cur, z_cur;
static int window_width,window_height;
static double v_x,v_y,v_z;
static float size=0.5;


static void on_display (void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

void pomeri(double v_x,double v_y,double v_z);


int main(int argc, char** argv)
{

glutInit(&argc,argv);

glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

glutInitWindowSize(600,600);

glutInitWindowPosition(100,100);

glutCreateWindow(argv[0]);


glutKeyboardFunc(on_keyboard);
glutReshapeFunc(on_reshape);
glutDisplayFunc(on_display);




x_cur = 0.0;
y_cur = 0.0;
z_cur = 0.0;


glClearColor(0.05,0.05,0.05,0);

glEnable(GL_DEPTH_TEST);
glLineWidth(2);

glutMainLoop();

return 0;


}


static void on_keyboard(unsigned char key, int x, int y){


switch(key){

case 27:
exit(0);
break;
case 'a':
pomeri(-0.1,0,0);
break;
case 'd':
pomeri(0.1,0,0);
break;
case 'w':
pomeri(0,0,-0.1);
break;
case 's':
pomeri(0,0,0.1);
break;
case 'q':
pomeri(0,0.1,0);
break;
case 'e':
pomeri(0,-0.1,0);
break;
}
}


static void on_reshape(int width, int height){

window_width=width;
window_height=height;

}

void pomeri(double v_x,double v_y,double v_z){

x_cur+=v_x;

if(x_cur<=-(1-size/2) || x_cur>= 1-size/2)
v_x*=-1;

y_cur+=v_y;

if(y_cur<=-(1-size/2) || y_cur>= 1-size/2)
v_y*=-1;
z_cur+=v_z;

if(z_cur<=-(1-size/2) || z_cur>= 1-size/2)
v_z*=-1;

glutPostRedisplay();

}


static void on_display(void){

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glViewport(0,0,window_width,window_height);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

gluPerspective(60,window_width/(float)window_height,1,25);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

gluLookAt(10/5,20/5,30/5,0,0,0,0,1,0);

glPushMatrix();


/*
  a glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
  b glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
  c glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);
  d glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);
  e glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
  f glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
  g glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
 */


glColor3f(0,0,1);

glBegin(GL_QUADS);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
glEnd();

glColor3f(0,0,1);

glBegin(GL_QUADS);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);

glEnd();

glColor3f(0,0,1);

glBegin(GL_QUADS);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur-0.5);
glEnd();

glColor3f(0,0,1);

glBegin(GL_QUADS);

glVertex3f(x_cur-0.5,y_cur-0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
glEnd();

glColor3f(0,0,1);

glBegin(GL_QUADS);

glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
glEnd();

glColor3f(0,0,1);

glBegin(GL_QUADS);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur-0.5);
 glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);
 glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
glEnd();

glPopMatrix();

glBegin(GL_LINES);
glColor3f(0,1,0);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
 glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
glColor3f(0,1,0);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
glColor3f(0,1,0);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
glColor3f(0,1,0);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur+0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur+0.5);
glColor3f(0,1,0);
glVertex3f(x_cur+0.5,y_cur-0.5,z_cur-0.5);
glVertex3f(x_cur+0.5,y_cur+0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur-0.5);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur-0.5);
glColor3f(0,1,0);
glVertex3f(x_cur-0.5,y_cur-0.5,z_cur+0.5);
glVertex3f(x_cur-0.5,y_cur+0.5,z_cur+0.5);




glColor3f(1,0,0);
glVertex3f(0,0,0);
glVertex3f(10,0,0);
glColor3f(0,1,0);
glVertex3f(0,0,0);
glVertex3f(0,10,0);
glColor3f(0,0,1);
glVertex3f(0,0,0);
glVertex3f(0,0,10);

glEnd();






glutSwapBuffers();
}