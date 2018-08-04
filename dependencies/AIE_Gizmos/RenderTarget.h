#pragma once

//*! Texture Include
#include "Texture.h"

//*! AIE NameSpace
namespace aie 
{
	//*! Render Target Class
	class RenderTarget
	{

	//*! Public Section
	public:
		//*! Default Constructor
		RenderTarget();
		//*! Overloaded Constructor
		RenderTarget(unsigned int a_targetCount, unsigned int a_width, unsigned int a_height);
		//*! Destructor
		virtual ~RenderTarget();

		//*! Start Target
		bool initialise(unsigned int a_targetCount, unsigned int a_width, unsigned int a_height);

		//*! Bind the FrameBufferObject - m_fbo
		void bind();
		//*! Clear the FrameBufferObject - set it to 0
		void unbind();

#pragma region Getters

		//*! Get Texture Width
		unsigned int	get_width() const { return m_width; }
		//*! Get Texture Height
		unsigned int	get_height() const { return m_height; }
		//*! Get the FrameBufferObject
		unsigned int	get_frame_fuffer_handle() const { return m_fbo; }
		//*! Get the Target Count
		unsigned int	get_target_count() const { return m_target_count; }
		//*! Get the Texture target
		const Texture&	get_target(unsigned int target) const { return m_targets[target]; }

#pragma endregion

	//*! Protected Section
	protected:

		//*! Texture Width
		unsigned int	m_width;
		//*! Texture Height
		unsigned int	m_height;
		//*! Frame Buffer Object
		unsigned int	m_fbo;
		//*! Render Buffer Object
		unsigned int	m_rbo;
		//*! Target Count
		unsigned int	m_target_count;
		//*! Texture Target
		Texture*		m_targets;
	};

} // namespace aie