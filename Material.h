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
#include "shader.h"



class Material
{
private:
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spec;
	GLint dif_tex;
	GLint spec_tex;
	
	
	
public:	
	Material(
	glm::vec3 amb,
	glm::vec3 dif,
	glm::vec3 spec,
	GLint dif_tex)
	{
		this->amb = amb;
		this->dif_tex = dif_tex;
		this->spec = spec;
		this->spec_tex = spec_tex;
		this->dif - dif;

	}

	~Material(){}
	void sendtoshader(Shader& id)
	{
		id.setVec3f(this->amb, "material.amb");
		id.setVec3f(this->dif, "material.dif");
		id.setVec3f(this->spec, "material.spec");
		id.set1i(this->dif_tex, "material.diff_tex");
		//id.set1i(this->spec_tex, "material.spec_tex");
	}


};