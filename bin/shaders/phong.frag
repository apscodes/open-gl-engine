//*! Classic Phong frag shader

#version 410


in vec4 vPosition;
in vec3 vNormal;

//*! Light Base Ambient
uniform vec3 Light_Ambient;
//*! Light Diffuse
uniform vec3 Light_Diffuse;
//*! Light Highlight
uniform vec3 Light_Specular;
//*! Current Light Direction
uniform vec3 Light_Direction;

//*! Object Base Ambient
uniform vec3 Object_Ambient;
//*! Object Diffuse
uniform vec3 Object_Diffuse;
//*! Object Specular
uniform vec3 Object_Specular;
//*! Specular Power
uniform float Specular_Power; 

//*! Current Camera Position
uniform vec3 Camera_Position;

//*! Final Out
out vec4 FragColour;

void main() 
{
	//*! Ensure normal and light direction are normalised
	vec3 final_normal = normalize(vNormal);
	vec3 nLight_direction = normalize(Light_Direction);

	//*! Calculate lambert term (negate light direction)
	float lambertTerm = max( 0, min( 1, dot( final_normal, -nLight_direction ) ) );

	//*! view vector (camera)
	vec3 view_vector = normalize(Camera_Position - vPosition.xyz);
	//*! Reflection vector
	vec3 reflection_vector = reflect(nLight_direction, final_normal);

	//*! Calculate Specular
	float specular_term = pow( max( 0, dot(reflection_vector, view_vector)), Specular_Power);

	//*! Calculate Ambient
	vec3 final_ambient = Light_Ambient * Object_Ambient;

	//*! Calculate Diffuse
	vec3 final_diffuse = Light_Diffuse * Object_Diffuse * lambertTerm;

	//*! Calculate Specular
	vec3 final_specular = Light_Specular * Object_Specular * specular_term;

	//*! Final output
	FragColour = vec4(final_ambient + final_diffuse + final_specular, 1 );
}