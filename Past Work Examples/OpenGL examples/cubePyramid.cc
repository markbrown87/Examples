/* 	Created by Mark Brown
 *   	Date: 27/9/2017
 *   	Description: The program shows a cube and a pyramid to rotate on the y and z axis with multiple
 *		colours per side. 
 * 
 *	This code was guided and aided by Dr. Chelberg's example files and a tutorial found on
 *	https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html
 *	and pieces of the code is present within this code.
 */

#include <iostream>
#include <Angel.h>

GLfloat _anglePyramid = 0.0f;
GLfloat _angleCube = 0.0f;  
int refreshRate = 15;        // refresh rate in milliseconds
 
// Sets the background colour, depth, depth testing, type of depth test and corrections in terms of perspective
void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
}
 

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW);     // Specifies which metrix stack is the target for subsequent matrix operations
 
   // Build 3D Cube GameObject
   glLoadIdentity();                 
   glTranslatef(1.5f, 0.0f, -7.0f); 

   // Rotates the cude to roughly (1,1,1)
   glRotatef(_angleCube, 1.0f, 1.0f, 1.0f);
 
   glBegin(GL_QUADS); 
      // Top
      glColor3f(0.4f, 1.0f, 0.0f);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom
      glColor3f(1.0f, 0.5f, 0.3f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back
      glColor3f(1.0f, 0.4f, 0.8f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right
      glColor3f(1.0f, 0.0f, 1.0f);
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);


   glEnd();
 
   // Build the Pyramid 3D GameObject
   glLoadIdentity();                  
   glTranslatef(-1.5f, 0.0f, -6.0f);  

   // Rotate the Pryamid
   glRotatef(_anglePyramid, 1.0f, 1.0f, 0.0f); 
 
   glBegin(GL_TRIANGLES);

      // Front
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      glColor3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      glColor3f(1.0f,0.0f,0.0f);
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);
      glVertex3f(-1.0f,-1.0f, 1.0f);

   glEnd();
 
   // Used for Double Buffering (Swap the two frame buffers [back and front buffer])
   glutSwapBuffers();
 
   // Update the angle rotation
   _anglePyramid += 0.2f;
   _angleCube -= 0.15f;
}
 
// Used to rebuild the display every "refreshRate" interval
void timer(int value) {
   glutPostRedisplay();
   glutTimerFunc(refreshRate, timer, 0);
}

// Used to close the program with 'c' key
// If this doesn't compile, it might be here.
extern "C" void keys (unsigned char key)
{
  switch (key) {
  case 'c':
    exit(SUCCESS);
    break;
  }
}
 
// resizing of the window space. Tutorial used GLsizei to limit the into to positive integers
void myReshape(GLsizei width, GLsizei height) { 
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   glViewport(0, 0, width, height);
 
   // Set of the aspect ratio
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 

int main(int argc, char** argv) {
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_DOUBLE);

   // Sets the window size
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Rotating 3D cube and Pyramid. If you're reading this, it compiled");

   //glewInit();
   
   glutDisplayFunc(display);
   glutReshapeFunc(myReshape);
   init();
   glutTimerFunc(0, timer, 0);

   // Event loop
   glutMainLoop();

   return(EXIT_SUCCESS);
}

