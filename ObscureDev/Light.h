#pragma once
#include "APS_Core.h"


class Light
{

public:

	//*! Default Constructor
	Light();
	//*! Overloaded
	Light(const glm::vec3& a_direction, const glm::vec3& a_diffuse, const glm::vec3& a_specular, const glm::vec3& a_ambient);
	//*! Deconstructor
	~Light();

	#pragma region Getters

		//*! Get the Direction
		glm::vec3 const get_direction() { return m_direction; };
		//*! Get the Diffuse
		glm::vec3 const get_diffuse() { return m_diffuse; };
		//*! Get the Specular
		glm::vec3 const get_specular() { return m_specular; };
		//*! Get the Ambient
		glm::vec3 const get_ambient() { return m_ambient_light; };

	#pragma endregion

	#pragma region Setters

		//*! Set the Direction
		void set_direction(const glm::vec3 a_direction) { m_direction = a_direction; }
		//*! Set the Diffuse										  
		void set_diffuse(const glm::vec3 a_diffuse) { m_diffuse = a_diffuse; }
		//*! Set the Specular										  
		void set_specular(const glm::vec3 a_specular) { m_specular = a_specular; }
		//*! Set the Ambient										  
		void set_ambient(const glm::vec3 a_ambient) { m_ambient_light = a_ambient; }

	#pragma endregion
		
private: 

	//*! Data
	glm::vec3 m_direction;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_ambient_light;

};