#pragma once

#include <glm.hpp>
#include <ext.hpp>
#include <glfw3.h>

class Camera
{

public:
	Camera();
	~Camera();
 
	//*! Pure virtual update as each camera will habe a unique update
	virtual void update(float a_delta_time, GLFWwindow* a_GL_window);
	
#pragma region Setters
	//*! Set a mew perspective for the camera
	void set_perspective(const float& a_field_of_view, const float& a_aspect_ratio, const float& a_near, const float& a_far);
	//*! Set look and from into points in space
	void set_look_at(const glm::vec3& a_from, const glm::vec3& a_to, const glm::vec3& a_up);
	//*! Move the camera to this position
	void set_position(const glm::vec4& a_position);
#pragma endregion
 

#pragma region Getters
	//*! Get the cameras world transform
	glm::mat4 const get_world_transform() { return m_world_transform; };
	//*! Get the cameras view transform
	glm::mat4 const get_view_transform() { return m_view_transform; };
	//*! Get the cameras veiw transform
	const glm::mat4* const get_view() const { return &m_view_transform; };
	//*! Get the cameras projection transform
	const glm::mat4* const get_projection() const { return &m_projection_transform; };
	//*! Get a precalculated projection * view transform
	const glm::mat4* const get_projection_view() const { return &m_projection_view_transform; };
	//*! Window Size
	glm::ivec2 const get_window_size() { return m_window_size; };
#pragma endregion
 
	void translate(const glm::vec4& a_translation_vector) { m_world_transform[3] += a_translation_vector; };

protected:	 
	//*! Update whenever the projection of the view changes
	void update_projection_view_transform();

	//*! Cameras Position and Rotation
	glm::mat4 m_world_transform;
	//*! Inverse world transform
	glm::mat4 m_view_transform;
	//*! Projection matrix information
	glm::mat4 m_projection_transform;
	//*! Projection x View transform information
	glm::mat4 m_projection_view_transform;

	//*! Window Data
	glm::ivec2 m_window_size;

private:


};

