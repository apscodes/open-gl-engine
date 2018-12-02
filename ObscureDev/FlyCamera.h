#pragma once
#include "Camera.h"
 
#include "Input.h"

class FlyCamera : public Camera
{

public:
	FlyCamera();
	FlyCamera(const float& a_movement_speed);
	~FlyCamera();

	/*!
		@brief		Camera update - check input from user
		@params		a_delta_time - A difference in time between frames
		@params		a_GL_window - A reference to the current window
		@return		void
	!*/
	virtual void update(float a_delta_time, GLFWwindow* a_GL_window);

	/*!
		@brief		Set the movement speed of the camera
		@params		a_speed - A value that is assigned to the movement speed of the camera
		@return		void
	!*/
	void set_speed(const float& a_speed) { m_movement_speed = a_speed; };



private:

	//*! Camera movement speed
	float m_movement_speed;
	//*! Upwards vector 
	glm::vec3 m_up;
	//*! User Input
	aie::Input* m_input;

	//*! Mouse Input Raw
	double m_mouse_x;
	double m_mouse_y;

	//*! Mouse position delta
	double m_delta_mouse_x;
	double m_delta_mouse_y;

	//*! Set the camera to look at the centre of the world on the first loop
	bool once  = false;
 
};

