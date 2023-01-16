//vertex shader is responsible for transforming 3D positions into 2D coordinates,
#version 410 core

//pecifies the input vertex attribute
layout(location=0) in vec3 inPos;
//This line is defining a variable called inPos that will hold the 3D position of each vertex in the mesh. 
layout(location=1) in vec3 inColour;
uniform mat4 MVP;
//uniform vec3 inColour;

out vec3 particleColour;
// It is called once for each vertex in the mesh, 
//and its job is to transform the input position into the output position that will be used to draw the vertex on the screen.
void main()
{
    gl_Position=MVP*vec4(inPos,1);
    particleColour=inColour;
    //gl_Position = inColour;
}