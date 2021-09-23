#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	glfwInit();
	// Tell what version of glfw is used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW that CORE profile is used (contains modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Initialization
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	
	// Error Handling
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 
	// makes the context window current---->i.e. displays it
	glfwMakeContextCurrent(window);
	// Load GLAD so it configures OpenGL
	gladLoadGL();
// SPecifies viewport of OpenGL iin the Window
// goes from 0,0 to 800,800
	glViewport(0, 0, 800, 800);

	// Change color of background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clear back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
//Swap back buffer with front buffer
	glfwSwapBuffers(window);
	//while loop
	while (!glfwWindowShouldClose(window))
	{
		

		
		//process all GLFW events
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}