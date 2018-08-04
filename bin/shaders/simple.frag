//*! a simple flat colour shader

#version 410

uniform vec3 diffuseTexture; //*! Diffuse colour

out vec4 FragColour;

void main() 
{
	FragColour = vec4(diffuseTexture, 1);
}
