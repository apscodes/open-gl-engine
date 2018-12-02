#include "Renderer.h"
#include "GameObject.h"
#include "MainApplication.h"
#include "Shader.h"
#include "Light.h"

Renderer::Renderer() : m_game_object(), m_mesh(), m_fly_camera(), m_vertex_shader("../bin/shaders/main.vert"), m_frag_shader("../bin/shaders/main.frag")
{
	//*! New Shader
	m_shader = new  aie::ShaderProgram();

	//*! New Textures for all
	m_diffuse_texture				   = new aie::Texture();
	m_alpha_texture					   = new aie::Texture();
	m_ambient_texture				   = new aie::Texture();
	m_specular_texture				   = new aie::Texture();
	m_specular_highlight_texture	   = new aie::Texture();
	m_normal_texture				   = new aie::Texture();
	m_displacement_texture			   = new aie::Texture();

	//*! New Material Component
	m_material = new aie::OBJMesh::Material();

	//*! 
	//if (m_render_target.initialise(1, 1280, 720) == false)
	//{
	//	printf("Render Target Error!\n");
	//}
} 

//*! Deconstructor 
Renderer::~Renderer()
{
	if (m_shader != nullptr)
		delete m_shader;

	
	if (m_diffuse_texture != nullptr)
		delete m_diffuse_texture;

	
	if (m_alpha_texture != nullptr)
		delete m_alpha_texture;

	
	if (m_ambient_texture != nullptr)
		delete m_ambient_texture;


	if (m_specular_texture != nullptr)
		delete m_specular_texture;


	if (m_specular_highlight_texture != nullptr)
		delete m_specular_highlight_texture;
	
	
	if (m_normal_texture != nullptr)
		delete m_normal_texture;
	
	
	if (m_displacement_texture != nullptr)
		delete m_displacement_texture;


	if (m_material != nullptr)
		delete m_material;
}

void Renderer::draw()
{
	//*! Bind the Render target
	//m_render_target.bind();

	glClearColor(0.85f, 0.85f, 0.85f, 1);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//*! Bind the object shader
	m_shader->bind();

	//*! Lighting data
	///m_shader->bindUniform("Light_Direction",	 m_light.m_direction);
	///m_shader->bindUniform("Light_Ambient",		 m_light.m_ambient_light);
	///m_shader->bindUniform("Light_Diffuse",		 m_light.m_diffuse);
	///m_shader->bindUniform("Light_Specular",		 m_light.m_specular);
	///m_shader->bindUniform("Specular_Power", 0.5f);
	
	//For all lights set and bind them to the object
	for (int index = 0; index < m_lights.size(); index++)
	{
		//Configure strings
		std::string l_direction = "m_lights[" + std::to_string(index) + "].Light_Direction";
		std::string l_ambient = "m_lights[" + std::to_string(index) + "].Light_Ambient";
		std::string l_diffuse = "m_lights[" + std::to_string(index) + "].Light_Diffuse";
		std::string l_specular = "m_lights[" + std::to_string(index) + "].Light_Specular";

		//*! Bind the uniforms for the object
		m_shader->bindUniform(l_direction.c_str(), m_lights[index]->get_direction());
		m_shader->bindUniform(l_ambient.c_str(), m_lights[index]->get_ambient());
		m_shader->bindUniform(l_diffuse.c_str(), m_lights[index]->get_diffuse());
		m_shader->bindUniform(l_specular.c_str(), m_lights[index]->get_specular());
	}





	//*! Texture Uniforms
	m_shader->bindUniform("Normal_Matrix", glm::inverseTranspose(glm::mat3(m_game_object->get_local_transform())));
	
	//*! Bind the Camera Position 
	m_shader->bindUniform("Camera_Position", glm::vec3(glm::inverse(*m_fly_camera.get_view())[3]));

	//*! RenderTarget
	///m_render_target.unbind();

	///glClearColor(0.45f, 0.45f, 0.45f, 1);

	//*! Bind the texture(s) to the object
	bind_all_textures();


	//*! Projection View Model
	//*! Bind the transform to the object
	auto m_pvm = *m_fly_camera.get_projection() *  *m_fly_camera.get_view() *  m_game_object->get_local_transform();
	//*! Binding the (expecting glm::mat4) into the shader using the 'ProjectionViewModel'
	m_shader->bindUniform("ProjectionViewModel", m_pvm);
	//*! Base Diffuse Colour if no texture
	m_shader->bindUniform("Kd", glm::vec3(1.0f, 0.0f, 1.0f));

	//*! RenderTarget
	///m_render_target.get_target(0).bind(0);


	//*! Mesh draw
	m_mesh.draw();

}

//*! Set the mesh data for the object
bool Renderer::set_mesh(const std::string a_file_path, const bool a_load_textures, const bool a_flip_texture)
{
	//*! Loading in a mesh via the file path
	if (!m_mesh.load(a_file_path.c_str(), a_load_textures, a_flip_texture))
	{
		printf("Failed to load the mesh! check the params and try again.");
		return false;
	}
	else
	{
		return true;
	}
}

//*! Set the shader that it renderers with
bool Renderer::set_shader(const aie::eShaderStage a_shader_type, const std::string a_file_path)
{
	if (m_shader != nullptr)
	{
		//*! Loading the shader via the file path
		if (!m_shader->loadShader(a_shader_type, a_file_path.c_str()))
		{
			printf("Failed to load the shader! check the params and try again.");
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		printf("Shader was nullptr.\n\n");
		return false;
	}
}

//*! Set the texture for the object
bool Renderer::set_texture(aie::Texture& a_texture, const char * a_file_path)
{
	if (&a_texture != nullptr)
	{
		//*! Load Texture by file path.
		if (!a_texture.load(a_file_path))
		{
			printf("Failed to load in the texture.\n\n");
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		printf("Texture was nullptr.\n\n");
		return false;
	}
}

//*! Bind the shader to the object
void Renderer::bind_shader()
{
	if (m_shader != nullptr)
	{
		//*! Linking Error check
		if (m_shader->link() == false)
		{
			printf("Shader Error: %s\n", m_shader->getLastError());
			return;
		}
	}
	else
	{
		printf("Shader was nullptr.\n\n");
		return;
	}
}

//*! Not sure if needed
void Renderer::set_all_material()
{
	//*! Nullptr Check
	if (m_material != nullptr)
	{
		//*! Nullptr Check
		if (m_diffuse_texture != nullptr)
			m_material->diffuseTexture = *m_diffuse_texture;
		else
		{
			printf("m_diffuse_texture was nullptr");
		}
	

		//*! Nullptr Check
		if (m_alpha_texture != nullptr)
			m_material->alphaTexture = *m_alpha_texture;
		else
		{
			printf("m_alpha_texture was nullptr");
		}

		//*! Nullptr Check
		if (m_ambient_texture != nullptr)
			m_material->ambientTexture = *m_ambient_texture;
		else
		{
			printf("m_ambient_texture was nullptr");
		}

		//*! Nullptr Check
		if (m_specular_texture != nullptr)
			m_material->specularTexture = *m_specular_texture;
		else
		{
			printf("m_specular_texture was nullptr");
		}

		//*! Nullptr Check
		if (m_specular_highlight_texture != nullptr)
			m_material->specularHighlightTexture = *m_specular_highlight_texture;
		else
		{
			printf("m_specular_highlight_texture was nullptr");
		}
		//*! Nullptr Check
		if (m_normal_texture != nullptr)
			m_material->normalTexture = *m_normal_texture;
		else
		{
			printf("m_normal_texture was nullptr");
		}
		//*! Nullptr Check
		if (m_displacement_texture != nullptr)
			m_material->displacementTexture = *m_displacement_texture;
		else
		{
			printf("m_displacement_texture was nullptr");
		}

	}
	else
	{
		printf("m_material was nullptr");
	}
}

//*! Bind All textures to the object
void Renderer::bind_all_textures()
{
	//*! Nullptr Check
	if (m_diffuse_texture != nullptr)
		m_diffuse_texture->bind(0); 
	else
	{
		printf("m_diffuse_texture was nullptr");
	}
		
	
	//*! Nullptr Check
	if (m_alpha_texture != nullptr)
		m_alpha_texture->bind(1);
	else
	{
		printf("m_alpha_texture was nullptr");
	}

	//*! Nullptr Check
	if (m_ambient_texture != nullptr)
		m_ambient_texture->bind(2);
	else
	{
		printf("m_ambient_texture was nullptr");
	}

	//*! Nullptr Check
	if (m_specular_texture != nullptr)
		m_specular_texture->bind(3);
	else
	{
		printf("m_specular_texture was nullptr");
	}

	//*! Nullptr Check
	if (m_specular_highlight_texture != nullptr)
		m_specular_highlight_texture->bind(4);
	else
	{
		printf("m_specular_highlight_texture was nullptr");
	}
	//*! Nullptr Check
	if (m_normal_texture != nullptr)
		m_normal_texture->bind(5);
	else
	{
		printf("m_normal_texture was nullptr");
	}
	//*! Nullptr Check
	if (m_displacement_texture != nullptr)
		m_displacement_texture->bind(6);
	else
	{
		printf("m_displacement_texture was nullptr");
	}
}
