#pragma once
#include <glm.hpp>
#include <ext.hpp>

#include "../AIE_Gizmos/tiny_obj_loader.h"
 
#include "Renderer.h"

//#include "MainApplication.h" 
//using namespace APS;
class Light;
 
class GameObject
{
public:
	
	//*!Default Constructor
	GameObject();
	
	//*! Overloaded Constructor(s)
	GameObject(const glm::mat4 a_global_matrix, const glm::mat4 a_local_matrix, const glm::mat4 a_parent_matrix, const char* a_vertex_shader, const char* a_frag_shader, const char* a_object_path);
	GameObject(const glm::mat4 a_global_matrix, const glm::mat4 a_local_matrix, const char* a_vertex_shader, const char* a_frag_shader, const char* a_object_path);
	GameObject(const glm::mat4 a_global_matrix, const char* a_vertex_shader, const char* a_frag_shader, const char* a_object_path);
	GameObject(const glm::mat4 a_global_matrix, const char* a_object_path);
	GameObject(const glm::vec4 a_global_position, const char* a_object_path);
	GameObject(const char* a_object_path);
	GameObject(const char* a_object_path, const char* a_diffuse_texture_path);
	GameObject(const char* a_object_path, const char* a_diffuse_texture_path, const char* a_normal_texture_path);
	GameObject(const char* a_object_path, const char* a_diffuse_texture_path, const char* a_normal_texture_path, const char* a_specular_texture_path);

	//*! Desctructor
	~GameObject();


	#pragma region Getters
	
		//*! Get the global transform matrix
		glm::mat4 const get_global_transform() { return m_global_matrix; };

		//*! Get the local transform matrix
		glm::mat4 const get_local_transform() { return m_local_matrix; };

		//*! Get the renderer component
		Renderer* get_renderer_component() { return m_renderer; };

	#pragma endregion

	#pragma region Setters
		
		//*! Set Local Matrix
		void set_local_transform(const glm::mat4 a_local_transform) { m_local_matrix = a_local_transform; }

		//*! Set position
		void set_position(const glm::vec4 a_position) { m_local_matrix[3] = a_position; };
 
		//*! Set scale
		void set_scale(const glm::vec3 a_scale);

		//*! Set Diffuse texture - Wrapper for the Renderer
		void set_diffuse_texture(const char * a_diffuse_texture_path);
		 
		//*! Set Light Data - Wrapper for the Renderer
		//void set_light_data(const Light& a_light_data);

		//*! Set Light Data - Wrapper for the Renderer
		void set_light_data(const std::vector<Light*> a_light_data);

	#pragma endregion

		//*! Object Draw
		void draw();

		
private:
	
	//*! Rotation Matrix - Game Object
	glm::mat4 m_global_matrix;
	glm::mat4 m_local_matrix;
	glm::mat4 m_parent_matrix;
 
	//*! Renderer Component
	Renderer* m_renderer;

	//*! Set the matricies of the game object
	void set_matricies(const glm::mat4& a_local, const glm::mat4& a_global, const glm::mat4& a_parent);
	//*! Main Default Game Object data
	void set_defaults();
};
