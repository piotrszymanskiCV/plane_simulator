#pragma once
#include "mesh.h"
#include "tekstury.h"
#include "shader.h"
#include "Material.h"
#include "libs.h"
#include"obj.h"

class Model
{
private:
	Material * material;
	Texture * overridetehturediff;
	Texture * overridetehturespec;
	std::vector<Mesh*> meshes;
	glm::vec3 origin;
	glm::vec3 position;

	void updateuniforms1()
	{

	}

public:
	Model(
		glm::vec3 position,
		Material*material,
		Texture* texdif,
		std::vector<Mesh*> meshes
		)
	{
		this->position = position;
		this->material = material;
		this->overridetehturediff = texdif;

		for (auto* i : meshes)
		{
			this->meshes.push_back(new Mesh(*i));
		}



		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setorigin(this->position);
		}









	}


	Model(
		glm::vec3 position,
		Material*material,
		Texture* texdif,
		const char* objfile)
	
	{
		this->position = position;
		this->material = material;
		this->overridetehturediff = texdif;

		std::vector<Vertex> mesh = loadOBJ(objfile);
		this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)));

		for (auto& i : this->meshes)
		{
			i->move(this->position);
			i->setorigin(this->position);
			
		}









	}








	~Model()
	{

		for (auto*& i : this->meshes)
			delete i;
	}

	//fuc



	void rotate(const glm::vec3 rotation)
	{	
		for (auto& i : this->meshes)
			i->rotate(rotation);

	}
	void rotateback() {
		
		for (auto& i : this->meshes)
			i->setRotation(glm::vec3(0.f,0.f,0.f));
			
	}


	void muf(const glm::vec3 rotation)
	{
		for (auto& i : this->meshes)
			i->move(rotation);

	}


















	void update()
	{


	}


	void render(Shader* shader)
	{
		this->updateuniforms1();
		
		//use porgram



		this->material->sendtoshader(*shader);




		shader->use();
		//ACTIVATE TEXTURE
		for (auto& i : this->meshes)
		{
			this->overridetehturediff->bind(0);

			// bind vertex array object
			i->render(shader);
		}

		
	}

};