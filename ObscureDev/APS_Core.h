//*! Base Core for all components to include?
#pragma once
//*! Time
#include <chrono>
#include <glm.hpp>
#include <ext.hpp>

#include "../glCore/gl_core_4_5.h"
#include <glfw3.h>

#include "Gizmos.h"
#include "../AIE_Gizmos/Input.h"

#include "../AIE_Gizmos/OBJMesh.h" 
#include "../AIE_Gizmos/Shader.h"
#include "../AIE_Gizmos/tiny_obj_loader.h"

#include <vector>


#pragma region TypeDef shortcuts

//*! Time - Clock and duration aliasing
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;
//*! Expected use: seconds = nanoseconds * NANO_TO_SECONDS;
static const double NANO_TO_SECONDS = 0.000000001;//8 Zeros before the 1
												  //*! Expected use: nanoseconds = seconds * NANO_TO_SECONDS;
static const ullong NANO_IN_SECONDS = 1000000000ULL;//9 Zeros after the 1

#pragma endregion

				
//*! Initial Namepace
namespace APS
{

	#pragma region Clock - Time

		using clock = std::chrono::high_resolution_clock;
		using time = std::chrono::time_point<clock>;


		struct custom_time
		{
			APS::clock m_clock;
			APS::time m_startTime;
			APS::time m_currentTime;
			APS::time m_previousTime;
		};

	#pragma endregion
 



}