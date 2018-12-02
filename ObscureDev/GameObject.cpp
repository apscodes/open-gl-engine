#include "GameObject.h"
#include "Light.h"

//*! Default constructor while setting up the member variables
GameObject::GameObject() : m_global_matrix(glm::mat4(0)), m_local_matrix(glm::mat4(0)), m_parent_matrix(glm::mat4(0))
{
	m_renderer = new Renderer();
}

//*! Matrix values, ver - frag shader, obj model, texture
GameObject::GameObject(const glm::mat4 a_global_matrix, const glm::mat4 a_local_matrix, const glm::mat4 a_parent_matrix, const char* a_vertex_shader, const char* a_frag_shader, const char* a_object_path)
{

	//*! Set the defaults - Until Overriden
	set_defaults();

 	//*! Set the maticies for the game object
	set_matricies(a_local_matrix, a_global_matrix, a_parent_matrix);
	
	//*! Vertex Shader
	m_renderer->set_shader(aie::eShaderStage::VERTEX, a_vertex_shader);
	
	//*! Fragment Shader
	m_renderer->set_shader(aie::eShaderStage::FRAGMENT, a_frag_shader);
 
	//*! Bind the shaders
	m_renderer->bind_shader();

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true , true);

}

//*! Matrix values, vert - frag shader, obj file - rest handled by defaults
GameObject::GameObject(const glm::mat4 a_global_matrix, const glm::mat4 a_local_matrix, const char * a_vertex_shader, const char * a_frag_shader, const char * a_object_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();
	
	//*! Set the maticies for the game object
	set_matricies(a_local_matrix, a_global_matrix, glm::mat4(0));

	//*! Vertex Shader
	m_renderer->set_shader(aie::eShaderStage::VERTEX, a_vertex_shader);

	//*! Fragment Shader
	m_renderer->set_shader(aie::eShaderStage::FRAGMENT, a_frag_shader);

	//*! Bind the shaders
	m_renderer->bind_shader();

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);
}

//*! Matrix values, vert - frag shader, obj file - rest handled by defaults
GameObject::GameObject(const glm::mat4 a_global_matrix, const char * a_vertex_shader, const char * a_frag_shader, const char * a_object_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();

	//*! Set the maticies for the game object
	set_matricies(glm::mat4(1), a_global_matrix, glm::mat4(0));

	//*! Vertex Shader
	m_renderer->set_shader(aie::eShaderStage::VERTEX, a_vertex_shader);

	//*! Fragment Shader
	m_renderer->set_shader(aie::eShaderStage::FRAGMENT, a_frag_shader);

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);
}

//*! Matrix Value - Global Matrix, model to load in - rest handled by defaults
GameObject::GameObject(const glm::mat4 a_global_matrix, const char * a_object_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();
	
	//*! Set the maticies for the game object
	set_matricies(glm::mat4(1), a_global_matrix, glm::mat4(0));

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);
}

//*! Vec4 Position values, model to load in - rest handled by defaults
GameObject::GameObject(const glm::vec4 a_global_position, const char * a_object_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();

	//*! Set the position in world space
	set_position(a_global_position);

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);
}

//*! Model to load in - rest handled by defaults
GameObject::GameObject(const char * a_object_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);
}

GameObject::GameObject(const char * a_object_path, const char * a_diffuse_texture_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);

	//*! Set the diffuse texture
	set_diffuse_texture(a_diffuse_texture_path);
}	


GameObject::GameObject(const char * a_object_path, const char * a_diffuse_texture_path, const char * a_normal_texture_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);

	//*! Set the diffuse texture
	set_diffuse_texture(a_diffuse_texture_path);

	//*! Set the normal texture
	//set_normal_texture(a_normal_texture_path);
}

GameObject::GameObject(const char * a_object_path, const char * a_diffuse_texture_path, const char * a_normal_texture_path, const char * a_specular_texture_path)
{
	//*! Set the defaults - Until Overriden
	set_defaults();

	//*! Set the mesh
	m_renderer->set_mesh(a_object_path, true, true);

	//*! Set the diffuse texture
	set_diffuse_texture(a_diffuse_texture_path);

	//*! Set the normal texture
	//set_normal_texture(a_normal_texture_path);

	//*! Set the specular texture
	//set_specular_texture(a_specular_texture_path);
}
 

//*! Deconstructor
GameObject::~GameObject()
{
	if (m_renderer != nullptr)
		delete m_renderer;
}

//*! Set the scale of the object
void GameObject::set_scale(const glm::vec3 a_scale)
{
	m_local_matrix[0][0] = a_scale.x;
	m_local_matrix[1][1] = a_scale.y;
	m_local_matrix[2][2] = a_scale.z;
}

//*! Wrapper for the Renderer class - set_diffuse_texture
void GameObject::set_diffuse_texture(const char * a_diffuse_texture_path)
{
	//*! Check the diffuse texture isnt nullptr
	if (m_renderer->get_diffuse_texture() != nullptr)
	{
		//*! Assign the texture with the path
		m_renderer->set_texture(*m_renderer->get_diffuse_texture(), a_diffuse_texture_path);
	}
}


void GameObject::set_light_data(const std::vector<Light*> a_light_data)
{
	//*! Check the Light data isnt nullptr
	if (&m_renderer->get_light_data() != NULL)
	{
		//*! Assign Light Data to the renderer
		m_renderer->set_light_data(a_light_data);
	}
}


//*! Draws the object
void GameObject::draw()
{
	//*! Renderer Component - Draw
	m_renderer->draw();
}

void GameObject::set_matricies(const glm::mat4 & a_local, const glm::mat4 & a_global, const glm::mat4 & a_parent)
{
	//*! If not blank / empty mat4
	if (a_local != glm::mat4(0))
		m_local_matrix = a_local;

	//*! If not blank / empty mat4
	if (a_global != glm::mat4(0))
		m_global_matrix = a_global;

	//*! If not blank / empty mat4
	if (a_parent != glm::mat4(0))
		m_parent_matrix = a_parent;
}

void GameObject::set_defaults()
{
	//*! Set the maticies for the game object
	set_matricies(glm::mat4(1), glm::mat4(0), glm::mat4(0));

	//*! New Renderer component - used in the default constructor
	m_renderer = new Renderer();

	//*! Vertex Shader - Default Shader
	m_renderer->set_shader(aie::eShaderStage::VERTEX, m_renderer->get_default_vertex_shader());

	//*! Fragment Shader - Default Shader
	m_renderer->set_shader(aie::eShaderStage::FRAGMENT, m_renderer->get_default_frag_shader());

	//*! Bind the shaders
	m_renderer->bind_shader();

	//*! Set the renderer game object target to this
	m_renderer->set_target_game_object(this);

	float offset = (float)std::rand();
	offset / 100000;
	int minus = (int)offset;
	offset - minus;
	rot = offset;
}


 
 


