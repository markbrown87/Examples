// Basic fragment shader
//
// Just passes color on.
//
// Written by dmc 
// last-modified: Wed Sep 28 11:40:16 2016
// 

varying vec4 color; // color passed in to this shader.

void main() 
{ 
  gl_FragColor = color;
} 
