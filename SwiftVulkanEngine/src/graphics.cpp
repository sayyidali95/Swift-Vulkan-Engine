#include "graphics.h"

namespace sa3d {
	namespace graphics {



		void window_resize(GLFWwindow *window, int width, int height);

		/*Get GLFW window called*/
		Window::Window(GLFWwindow *window, const char *title, int width, int height)
		{
			m_Window = window;
			m_Title = title;
			m_Width = width;
			m_Height = height;

			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}
		Window::~Window()
		{
			vkDestroyInstance(instance, nullptr);

			//glfwDestroyWindow(m_Window);

			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);






		
			return true;

		}

		void Window::initVulkan()
		{
			createInstance();
			setupDebugCallback();



		}

		void Window::setupDebugCallback() {
			if (!enableValidationLayers) return;

		}

		//create vulkan instance
		void Window::createInstance() {
			/* Get application info and print to console*/
			if (enableValidationLayers && !checkValidationLayerSupport()) {
				throw std::runtime_error("validation layers requested, but not available!");
			}

			VkApplicationInfo appInfo = {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hello Triangle";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			/* Get instance info and print to console */
			VkInstanceCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			// get glfw extensions
			auto extensions = getRequiredExtensions();

			createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			createInfo.ppEnabledExtensionNames = extensions.data();

			createInfo.enabledLayerCount = 0;

			VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

			//Initialization error checking
			if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
			{
				throw std::runtime_error("failed to create Vulkan instance!");
			}

			//check  Vulkan extension info
			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

			

			

			//Check Vulkan validation layer info
			if (enableValidationLayers) {
				createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
				createInfo.ppEnabledLayerNames = validationLayers.data();
			}
			else {
				createInfo.enabledLayerCount = 0;
			}

			// list extensions
			std::cout << "available extensions:" << std::endl;

			


		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			//TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			//TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::clear() const
		{
			//glClearColor(0.2f, 0.3f, 0.3f, 0.7f);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}


		void Window::update()
		{


			glfwSwapBuffers(m_Window);
			glfwPollEvents();
			//			glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);

		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			//glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;

			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, 1);
			if (key >= 0 && key < 1024)
			{
				if (action == GLFW_PRESS)
					win->m_Keys[key] = true;
				else if (action == GLFW_RELEASE)
					win->m_Keys[key] = false;
			}
		}
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}


		bool Window::checkValidationLayerSupport() {
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			for (const char* layerName : validationLayers) {
				bool layerFound = false;

				for (const auto& layerProperties : availableLayers) {
					if (strcmp(layerName, layerProperties.layerName) == 0) {
						layerFound = true;
						break;
					}
				}

				if (!layerFound) {
					return false;
				}
			}

			return true;

		}

		//get required extensions
		std::vector<const char*> Window::getRequiredExtensions() {
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

			if (enableValidationLayers) {
				extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			}

			return extensions;
		}

		//callbacks for vulkan debug
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData) {

			std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

			return VK_FALSE;
		}





	}
}