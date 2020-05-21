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

class Shader
{
private:
	GLuint id;

	std::string loadshadersource(char* filename)
	{
		std::string temp = "";
		std::string src = "";
		std::ifstream i_f;
		i_f.open(filename);
		if (i_f.is_open())
		{
		while (std::getline(i_f, temp))
			src += temp + "\n";
		}
		else {
			std::cout << "error shader 1 " << "\n";
		}
		i_f.close();

		return(src);
	}
	//tworzenie shadera z pliku:
	GLuint loadshader(GLenum type, char* filename)
	{
		GLint succes;
		
		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadshadersource(filename);
		// tworzymy shader w pamiecie opengl'a i dostajemy jego id 
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
		if (!succes) {

			std::cout << "b³¹d shadera 2" << "\n";
			
		}
		return shader;
	}

	void linker(GLuint vertexshader, GLuint geometryshader, GLuint fragmentshader) 
	{
		GLint succes;
		this -> id = glCreateProgram();
		
		
		glAttachShader(this->id, vertexshader);
		if (geometryshader) 
		{
			glAttachShader(this->id, geometryshader);
		}
		glAttachShader(this->id, fragmentshader);
		glLinkProgram(this->id);


		glGetProgramiv(this ->id, GL_LINK_STATUS, &succes);
		if (!succes) {
			std::cout << "blad shader 3" << "\n";
			
		}
		
		
		glUseProgram(0);
		

	}

public:
	Shader(char* vertexfile, char* fragmentfile, char* geomertyfile = "")//konstruktor 
	{
		GLuint vertexshader = 0;
		GLuint geomertyshader = 0;
		GLuint fragmentshader = 0;

		vertexshader = loadshader(GL_VERTEX_SHADER, vertexfile);
		if (geomertyfile != "") {
			geomertyshader = loadshader(GL_GEOMETRY_SHADER, geomertyfile);

		}


		fragmentshader = loadshader(GL_FRAGMENT_SHADER, fragmentfile);

		this->linker(vertexshader, geomertyshader, fragmentshader);
		
		glDeleteShader(fragmentshader);
		glDeleteShader(vertexshader);
		glDeleteShader(geomertyshader);
		

	}


	~Shader()//destruktory
	{

		glDeleteProgram(this->id);
	}

	void set1i(GLfloat value, const GLchar* name)
	{
		this->use();
		glUniform1f(glGetUniformLocation(this->id, name), value);




		this->unuse();

	}

	

	void use()
	{

		glUseProgram(this->id);
	}
	void unuse() {

		glUseProgram(0);
	}
	void setVec1f(GLfloat value, const GLchar* name)
	{
		this->use();
		glUniform1f(glGetUniformLocation(this->id, name),value);




		this->unuse();

	}
	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		this->use();
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));




		this->unuse();

	}

	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		this->use();
		glUniform3fv(glGetUniformLocation(this ->id , name), 1, glm::value_ptr(value));




		this->unuse();

	}
	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		this->use();
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));




		this->unuse();

	}

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean tran = GL_FALSE)
	{
		this->use();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, tran, glm::value_ptr(value));




		this->unuse();

	}
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean tran = GL_FALSE)
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, tran, glm::value_ptr(value));




		this->unuse();

	}
};


