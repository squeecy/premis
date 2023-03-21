#ifndef EBO_CLASS__H
#define EBO_CLASS__H 

#include <glad/glad.h>


class ebo 
{
public:
	GLuint ID;

	ebo(GLuint* indices, GLsizeiptr size);

	void Bind();

	void Unbind();

	void Delete();
};

#endif
