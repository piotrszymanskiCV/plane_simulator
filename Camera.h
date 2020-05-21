#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>


enum direction {FORWARD  = 0, DOWNWARD , LEFT , RIGHT ,UP ,DOWN};
class Camera
{
private:

	glm::mat4 ViewMatrix;

	GLfloat movementspeed;
	GLfloat sensitivity;


	glm::vec3 worldup;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 rotation;
	


	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
	
	
	
	
	
	void updatecameravectors() 
	{
		this->front.x = cos(glm::radians(this->yaw))*cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw))*cos(glm::radians(this->pitch));


		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldup));

		this->up = glm::normalize(glm::cross(this->right, this->front));




	}




















public:
	Camera(glm::vec3 position, glm::vec3 direction  , glm::vec3 worldUp)
	{
		this->ViewMatrix = glm::mat4(1.f);
		this->movementspeed =  5.1f;
		this->sensitivity = 1.f;
		this->worldup = worldUp;
		this->position = position;
		this->right = glm::vec3(0.f);
		this->up = worldUp;
		this->pitch = 0.f;
		this->yaw = 0.f;
		this->roll = -90.f;
		this->updatecameravectors();
		this->rotation = glm::vec3(0.f, 0.f, 0.f);
	}

	~Camera() {}


	const glm::mat4 getViewMatrix()
	{
		this->updatecameravectors();

		this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
		
		return this->ViewMatrix;

	}

	const glm::vec3 getposition() const 
	{
		return this->position;
	}
	
	
	
	void updatemouseinput(const float& dt, const double& offsetX, const double& offsety)
	{
		this->pitch += static_cast<GLfloat>(offsety) * this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;

		if (this->pitch >= 80.f)
			this->pitch = 80.f;
		else if (this->pitch <= -80.f)
			this->pitch = -80.f;

		if (this->yaw > 360.f || this->yaw < -360.f)
			this->yaw = 0;




	}
	
	
	void move(const float& dt, const int direction) {
		switch (direction)
		{
		case FORWARD:
			this->position.x += 0.1f; 

			break;
		case DOWNWARD:
			this->position.x -= 0.1f;

			break;
		case LEFT:
			this->position.z -= 0.1f ;
			this->rotation.x -= 11.f;
			break;
		case RIGHT:

			this->position.z += 0.1f;
			break;
		case UP:

			this->position.y += 0.1f;
			break;
		case DOWN:

			this->position.y -= 0.1f;
			break;
		default:


			break;






		}


	}
	
	void updateinput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
	{
		
		this->updatemouseinput(dt, offsetX , offsetY);
		
	
	}


};