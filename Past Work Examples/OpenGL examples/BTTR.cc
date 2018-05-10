/* 		Created by Mark Brown
 *   	Date: 
 *   	Description: 
 * 
 *		https://www.youtube.com/watch?v=7k8RCVfTS7w
 */

#include <iostream>
#include <Angel.h>

//GLfloat _anglePyramid = 0.0f;
//GLfloat _angleCube = 0.0f;  
int refreshRate = 15;        // refresh rate in milliseconds
 
// Sets the background colour, depth, depth testing, type of depth test and corrections in terms of perspective
void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST); //Depth test was enabled... why didn't it work?
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
}
 

void display() {
 /*
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   glMatrixMode(GL_MODELVIEW);     // Specifies which metrix stack is the target for subsequent matrix operations
 
   // Build 3D Cube GameObject
   glLoadIdentity();                 
   glTranslatef(1.5f, 0.0f, -7.0f); 

   // Rotates the cude to roughly (1,1,1)
   glRotatef(_angleCube, 1.0f, 1.0f, 1.0f);

   // Build the Pyramid 3D GameObject
   glLoadIdentity();                  
   glTranslatef(-1.5f, 0.0f, -6.0f);  

   // Rotate the Pryamid
   glRotatef(_anglePyramid, 1.0f, 1.0f, 0.0f); 

 
   // Used for Double Buffering (Swap the two frame buffers [back and front buffer])
   glutSwapBuffers();
 
   // Update the angle rotation
   _anglePyramid += 0.2f;
   _angleCube -= 0.15f;
   */
   
   
   //game objects or functions to create gameobjects goes here.
   //background scrolls downward and bomber plane stays still
   //moving objedcts and mouse click to destory or save
   
   
}
 
// Used to rebuild the display every "refreshRate" interval
void timer(int value) {
	
   glutPostRedisplay();
   glutTimerFunc(refreshRate, timer, 0);
}


// Make sure to use the example within his files. Most recent lecture had these files
extern "C" void keys (unsigned char key)
{
 /* switch (key) {
  case 'c':
    exit(EXIT_SUCCESS);
    break;
  }*/
  
  //menu goes here
}
 
// keep this the same
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

   // figure out what full screen is
   // Sets the window size
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Bombers to the Rescue");

   //glewInit();
   
   glutDisplayFunc(display);
   glutReshapeFunc(myReshape);
   init();
   glutTimerFunc(0, timer, 0);

   // Event loop
   glutMainLoop();

   return(EXIT_SUCCESS);
}

