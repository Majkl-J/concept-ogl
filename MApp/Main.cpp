//These guys are really important, don't touch
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//You can touch these
// 
// Custom header files
#include "shaderClass.h"	//Shader Class
#include "textureClass.h"	//Tex class
#include "VAO.h"	// Vector Array Object
#include "VBO.h"	// Vector Buffer Object
#include "EBO.h"	// Element Buffer Object

// The STB texture tool
// Will make own version once I figure out png headers
#include <stb/stb_image.h>


//Define vertices
GLfloat vertices[] =
{
	//  COORDINATES									/		COLORS		/	/ TEXTURE COORDS //
		-0.5f,	-0.5f,	0.0f,						0.8f, 0.2f, 0.0f,			0.0f, 0.0f,		// Lower left corner
		-0.5f,	 0.5f,	0.0f,						0.8f, 0.2f, 0.0f,			0.0f, 1.0f,		// Upper left corner
		 0.5f,	 0.5f,	0.0f,						0.6f, 0.6f, 1.0f,			1.0f, 1.0f,		// Upper right corner
		 0.5f,	-0.5f,	0.0f, 						0.8f, 0.2f, 0.0f,			1.0f, 0.0f,		// Lower left corner
};
// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1,	// Upper triangle
	0, 3, 2		// Lower Triangle
};



int main() {
	int w = 720;
	int h = 720;
	//initialize glfw
	glfwInit();

	//tell glfw what version im using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell glfw that im using profile CORE
	//No old functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a glfw window 
	GLFWwindow* window = glfwCreateWindow(w, h, "M-Application Framework", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Add window to context
	glfwMakeContextCurrent(window);

	//Tell glad to load and configure ogl
	gladLoadGL();

	//Specify the viewport size for ogl
	glViewport(0, 0, w, h);


	//Link shaders

	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attribs (coords, colors) to VAO
	// !!!!! REMEMBER TO EDIT EACH TIME I CHANGE THE ATTRIBUTES !!!!!
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Get ID of the scale uniform for scaling vectors
	GLuint uniScale = glGetUniformLocation(shaderProgram.ID, "scale");




	// TEXTURE STUFF
	Texture denis("Denis_Texture.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

	denis.texUnit(shaderProgram, "tex0", 0);







	// -----------MAIN WHILE LOOP-------------
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assign Value to uniScale
		glUniform1f(uniScale, 0.1f);
		//Bind the 2D texture
		denis.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	denis.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}