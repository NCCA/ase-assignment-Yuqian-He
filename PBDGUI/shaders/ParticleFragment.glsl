// a fragment shader is responsible for determining the final color of each pixel on the screen.
#version 410 core

layout(location=0) out vec4 fragColour;//specifies the output fragment color.

in vec3 particleColour;

void main()
{
    fragColour=vec4(particleColour,1.0);
}