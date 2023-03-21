#include "VertexB.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
vbo::vbo(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void vbo::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void vbo::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void vbo::Delete()
{
	glDeleteBuffers(1, &ID);
}
