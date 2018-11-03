#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE


#include <iostream>
#include <vector>



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

namespace sa3d {


	/**
	* @brief initialize the 3d graphics system using Vulkan and GLFW
	
	*/


namespace graphics {

#define MAX_KEYS		1024
#define MAX_BUTTONS		32

	/**
	@brief Window class to upen up a window for display purposes
	@param m_Window used to have the window's current context
	@param m_Width width of screen window
	@param m_Height height of the screen window
	@param m_Title pointer to the title of the screen window
	@return Window containing the main viewport of the game
	
	*/



			class Window
			{

			private:
				friend struct GLFWwindow;
				VkInstance instance;
				const char *m_Title;
				int m_Width, m_Height;
				bool m_Closed;
				VkDebugUtilsMessengerEXT callback;		//Vulkan callback



				/*Define Keys and buttons*/
			public:
				GLFWwindow *m_Window;
				bool m_Keys[MAX_KEYS];
				bool m_MouseButtons[MAX_BUTTONS];
				double mx, my;
				uint32_t extensionCount = 0;			/** extensions supported*/



				/*Window Functions*/
				Window(GLFWwindow *window, const char *name, int width, int height);
				~Window();
				void clear() const;
				void update();
				bool closed() const;

				/*Screen Width*/
				int getWidth() const { return m_Width; }
				int getHeight() const { return m_Height; }

				/*Key is Pressed*/
				bool isKeyPressed(unsigned int keycode) const;
				bool isMouseButtonPressed(unsigned int button) const;
				void getMousePosition(double& x, double& y) const;
				void doMovement();

				/*Vulkan Debug*/
				bool checkValidationLayerSupport();
				void setupDebugCallback();
				std::vector<const char*> Window::getRequiredExtensions();  //get extensions in vulkan

			private:
				bool init();
				/*init Vulkan*/
				void initVulkan();
				void createInstance();

				/*Input Callbacks*/
				friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
				friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
				friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);



			};


		}
}