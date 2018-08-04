#include "MainApplication.h"
#include <iostream>
#include "FlyCamera.h"
 

MainApplication::MainApplication() : m_window(nullptr)
{ 
	//*! Object matricies
	game_object_matrix_setup();
	
	//*! Initialises the clock variables
	start_clock();
 

	//*! Creates a graphics card handle to grab access to it.
	if (glfwInit() == false)
	{
		//*! Error Code for when it can not. ^^
		printf("GLFW INIT FAIL");
		return;
	}

	m_window = glfwCreateWindow(1280, 720, "OpenGL Window", nullptr, nullptr);

	//*! Set the cursor position before the camera update is called
	glfwSetCursorPos(m_window, 640, 360);

	//*! Set the defaults
	startup();


	//*! Setup the static camera
	m_static_camera = new Camera();
	m_static_camera->set_look_at(glm::vec3(15, 15, 15), glm::vec3(0), glm::vec3(0, 1, 0));
	m_static_camera->set_perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);


	//*! Set the cursor to the center of the screen
	glfwSetCursorPos(m_window, (m_static_camera->get_window_size().x / 2), (m_static_camera->get_window_size().y / 2));


}

 

MainApplication::MainApplication(const glm::ivec2 a_window_size, std::string a_window_title, GLFWmonitor * a_glfw_monitor, GLFWwindow * a_glfw_window)
{
	//*! Object matricies
	game_object_matrix_setup();

	//*! Initialises the clock variables
	start_clock();


	//*! Creates a graphics card handle to grab access to it.
	if (glfwInit() == false)
	{
		//*! Error Code for when it can not. ^^
		printf("GLFW INIT FAIL");
		return;
	}

	m_window = glfwCreateWindow(a_window_size.x, a_window_size.y, a_window_title.c_str(), a_glfw_monitor, a_glfw_window);

	//*! Set the cursor position before the camera update is called
	glfwSetCursorPos(m_window, a_window_size.x / 2, a_window_size.y / 2);

	//*! Set the defaults
	startup();


	//*! Setup the user contolled camera
	m_fly_camera = new FlyCamera();
	m_fly_camera->set_speed(10.0f);
	m_fly_camera->set_position(glm::vec4(15, 15, 15, 1.0f));
	m_fly_camera->set_look_at(m_fly_camera->get_world_transform()[3], glm::vec3(0), glm::vec3(0, 1, 0));
	m_fly_camera->set_perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.f);


	//*! Setup the static camera
	m_static_camera = new Camera();
	m_static_camera->set_look_at(glm::vec3(15, 15, 15), glm::vec3(0), glm::vec3(0, 1, 0));
	m_static_camera->set_perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	


	//*! Set the cursor to the center of the screen
	//glfwSetCursorPos(m_window, (m_fly_camera->get_window_size().x / 2), (m_fly_camera->get_window_size().y / 2));
	//m_fly_camera->set_look_at(m_fly_camera->get_world_transform()[3], glm::vec3(0), glm::vec3(0, 1, 0));
}


MainApplication::~MainApplication()
{
	//*! Deletion check to make sure it exists before it deletes
	if (m_fly_camera != nullptr)
		delete m_fly_camera;

	//*! Deletion check to make sure it exists before it deletes
	if (m_static_camera != nullptr)
		delete m_static_camera;

	//*! Deletion check to make sure it exists before it deletes
	if (!m_game_object.empty())
	{
		//*! Clear the vector of game objects
		for (int index = 0; index < m_game_object.size(); index++)
		{
			if (m_game_object[index] != nullptr)
				delete m_game_object[index];
		}
	}

	////*! Deletion check to make sure it exists before it deletes
	//if (m_light != nullptr)
	//	delete m_light;
	//*! Deletion check to make sure it exists before it deletes
	if (!m_lights.empty())
	{
		//*! Clear the vector of lights
		for (int index = 0; index < m_lights.size(); index++)
		{
			if (m_lights[index] != nullptr)
				delete m_lights[index];
		}
	}
	//*! Deletion check to make sure it exists before it deletes
	//if (m_game_object_camera != nullptr)
	//	delete m_game_object_camera;
	//*! Deletion check to make sure it exists before it deletes
	if (m_quad_mesh != nullptr)
		delete m_quad_mesh;
}

int MainApplication::startup()
{
	/*! Create Seperate Functions for GLFW Setup - Lights - Game Object Loading - Custom Mesh Data !*/

	#pragma region GLFW Setup

		if (m_window == nullptr)
		{
			glfwTerminate();
			printf("WINDOW == NULLPTR");
			return -2;
		}

		//*! Bring the new window to the front of the screen
		glfwMakeContextCurrent(m_window);

		//*! Load the interface functions for the current window
		//*! If we fail - nuke the window and exit
		if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
			printf("OGL LOAD FAIL");
			return -3;
		}

		glm::ivec2 win_size;
		glfwGetWindowSize(m_window, &win_size.x, &win_size.y);
		//*! 
		if (m_render_target.initialise(1, win_size.x, win_size.y) == false)
		{
			printf("Render Target Error!\n");
		}

		//*! Getting the Open GL Version number
		auto major = ogl_GetMajorVersion();
		auto minor = ogl_GetMinorVersion();
		printf("GL: %i.%i\n", major, minor);
	
		//*! Background colour to clear too
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		//*! Enable Depth
		glEnable(GL_DEPTH_TEST);

	#pragma endregion


	#pragma region AIE Gizmos

		//*! AIE Gizmos - Better numbers
		aie::Gizmos::create(10000, 10000, 10000, 10000);

		//*! AIE Input
		aie::Input::create();

	#pragma endregion


	#pragma region Light Information

		//*! Light Data
		m_light = new Light({ 1, 1, 0 }, { 0.8f, 0.0f, 0.8f }, { 0.75f, 0.75f, 0.75f }, { 0.25f, 0.25f, 0.25f });
		m_lights.push_back(m_light);
 
		m_light = new Light({ 1, 0, 1 }, { 0.0f, 0.8f, 0.0f }, { 0.75f, 0.75f, 0.75f }, { 0.25f, 0.25f, 0.25f });
		m_lights.push_back(m_light);

	#pragma endregion
	

	#pragma region Game Object Loading

		//*! New Object
		m_game_object_empty = new GameObject(glm::vec4(0, 0.5f, 0, 1), "../bin/soulspear/soulspear.obj");

		//*! Pass the lighting data across to the renderer
		m_game_object_empty->set_light_data(m_lights);

		//*! Add in the game object into the vector of game objects
		m_game_object.push_back(m_game_object_empty);
 



		//*! New Object
		m_game_object_empty = new GameObject(glm::vec4(4.5f, 2.5f, 0, 1), "../bin/Camera/leica.obj");

		//*! Rotational Offset of the object
		glm::mat4 rot(1);
		rot = glm::rotate(45.0f, glm::vec3(0, 1, 0));

		m_game_object_empty->set_local_transform(rot * m_game_object_empty->get_local_transform());

		//*! Pass the lighting data across to the renderer
		m_game_object_empty->set_light_data(m_lights);

		//*! Add in the game object into the vector of game objects
		m_game_object.push_back(m_game_object_empty);
		
		

		//*! New Object
		m_game_object_empty = new GameObject(glm::vec4(-10, 10.0f, 0, 1), "../bin/Gargoyle/Gargoyle.obj");
 
		//*! Pass the lighting data across to the renderer
		m_game_object_empty->set_light_data(m_lights);

		//*! New Scale
		m_game_object_empty->set_scale(glm::vec3(0.1f));

		//*! Add in the game object into the vector of game objects
		m_game_object.push_back(m_game_object_empty);

	#pragma endregion


	#pragma region Post Quad Mesh
	
		//*! New Mesh Object
		m_quad_mesh = new Mesh();
		//*! New Quad on the screen
		m_quad_mesh->initialise_full_screen_quad();

		//*! Quad shader and texture data
		m_quad_shader.loadShader(aie::eShaderStage::VERTEX, "../bin/shaders/post.vert");
		m_quad_shader.loadShader(aie::eShaderStage::FRAGMENT, "../bin/shaders/post.frag");
		//*! Link the shaders
		if (m_quad_shader.link() == false) {
			printf("Shader Error: %s\n", m_quad_shader.getLastError());
			return -1;
		}

	#pragma endregion


	return 0;
}

//*! Clean up of aie gizmos and glfw
void MainApplication::shutdown()
{
	//*! Clear the AIE Input from memory
	aie::Input::destroy();
	//*! Clear the AIE Gizmos from memory
	aie::Gizmos::destroy();

	//*! Destroys the window created
	glfwDestroyWindow(m_window);

	//*! Lets go of the graphics card handle to clean the memory that was used.
	glfwTerminate();
}

//*! Return true while the user hasn't pressed the Escape key
bool MainApplication::update()
{
	//*! Main loop
	if (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
 		//*! User Input
		glfwPollEvents();
		//*! User did not press the escape key this frame, continue running the application
		return true;
	}
	else
	{
		//*! User pressed the escape key. Exit the program
		return false;
	}
}



void MainApplication::draw()
{
	//aie::Gizmos::clear();
	
	//*! Clearubf the buffer (old render data) - Colour and depth checks
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 
	 
	//*! Get the current delta time as a double, but cast it as a float for the glm::rotate
	m_delta_time = get_delta_time();

	//*! Move light over time
	m_lights[0]->set_direction(glm::normalize(glm::vec3(glm::cos((float)glfwGetTime() * 2.0f), 0.0f, glm::sin((float)glfwGetTime() * 2.0f))));

	#pragma region GameObject Rendering
 
 	//*! Bind the shader m_game_object_soulspear
	//m_game_object_soulspear->get_combined_shader().bind();

	
	//*! What camera am I using
	if (m_fly_camera != nullptr)
	{	 

		//*! Bind the Render target
		m_render_target.bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			

		#pragma region Grid Rendering

			//*! Clear the gizmos
			//aie::Gizmos::clear();

			//*! Makes an identity matrix
			aie::Gizmos::addTransform(glm::mat4(1));

			//*! Colour of white
			glm::vec4 white(1);
			//*! Colout of black
			glm::vec4 black(0.5f, 0.5f, 0.5f, 1);

			//*! Iterate over the following to create a grid pattern
			for (int i = 0; i < 21; ++i)
			{
				aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
				aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
			}
			
		#pragma endregion


		//*! Game Objects
		for (int index = 0; index < m_game_object.size(); index++)
		{
			//*! Spin of gameObject
			//glm::mat4 rot(1);
			//rot = glm::rotate((float)m_delta_time / 10, glm::vec3(0, 1, 0));
			//m_game_object[index]->set_local_transform(rot * m_game_object[index]->get_local_transform());
		
			//*! Direction between each game object and the camera
			//m_lights[0]->m_direction = glm::vec3(m_game_object[index]->get_local_transform()[3] - m_static_camera->get_world_transform()[3]);
			//*! Light Data - Update
			m_game_object[index]->get_renderer_component()->set_light_data(m_lights);
			 //*! Camera Data - Update
			m_game_object[index]->get_renderer_component()->set_camera(*m_fly_camera);
			//*! Game Object Draw
			m_game_object[index]->draw();
		}

		//*! RenderTarget
		m_render_target.unbind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//*! Bind Quad Shader
		m_quad_shader.bind();

		//*! Update the camera Perspective camera - Pass a static camera
		///auto m_pvm = *m_fly_camera->get_projection() * *m_fly_camera->get_view() *m_quad_mesh->get_local_transform();
		//*! Pass the auto (expecting glm::mat4) into the shader using the 'ProjectionViewModel'
		///m_quad_shader.bindUniform("ProjectionViewModel", m_pvm);
		//*! Diffuse Texture
		//m_quad_shader.bindUniform("diffuseTexture", 0);


		//*! Bind the colour target
		m_quad_shader.bindUniform("post_target", 0);



		blurOn = (glfwGetMouseButton(m_window, 0) == GLFW_PRESS) ? true : false;
		
		if (blurOn)
		{
			//*! Effecting the blur factor over time.
			m_quad_shader.bindUniform("blur_factor", glm::vec2(glm::sin((float)glfwGetTime()) * 15.0f, glm::sin((float)glfwGetTime() * 15.0f)));
		}
		else
		{
			//*! Effecting the blur factor over time.
			m_quad_shader.bindUniform("blur_factor", glm::vec2(0,0));
		}



		distortOn = (glfwGetMouseButton(m_window, 1) == GLFW_PRESS) ? true : false;

		if (distortOn)
		{
			//*! Effecting the blur factor over time.
			m_quad_shader.bindUniform("distort_factor", 15.0f);
		}
		else
		{
			//*! Effecting the blur factor over time.
			m_quad_shader.bindUniform("distort_factor", 0.0f);
		}


		//*! RenderTarget - All above rendered content bind to the target
		m_render_target.get_target(0).bind(0);

		//*! Draw Quad - With the render target texture
		m_quad_mesh->draw();



	}
	else
	{
		printf("no fly camera!");
	}
	
		 

	#pragma endregion


	#pragma region Camera Rendering

	//*! Draw the current frames data in the view of the camera
	if (m_fly_camera != nullptr)
	{
		//*! Fly Camera
		aie::Gizmos::draw(*m_fly_camera->get_projection_view());
	
		//*! Fly Camera update
		m_fly_camera->update((float)m_delta_time, m_window);
	}
	else
	{
		//*! No camera
		aie::Gizmos::draw(m_projection * m_view);
	}
		
	
	#pragma endregion
	
	//*! Bring forth the rendered frame and discard the old.
	glfwSwapBuffers(m_window);
}

const double MainApplication::get_delta_time()
{
	m_time.m_previousTime = m_time.m_currentTime;
	m_time.m_currentTime = m_time.m_clock.now();
	auto duration = m_time.m_currentTime - m_time.m_previousTime;
	
	//*! Delta time display
	///std::cout << duration.count() << " : " << m_delta_time << std::endl;
	
	return duration.count() * NANO_TO_SECONDS;
}

void MainApplication::game_object_matrix_setup()
{
	//*! Object matricies
	m_global_matrix = glm::mat4(1);
	m_local_matrix = glm::mat4(1);
	m_global_matrix = glm::mat4(1);

	//*! Starting positions for the 2 objects
	m_parent_matrix[3] = glm::vec4(0, 1, 10, 1);
	m_local_matrix[3] = glm::vec4(0, 0, -2, 1);

	m_global_matrix = m_parent_matrix * m_local_matrix;

	//*! slight rotation of the parent planet
	glm::mat4 rot(1);
	rot = glm::rotate(0.5f, glm::vec3(1, 0, 0));
	m_parent_matrix = m_parent_matrix * rot;
}

//*! Start the clock for time between frame calculations
void MainApplication::start_clock()
{
	m_time.m_startTime = m_time.m_clock.now();
	m_time.m_currentTime = m_time.m_clock.now();
	m_time.m_previousTime = m_time.m_clock.now();
}



 
