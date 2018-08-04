#include "Light.h"


//*! Default
Light::Light() : m_direction(),
				 m_diffuse(),
				 m_specular(),
				 m_ambient_light()
{}


//*! Overloaded Constuctor
Light::Light(const glm::vec3 & a_direction, const glm::vec3 & a_diffuse, const glm::vec3 & a_specular, const glm::vec3 & a_ambient)
{
	set_direction(a_direction);
	set_ambient(a_ambient);
	set_diffuse(a_diffuse);
	set_specular(a_specular);
}

//Deconstructor
Light::~Light()
{
}
