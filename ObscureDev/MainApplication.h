#pragma once

//*! Main Includes and TypeDef Shortcuts
#include "APS_Core.h"

//*! RenderTarget
#include "RenderTarget.h"
//*! Light Data
#include "Light.h"
//*! Game Object Container
#include "GameObject.h"
//*! Custom Mesh
#include "Mesh.h"

//*! Camera Object
#include "FlyCamera.h"

//*! #include <thread>


 


class MainApplication
{

public:
	//*! Creates a window on default values
	MainApplication();
	//*! Creates a window with the params
	MainApplication(const glm::ivec2 windowSize, std::string windowTitle,	GLFWmonitor* windowMonitorMode, GLFWwindow* windowShareMode);
	//*! Deletes any newed memory by this class
	~MainApplication();
	
	/*!
		@brief Startup a new window
		@return int - result to 0 if no errors. Otherwise other exit codes will be used
	!*/
	int startup();
	//*! Cleans up glfw windows and aie::gizmos
	void shutdown();
 
	/*! 
		@brief Update the programs main loop
		@return bool - If the program can run another frame, result to true
	!*/
	bool update();
	/*!
		@brief Draw the current frame data and clear the previous frame
		@return void - no need to return anything unless it becomes needed to make sure a successful draw was comepleted
	!*/
	virtual void draw();

	//*! Access to the GLFW window
	GLFWwindow* get_window_ptr() const { return m_window; }
	//*! Get the current delta time
	const double get_delta_time();



protected:


	void create_hex_grid(int row_max, int col_max, float height);
	//*! User input
	aie::Input* m_input;
	
	//*! Game object matricies setup
	void game_object_matrix_setup();
	

	//*! Current window
	GLFWwindow * m_window;
 
	//*! DeltaTime
	double m_delta_time;

	//*! Create a clock and start it
	APS::custom_time m_time;
	//*! Start the clock timers
	void start_clock();


	//*! Rotation Matrix - Game Object
	glm::mat4 m_global_matrix;
	glm::mat4 m_local_matrix;
	glm::mat4 m_parent_matrix;

	//*! Fun sin time
	double m_sinTime;
	
	//*! Dynamic Camera - User Controlleds
	FlyCamera* m_fly_camera;

	//*! Static Camera view and projection direction
	glm::mat4 m_view;
	glm::mat4 m_projection;
	Camera* m_static_camera;

	
	//*! GameObject Data
	GameObject* m_game_object_empty;
	//*! Vector of GameObject
	std::vector<GameObject*> m_game_object;
 
	//*! Custom mesh
	Mesh* m_quad_mesh;
	//*! Shader Data
	aie::ShaderProgram m_quad_shader;
	//*! Texture Data
	aie::Texture m_quad_texture;

	//*! Lighting information
	Light* m_light;
 

	std::vector<Light*> m_lights;


	//*! Render Target
	aie::RenderTarget m_render_target;


private:

	bool blurOn;

	bool distortOn;
	
	int row = 0;
	int col = 0;

	float scale_factor = 5.0f;
	int world_offset = -10;
	//*! No Gap
	float x_odd_set = 0.864f * scale_factor;
	float z_set = 0.750f * scale_factor;
	//*! Slight Gap
	//float x_odd_set = 0.88f * scale_factor;
	//float z_set = 0.766f * scale_factor;
	///*! std::thread m_render_thread;
 
};

