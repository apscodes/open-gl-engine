//*! Classic Phong vertex shader

#version 410

layout( location = 0 ) in vec4 Position;
layout( location = 1 ) in vec4 Normal;

//*! Output Position
out vec4 vPosition;
//*! Output Normal
out vec3 vNormal;

uniform mat4 ProjectionViewModel;

//*! Matrix Transform 
uniform mat4 ModelMatrix;

//*! Matrix to transform the normal
uniform mat3 Normal_Matrix;


void main() 
{
	vPosition = ModelMatrix * Position;
	vNormal = Normal_Matrix * Normal.xyz;
	gl_Position = ProjectionViewModel * Position;
}