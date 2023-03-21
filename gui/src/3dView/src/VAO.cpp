#include"VAO.h"

// Constructor that generates a VAO ID
vao::vao()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void vao::LinkAttrib(vbo& vbo, GLuint layout, GLuint numComponents, GLenum type, 
			GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

// Binds the VAO
void vao::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void vao::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void vao::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
