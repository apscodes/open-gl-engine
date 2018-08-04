#include "Camera.h"
#include <ext.hpp>


Camera::Camera()
{
	//*! Set some default values
	m_world_transform = glm::mat4(1);
	m_view_transform = glm::mat4(1);
	m_projection_transform = glm::mat4(1);
	m_projection_view_transform = glm::mat4(1);
  
}


Camera::~Camera()
{
}


/*!
	@brief		
	@params		a_field_of_view -
	@return		void
!*/
void Camera::update(float a_delta_time, GLFWwindow* a_GL_window)
{
}



/*!	
	@brief		Setting the perspective values for the camera
	@params		a_field_of_view - 
	@params		a_aspect_ratio - 
	@params		a_near - 
	@params		a_far - 
	@return		void
!*/
void Camera::set_perspective(const float & a_field_of_view, const float & a_aspect_ratio, const float & a_near, const float & a_far)
{
	m_projection_transform = glm::perspective(a_field_of_view, a_aspect_ratio, a_near, a_far);
	update_projection_view_transform();
}


/*!
	@brief		Setting the faceing direction of the camera
	@params		glm::vec3 - Current position
	@params		glm::vec3 - Facing direction
	@params		glm::vec3 - World axis up direction
	@return		void
!*/
void Camera::set_look_at(const glm::vec3& a_from, const glm::vec3& a_to, const glm::vec3& a_up)
{
	m_view_transform = glm::lookAt(a_from, a_to, a_up);
	m_world_transform = glm::inverse(m_view_transform);
	update_projection_view_transform();
}


/*!
	@brief		Set the position to the position section of the world_trasnform
	@params		glm::vec4 - containing the calculated position
	@return		void
!*/
void Camera::set_position(const glm::vec4 & a_position)
{
	m_world_transform[3] = a_position;
	m_view_transform = glm::inverse(m_world_transform);
	update_projection_view_transform();
}


/*!
	@brief		Update the matrix of the camera
	@return		void
!*/
void Camera::update_projection_view_transform()
{
	m_projection_view_transform = m_projection_transform * m_view_transform;
}
