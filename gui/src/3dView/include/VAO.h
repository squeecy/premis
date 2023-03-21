#ifndef VAO__H
#define VAO__H

#include <glad/glad.h>

#include"vertexB.h"

class vao 
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	vao();

	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(vbo& vbo, GLuint layout, GLuint numComponents, GLenum type, 
			GLsizeiptr stride, void* offset);

	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};
#endif
