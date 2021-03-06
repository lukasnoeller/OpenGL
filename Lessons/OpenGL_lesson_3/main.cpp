#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";
int main()
{
	glfwInit();
	// Tell what version of glfw is used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW that CORE profile is used (contains modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//vertices coordinates 
	GLfloat vertices[] =
	{
		-0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f, //Lower left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right vertex
		0.0f, 0.5f * float(sqrt(3))  / 3, 0.0f, // Center upper vertex
		float(-0.5 / 2), 0.0f, 0.0f, // Middle left vertex
		float(0.5 / 2), 0.0f, 0.0f, // Middle right vertex
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		//Lower middle vertex
		

	};
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle 
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};
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
// Specifies viewport of OpenGL iin the Window
// goes from 0,0 to 800,800
	glViewport(0, 0, 800, 800);
	// create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader source to vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach fragment shader source to fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO,VBO,EBO;
	
	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);
	
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//Swap back buffer with front buffer
	glfwSwapBuffers(window);
	//while loop
	while (!glfwWindowShouldClose(window))
	{
		// Change color of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT,0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		//process all GLFW events
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}