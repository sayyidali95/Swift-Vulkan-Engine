
#include "graphics.h"
#include "camera.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
using namespace sa3d;
using namespace graphics;
using namespace glm;





GLFWwindow *w;
// Camera Properties
// Window dimensions
const GLuint screenWidth = 960, screenHeight = 540;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


int main() {
	Window window(w, "Swift Vulkan Engine", screenWidth, screenHeight);
	Window* pWindow = &window;

	

	std::cout << window.extensionCount << " extensions supported" << std::endl;

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	while (!glfwWindowShouldClose(window.m_Window)) {
		glfwPollEvents();
	}

	window.closed();

	glfwTerminate();

	return 0;
}