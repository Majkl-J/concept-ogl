#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
	public:
		// Reference ID of the Texture Program
		GLuint ID;
		// 
		GLenum type;

		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		void texUnit(Shader& shader, const char* uniform, GLuint unit);

		// Binds the Texture Program
		void Bind();
		// UnBinds the Texture Program
		void Unbind();
		// Deletes the Texture Program
		void Delete();
};

#endif