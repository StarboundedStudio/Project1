#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "stb/stb_image.h"

#include"shaderClass.h"
#include"VAO.h"
#include"EBO.h"
#include"VBO.h"

// Vertices coordinates
GLfloat vertices[] =
{ //                COORDINATES            /       COLORS             //
	-0.5f,  -0.5f * float(sqrt(3))     / 3, 0.0f, 0.8f, 0.3f,  0.02f, // Lower Left Corner
	0.5f,   -0.5f * float(sqrt(3))     / 3, 0.0f, 0.8f, 0.3f,  0.02f, // Lower Right Corner
	0.0f,   0.5f  * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f,  0.32f, // Upper Corner
	-0.25f, 0.5f  * float(sqrt(3))     / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner Left Corner
	0.25f,  0.5f  * float(sqrt(3))     / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner Right Corner
	0.0f,   -0.5f  * float(sqrt(3))     / 3, 0.0f, 0.8f, 0.3f,  0.02f  // Inner Down Corner 
};

GLuint indices[] =
{
	0, 3, 5, // Lower Left Triangle
	3, 2, 4, // Lower Right Triangle
	5, 4, 1 // Upper Triangle
};

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Project1"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Project1", NULL, NULL);
	//Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		// Bind the VAO so OpenGl knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete all the object we've created
	VAO1.Delete();
	EBO1.Delete();
	VAO1.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminates GLFW before the program ends
	glfwTerminate();
	return 0;
}