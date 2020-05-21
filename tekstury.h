#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <string>
#include <glm.hpp>
#include <string>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <fstream>
#include<SOIL2.h>

class Texture
{
private:
	GLuint tex;
	int width;
	int height;
	
	unsigned int type;






public:
	Texture(const char* filename, GLenum type) 
	{
		this->type = type;
		
		unsigned char* image = SOIL_load_image(filename, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
		glGenTextures(1, &this->tex);
		glBindTexture(type, this->tex);


		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (image) {
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);


		}
		else
		{
			std::cout << "bald tekstury 1";
		}

		glActiveTexture(0);
		glBindTexture(type, 0);
		SOIL_free_image_data(image);

	}


	~Texture()
	{
		glDeleteTextures(1 , &this->tex);

	}

	inline GLuint getid() const { return this->tex; }


	void bind(const GLint texture)
	{

		glActiveTexture(GL_TEXTURE0 + texture);
		glBindTexture(this->type, this->tex);

	}

	void unbind()
	{
		glActiveTexture(0);
		glBindTexture(type, 0);

	}
	

};