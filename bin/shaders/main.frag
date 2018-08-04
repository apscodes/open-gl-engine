//*! A normal map fragment shader - with phong lighting
#version 410


in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;

//*! Output colour
out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;


//*! object material ambient
uniform vec3 Ka; 

//*! object material diffuse
uniform vec3 Kd; 

//*! object material specular
uniform vec3 Ks;

//*! Specular power
uniform float specularPower;


struct Light_Data
{
	//*! Light ambient colour
	vec3 Light_Ambient;

	//*! Light diffuse colour
	vec3 Light_Diffuse; 

	// Light specular colour
	vec3 Light_Specular; 

	//*! Light direction
	vec3 Light_Direction;
};
    
#define NR_LIGHTS 2
uniform Light_Data m_lights[NR_LIGHTS];



//*! Material Specular Power
uniform float Specular_Power; 

//*! Camera Position (world space)
uniform vec3 Camera_Position;


//*! Light Calculation
vec3 Calculate_Directional_Lights(Light_Data a_light, vec3 a_normalNormalised, vec3 a_viewVector)
{
    vec3 lightDir = normalize(a_light.Light_Direction);

    //Calculates the lambert term( negate light direction)
    float lambertTerm;

    lambertTerm = max( 0, min( 1, dot( a_normalNormalised, lightDir)));    
    
    vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
    vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;

    vec3 reflectionVector = reflect( lightDir, a_normalNormalised);
    
    float specularTerm = pow(max(0, dot(reflectionVector, a_viewVector)), specularPower);
    
    vec3 diffuse = a_light.Light_Diffuse * Kd * texDiffuse * lambertTerm;
    vec3 ambient = a_light.Light_Ambient * Ka;
    vec3 specular = a_light.Light_Specular * Ks * texSpecular * specularTerm;
    
    return(ambient + diffuse + specular);
}




//*! Entry Point
void main() 
{
	//*!
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	//vec3 L = normalize(Light_Direction);
	//*!
	mat3 TBN = mat3(T,B,N);

	
	//*!
	//vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;
	vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	//*!
	N = TBN * (texNormal * 2 - 1);
	
	//*! Calculate lambert term
	//float lambertTerm = max( 0, dot( N, -L ) );

	//*! Calculate view vector and reflection vector
	vec3 V = normalize(Camera_Position - vPosition.xyz);
	//vec3 R = reflect( L, N );

	//*! Calculate specular term
	//float specularTerm = pow( max( 0, dot( R, V ) ), Specular_Power );

	//*! Calculate each light property
	//vec3 ambient = Light_Ambient * Ka;
	//vec3 diffuse = Light_Diffuse * Kd * texDiffuse * lambertTerm;
	//vec3 specular = Light_Specular * Ks * texSpecular * specularTerm;


	vec3 result = vec3(0, 0, 0);
    for(int index = 0; index < NR_LIGHTS; index++)
    {
        result += Calculate_Directional_Lights(m_lights[index], N, V);
    }

	//vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;

	FragColour = vec4(result, 1); //vec4(ambient + diffuse + specular, 1);

}