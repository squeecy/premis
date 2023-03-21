#ifndef SHADER__H
#define SHADER__H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Vertex Shader source code

static GLuint shaderProgram;
static GLuint VAO, VBO, EBO;

std::string getfileContents(const char* filename);




class Shader
{
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();
};

#endif
