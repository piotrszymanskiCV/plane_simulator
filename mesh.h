#pragma once

#include<iostream>
#include<vector>

#include"Vertex.h"
#include"primitives.h"
#include"Shader.h"
#include"tekstury.h"
#include"Material.h"

class Mesh
{
private:
	Vertex * vertexArray;
	//Vertex * vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	//GLuint* indexArray;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 origin;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;







	void initVAO()
	{
		

		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		//GEN VBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

		//GEN EBO AND BIND AND SEND DATA
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);


		//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		//Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		//Texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		//BIND VAO 0
		glBindVertexArray(0);
	}































	
	


	


	void updateUniforms(Shader* shader)
	{
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}


public:
	Mesh(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),//skasowac to 
		glm::vec3 rotation = glm::vec3(0.f), 
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->origin = origin;
		this->rotation = rotation;
		this->scale = scale;



		this->nrOfVertices = nrOfVertices;
		this ->nrOfIndices = nrOfIndices;
		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertexArray[i] = vertexArray[i];
		}



		this->indexArray = new GLuint[this->nrOfIndices];



		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indexArray[i] = indexArray[i];
		}





		this->initVAO();
		this->updatemodel1();
		
	}








	Mesh(
		Primitive* primitive,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 origin = glm::vec3(0.f),//skasowac to 
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		

		this->nrOfVertices = primitive->getNrOfVertices();
		this->nrOfIndices = primitive->getNrOfIndices();
		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = primitive->getVertices()[i];
		}



		this->indexArray = new GLuint[this->nrOfIndices];



		for (size_t i = 0; i <this->nrOfIndices; i++)
		{
			this->indexArray[i] = primitive->getIndices()[i];
		}





		this->origin = origin;












		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->initVAO();
		this->updatemodel1();

	}


	Mesh(const Mesh& onj)
		{
		this->origin = origin;
		this->position = onj.position;
		this->rotation = onj.rotation;
		this->scale = onj.scale;

		this->nrOfVertices = onj.nrOfVertices;
		this->nrOfIndices = onj.nrOfIndices;
		this->vertexArray = new Vertex[this->nrOfVertices];
		for (size_t i = 0; i < this->nrOfVertices; i++)
		{
			this->vertexArray[i] = onj.vertexArray[i];
		}



		this->indexArray = new GLuint[this->nrOfIndices];



		for (size_t i = 0; i <this->nrOfIndices; i++)
		{
			this->indexArray[i] = onj.indexArray[i];
		}


		
		this->initVAO();
		this->updatemodel1();


		}
























void updatemodel1() {

	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);// wrzucic to zeby owkol wlasnej osi zamiar tegp 2 na gorze
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);

}

~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		
		
		if (this->nrOfIndices > 0)
		{
			glDeleteBuffers(1, &this->EBO);
		}

		delete[] this->vertexArray;
		delete[] this->indexArray;






	}

void setorigin(const glm::vec3 origin)
{
	this->origin = origin;

}

void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}
void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}
void setScale(const glm::vec3 setScale)
	{
		this->scale = scale;
	}
void move(const glm::vec3 position)
	{
		this->position += position;
	}
void rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;
	}
void scaleUp(const glm::vec3 scale)
	{
		this->scale += scale;
	}
void update()
	{

	}

	void render(Shader* shader)
	{
		
		
		
		
		
		this->ModelMatrix = glm::mat4(1.f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);// wrzucic to zeby owkol wlasnej osi zamiar tegp 2 na gorze
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
		
		this->updateUniforms(shader);

		shader->use();

		
		glBindVertexArray(this->VAO);

		if (this->nrOfIndices == 0)
		{
			glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);

		}
		else
			glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};