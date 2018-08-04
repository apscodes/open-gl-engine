#pragma once

//*! Light Data
#include "Light.h"
//*! Texture
#include "Texture.h"
//*! Shader 
#include "../AIE_Gizmos/Shader.h"
//*! Mesh Data
#include "../AIE_Gizmos/OBJMesh.h"
//*! Camera - Target
#include "FlyCamera.h"
//*! RenderTarget
#include "RenderTarget.h"
//*! Typedef Defines 
#include "APS_Core.h"
//*! GameObject - Forward Dec
class GameObject;


class Renderer
{
public:
	Renderer();
	~Renderer();

	virtual void draw();

	#pragma region Getters

		//*! Get a reference of the private shader
		aie::ShaderProgram* get_shader() { return m_shader; };
		//*! Get a reference of the private mesh
		aie::OBJMesh& get_mesh() { return m_mesh; };
		//*! Get the Light_Data
		std::vector<Light*>& get_light_data() { return m_lights; };
		//*! Get a reference of the private texture
		aie::Texture* get_diffuse_texture() { return m_diffuse_texture; };
		//*! Default Shader(s)
		std::string get_default_vertex_shader() { return m_vertex_shader.c_str(); };
		std::string get_default_frag_shader() { return m_frag_shader.c_str(); };
		//*! Get Material
		aie::OBJMesh::Material* get_material() { return m_material; }

	#pragma endregion


	#pragma region Setters

		//*! Set the mesh
		bool set_mesh(const std::string a_file_path, const bool a_load_textures, const bool a_flip_texture);
		//*! Set the shader
		bool set_shader(const aie::eShaderStage a_shader_type, const std::string a_file_path);
		//*! Set Combined Texture
		bool set_texture(aie::Texture& a_texture, const char* a_file_path);
		//*! Bind the shader
		void bind_shader();
		//*! Set the Camera Data
		void set_camera(const FlyCamera& a_fly_camera) { m_fly_camera = a_fly_camera; };
		//*! Set Base Camera
		void set_camera(const Camera& a_camera) { m_fly_camera = a_camera; };
		//*! Set the lighing data
		//void set_light_data(const Light& a_light_data) { m_light = a_light_data; };
		//*! Set the lighing data - Overloaded
		void set_light_data(const std::vector<Light*> a_light_data) { m_lights = a_light_data; };
 		//*! Set the target game object
		void set_target_game_object(GameObject* a_game_object) { m_game_object = a_game_object; }
		//*! Set the mesh's material texture
		void set_all_material();
		//*! Bind All textures
		void bind_all_textures();

	#pragma endregion

private:

	//*! Game Object Reference - Positional Data
	GameObject* m_game_object;

	//*! Mesh
	aie::OBJMesh m_mesh;

	//*! OBJMesh Material Data
	aie::OBJMesh::Material* m_material;
	//*! Texture Data - Maps
	aie::Texture* m_diffuse_texture;			//*! bound slot 0
	aie::Texture* m_alpha_texture;				//*! bound slot 1
	aie::Texture* m_ambient_texture;			//*! bound slot 2
	aie::Texture* m_specular_texture;			//*! bound slot 3
	aie::Texture* m_specular_highlight_texture;	//*! bound slot 4
	aie::Texture* m_normal_texture;				//*! bound slot 5
	aie::Texture* m_displacement_texture;		//*! bound slot 6
	
	//*! Shader
	aie::ShaderProgram* m_shader;
	//*! Defaults
	std::string m_vertex_shader;
	std::string m_frag_shader;


	//*! Camera Data
	Camera m_fly_camera;

	//*! Light Data
	Light m_light;
	std::vector<Light*> m_lights;

	//*! Render Target
	aie::RenderTarget m_render_target;


};

