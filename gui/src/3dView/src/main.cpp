#include <stdio.h>
#include <tchar.h>
#include <string>
#include <cmath>
#include <iostream>
#include "shader.h"
#include "VAO.h"
#include "vertexB.h"
#include "EBO.h"
#include "serialread.h"
#include "record.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define M_PI 3.14159265358979323846
//window constants
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

//vertices and indices for drawing pyramid
GLfloat vertices[] =
{
	-0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
	 0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,
	 0.0f, 0.8f, 0.0f,      0.93f, 0.86f, 0.76f
};

GLuint indices[] =
{
	0, 1 ,2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};



int main() {

	int usrInput; //hold user input for either mode

	serialData_T DATA; //struct init
	replayData rData;
	glfwInit(); //init glfw

	// check for user input
	std::cout << "Select '0' for live view, select '1' for replay" << std::endl;
	std::cin >> usrInput;

	//do either depending on user input
	if(usrInput == 1){fillData(std::ifstream("../bin/output.txt"),&rData);};
	std::ofstream inFile("../bin/output.txt");

	//specify opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//create window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3d View Telemetry", NULL, NULL);

	if(window == NULL)
	{
		std::cout << "Window Creation Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //tell glfw to use window

	gladLoadGL(); //load openGL configs
	glViewport(0, 0, WIDTH, HEIGHT); //where to display the pixels


	//direct to shaders
	Shader shaderProgram("../resources/default.vert", "../resources/default.frag");
	
	// display vao, vbo, ebo
	vao VAO1;
	VAO1.Bind();

	vbo VBO1(vertices, sizeof(vertices));
	ebo EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	while(!glfwWindowShouldClose(window))
	{
		serialRead(&DATA); //read serial input

		if(usrInput == 0){inFile << std::to_string(DATA.roll) << std::endl;} //print input to file

		glClearColor(26.0f/255, 36.0f/255, 48.0f/255, 1.0f); //display color
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();

		//drawCircle(WIDTH/2, HEIGHT/2, 0, 120);
		glm::mat4 model_pitch = glm::mat4(1.0f); //pitch model matrix
		glm::mat4 model_roll = glm::mat4(1.0f); //roll model matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		
		//rotate pitch
		if(usrInput == 0)
		{
			model_pitch = glm::rotate(model_pitch, glm::radians(DATA.pitch), glm::vec3(1.0f, 0.0f, 0.0f));
			model_roll= glm::rotate(model_roll, glm::radians(DATA.roll), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else
		{
			model_pitch = glm::rotate(model_pitch, glm::radians((float)rData.pitch[0]), glm::vec3(1.0f, 0.0f, 0.0f));
			model_roll= glm::rotate(model_roll, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}

		//pass names to shaders
		int modelLoc_pitch = glGetUniformLocation(shaderProgram.ID, "model_pitch");
		glUniformMatrix4fv(modelLoc_pitch, 1, GL_FALSE, glm::value_ptr(model_pitch));

		int modelLoc_roll = glGetUniformLocation(shaderProgram.ID, "model_roll");
		glUniformMatrix4fv(modelLoc_roll, 1, GL_FALSE, glm::value_ptr(model_roll));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents(); //process events
	}

	//clean up
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	serialDisconnect();
	if(usrInput == 0){inFile.close();}


	glfwDestroyWindow(window);  //close the window
	glfwTerminate(); //end glfw

    return 0;
}
