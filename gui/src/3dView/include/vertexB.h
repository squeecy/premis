#ifndef VERTEXB__H 
#define VERTEXB__H

#include<glad/glad.h>

class vbo
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	vbo(GLfloat* vertices, GLsizeiptr size);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif
