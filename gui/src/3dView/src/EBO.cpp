#include "EBO.h"

ebo::ebo(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ebo::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ebo::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}


void ebo::Delete()
{
	glDeleteBuffers(1, &ID);
}
