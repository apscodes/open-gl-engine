//*! Printing to console.
#include <iostream>
//*! Memory Checker
#include <crtdbg.h>
//*! Base application
#include "MainApplication.h"
///*! Main Camera 
///#include "FlyCamera.h"



#pragma region Commenting Style Guide

	//*! Single line comments

	/*!
	 *	Multi line comments
	 *
	 !*/

	 // Temporary comments

	/// Temperary not needed - revise over it to see if it's needed.

	/*!
		@brief		Desciption of the function
		@params		a_args_name - description
		@params		a_args_name - description
		@return		void
	!*/

#pragma endregion
 
 
int main()
{
	//*! Memory Checker
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout << "Start of the program." << std::endl;

	//*! MainApplication* main_app = new MainApplication();
	///*! or	Either one will create an application window
 
	MainApplication* main_app = new MainApplication(glm::ivec2(1280,720), "Open GL Engine - ObscureDev", nullptr, nullptr);


	//*! nullptr check 
	///AND if the startup process worked && main_app->startup() == 0
	if (main_app != nullptr)
	{
		//*! While the Update results to true
		while (main_app->update())
		{
			//*! Draw the mainApp While it is working
			main_app->draw();
		}
		//*! When the update return false
		main_app->shutdown();
	}
	else
	{
		delete main_app;
	}
			
 
	//*! Clean up
	delete main_app;
	 

	return 0;
}


