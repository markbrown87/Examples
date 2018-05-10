// Basic shader with offset to move an object, and scaling to work
// with resized windows.
//
// This version adds color passed in as a uniform variable.
//
// Written by dmc 
// last-modified: Wed Sep 28 11:39:26 2016

// Pass in the vertex.
attribute vec4 vPosition;

// Pass out the color to the fragment shader.
varying   vec4 color;


uniform  vec2 windowSize; // How big is the window
uniform  vec4 vColor;     // What color should the object be?

void main() 
{
  gl_Position.x=(2.0*(vPosition.x))/windowSize.x-1.0;
  gl_Position.y=(2.0*(vPosition.y))/windowSize.y-1.0;
  gl_Position.z=0.0;
  gl_Position.w=1.0;
  color = vColor;
  color.a = 1.0;
}
