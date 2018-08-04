#include "FlyCamera.h"
#include <iostream>	



FlyCamera::FlyCamera() : m_movement_speed(10.0f), m_up(glm::vec3(0,1,0))
{
}

FlyCamera::FlyCamera(const float & a_movement_speed)
{
	m_movement_speed = a_movement_speed;

	m_up = glm::vec3(0, 1, 0);

	m_window_size = glm::ivec2(0);
}



FlyCamera::~FlyCamera()
{
}

void FlyCamera::update(float a_delta_time, GLFWwindow * a_GL_window)
{
	//*! Create an instance of the aie::Input
	m_input = aie::Input::getInstance();

	//*! Mouse Input
	glfwGetCursorPos(a_GL_window, &m_mouse_x, &m_mouse_y);
	
	//*! Relocate at some point
	//*! Get the windows center position based on the width and hieght of the window
	glfwGetWindowSize(a_GL_window, &m_window_size.x, &m_window_size.y);

	//*! Calculate the mouse positional offset from center
	m_delta_mouse_x = ((m_window_size.x  / 2) - m_mouse_x) * 0.0174533;
	m_delta_mouse_y = ((m_window_size.y / 2) - m_mouse_y) * 0.0174533;
	
	//*! Set the cursor to the center of the screen
	glfwSetCursorPos(a_GL_window, (m_window_size.x / 2), (m_window_size.y / 2));
	
	//*! Calculate the  world up relative to the camera
	glm::vec4 m_up = glm::inverse(m_world_transform) * glm::vec4(0,1,0,0);
	glm::mat4 m_rot_mat(1.0f);

	//*! Rotate on the global worlds up
	m_rot_mat = glm::rotate((float)-m_delta_mouse_x * a_delta_time, glm::vec3(m_up[0], m_up[1], m_up[2]));
	m_view_transform = m_rot_mat * m_view_transform;
	
	//*! Rotate Up/Down
	m_rot_mat = glm::rotate((float)-m_delta_mouse_y * a_delta_time, glm::vec3(1,0,0));
	m_view_transform = m_rot_mat * m_view_transform;
	
	//*! Update world transform
	m_world_transform = glm::inverse(m_view_transform);


	//*! Keyboard Input
	//*! Get input key W - Forward
	if (glfwGetKey(a_GL_window, GLFW_KEY_W) || m_input->wasKeyPressed(aie::INPUT_KEY_W))
		translate(get_world_transform()[2] * -m_movement_speed * a_delta_time);

	//*! Get input key A - Left
	if (glfwGetKey(a_GL_window, GLFW_KEY_A) || m_input->wasKeyPressed(aie::INPUT_KEY_A))
		translate(get_world_transform()[0] * -m_movement_speed * a_delta_time);
		
	//*! Get input key S - Backwards
	if (glfwGetKey(a_GL_window, GLFW_KEY_S) || m_input->wasKeyPressed(aie::INPUT_KEY_S))
		translate(get_world_transform()[2] * m_movement_speed * a_delta_time);

	//*! Get input key D - Right
	if (glfwGetKey(a_GL_window, GLFW_KEY_D) || m_input->wasKeyPressed(aie::INPUT_KEY_D))
		translate(get_world_transform()[0] * m_movement_speed * a_delta_time);
	
	//*! Get input key Q - Down
	if (glfwGetKey(a_GL_window, GLFW_KEY_Q) || m_input->wasKeyPressed(aie::INPUT_KEY_Q))
		translate(get_world_transform()[1] * -m_movement_speed * a_delta_time);
	
	//*! Get input key E - Up
	if (glfwGetKey(a_GL_window, GLFW_KEY_E) || m_input->wasKeyPressed(aie::INPUT_KEY_E))
		translate(get_world_transform()[1] * m_movement_speed * a_delta_time);

	//std::cout << "Fly Camera Position X:" << get_world_transform()[3].x << " Y:" << get_world_transform()[3].y << " Z:" << get_world_transform()[3].z << std::endl;
 	
 

	

	//*! Constant looking at glm::vec.zero
	///set_look_at(get_world_transform()[3], glm::vec3(0), glm::vec3(0, 1, 0));

	set_position(get_world_transform()[3]);
	//m_up = glm::vec3(0, 1, 0);
}

 