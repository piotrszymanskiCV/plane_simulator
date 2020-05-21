#include "Game.h"
#include "Model.h"
#include "obj.h"


void Game::initGLFW()
{
	if (glfwInit() == GLFW_FALSE) {

		std::cout << "blad glfw init" << "\n";
		glfwTerminate();
	}
}

void Game::initwindow(
	const char* title,
	bool resisable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GLVERMAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,this->GLVERMINOR);
	glfwWindowHint(GLFW_RESIZABLE, resisable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
	if (this->window == nullptr)
	{
		std::cout << "blad glfw window init" << "\n";
		glfwTerminate();
	}
	
	
	glfwGetFramebufferSize(this->window, &this->framebufferwidth, &this->framebufferheight);
	glfwSetFramebufferSizeCallback(window, Game::rozszerzanko);

	//glViewport(0, 0, framebufferwidth, framebufferlength);
	glfwMakeContextCurrent(this->window);
}

void Game::initGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW siê nie za³adowa³o" << "\n";
		glfwTerminate();

	}
}

void Game::initopengl()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//input 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initmatrix()
{
	
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camerafront, this->worldup); 

	
	this->ProjectionMatrix = glm::mat4(1.f);
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferwidth) / this->framebufferheight,
		this->nearplate,
		this->farplane
	);
}

void Game::initshaders()
{
	this->shaders.push_back(new Shader("vertex.glsl", "fragment.glsl"));
}

void Game::inittekstures()
{
	this->Textrures.push_back( new Texture("images/pobrane.png", GL_TEXTURE_2D));
	//this->Textrures.push_back(new Texture("images/pobrane_specular.png", GL_TEXTURE_2D));


	this->Textrures.push_back( new Texture("images/container.png", GL_TEXTURE_2D));
}

void Game::initmaterials()
{
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
		0));
}

void Game::initmeshes()
{
	
}

void Game::initobj()
{
	

}
void Game::initmodels()
{
	std::vector<Mesh*>meshes;
	std::vector<Mesh*>meshes1;
	std::vector<Mesh*>meshes2;
	std::vector<Vertex> mesh = loadOBJ("OBJFILES/samolot.obj");
	meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(0.01f)
	));
	
	std::vector<Vertex> mesh2 = loadOBJ("OBJFILES/budynek.obj");
	meshes2.push_back(new Mesh(mesh2.data(), mesh2.size(), NULL, 0, glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(10.f,0.f,0.f),
		glm::vec3(0.33f)
	));
	
	
	/*std::vector<Vertex> mesh1 = loadOBJ("OBJFILES/samolot.obj");
	meshes1.push_back(new Mesh(mesh1.data(), mesh1.size(), NULL, 0, glm::vec3(10.f, -0.5f, 10.f),
		glm::vec3(0.f),
		glm::vec3(0.f, 180.f, 0.f),
		glm::vec3(0.2f)
	));
	*/
	
	
	meshes1.push_back(
		new Mesh(
			&Pyramid(),
			glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);
	this->models.push_back(new Model(
		glm::vec3(0.f, -1.0f, -30.f),
		this->materials[0],
		this->Textrures[TEX_PUSHEN0],
		meshes1));
	
	
		this->models.push_back(new Model(
			glm::vec3(2.f, -1.5f, -12.f),
			this->materials[0],
			this->Textrures[TEX_PUSHEN0],
			meshes2));

		this->models.push_back(new Model(
			glm::vec3(20.f, -0.5f, -2.f),
			this->materials[0],
			this->Textrures[TEX_PUSHEN0],
			meshes2));
		

		this->models.push_back(new Model(
			glm::vec3(40.f, -2.5f, -12.f),
			this->materials[0],
			this->Textrures[TEX_PUSHEN0],
			meshes2));

		
		
		this->models.push_back(new Model(
			glm::vec3(2.f, -1.4f, 0.f),
			this->materials[0],
			this->Textrures[TEX_PUSHEN0],
			meshes));

		


		
	

	for (auto*& i : meshes)
		delete i;
}

void Game::teren()
{
	std::vector<Mesh*>meshes;
	std::vector<Vertex> mesh = loadOBJ("OBJFILES/diamond1.obj");
	meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	));


	std::vector<Mesh*>meshes1;
	
	
	
	std::vector<Vertex> mesh1 = loadOBJ("OBJFILES/diamond1.obj");
	meshes1.push_back(new Mesh(mesh1.data(), mesh1.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	));

	GLfloat iksde = 4.f;
	GLfloat kk = 0.f;
	for (size_t i = 0; i < 5; i++)
	{
		this->models.push_back(new Model(
			glm::vec3(kk, -1.49f, 0.f),
			this->materials[0],
			this->Textrures[TEX_PUSHEN0],
			meshes1));
		kk = kk + iksde;
	}
	









	GLfloat przesun = 1.f;
	GLfloat zerówka = 1.f;
	
	
	GLfloat zerówka2 = -5.f;
	for (size_t i = 0; i < 10; i++)
	{

		std::cout << "penis ? ";
		this->models.push_back(new Model(
			glm::vec3(1.f, -1.5f,zerówka2),
			this->materials[0],
			this->Textrures[TEX_CONTAINER_1],
			meshes));
		for (size_t i = 0; i < 300; i++)
		{

			std::cout << "penis ? ";
			this->models.push_back(new Model(
				glm::vec3(zerówka, -1.5f, zerówka2),
				this->materials[0],
				this->Textrures[TEX_CONTAINER_1],
				meshes));
			zerówka = zerówka + przesun;
		}
		zerówka = 1.f;
		zerówka2 = zerówka2 + przesun;
		
		
		
	}



	for (auto*& i : meshes)
		delete i;

}

void Game::initlights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));

}

void Game::inituniform()
{

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	


}

void Game::updateuniforms()
{

	


	//move rotate and scale 

	//camera
	this->ViewMatrix = this->camera.getViewMatrix();
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getposition(), "camPosition");



	glfwGetFramebufferSize(this->window, &this->framebufferwidth, &this->framebufferheight);

	
	
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferwidth) / this->framebufferheight,
		this->nearplate,
		this->farplane
	);
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

}

Game::Game(
	const char* title,
	const int WINDOW_WIDTH,
	const int WINDOW_HEIGHT,
	int glmajor, int glminor, 
	bool res
)
	: WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GLVERMAJOR(glmajor), GLVERMINOR(glminor),
	camera(glm::vec3(-15.f,-0.9f,0.f), glm::vec3(10.f,0.f,1.f),glm::vec3(0.f,1.f,0.f))
{	
	this->window = nullptr;
	this->framebufferwidth = this->WINDOW_WIDTH;
	this->framebufferheight = this->WINDOW_HEIGHT;

	
	this->camPosition = glm::vec3(0.f, 0.f, 2.f);
	this->worldup = glm::vec3(0.f, 1.f, 0.f);
	this->camerafront = glm::vec3(0.f, 0.f, -1.f);


	
	
	
	this->fov = 8.f;
	this->nearplate = 0.01f;
	this->farplane = 1000.f;
	
	
	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0;
	this->mouseX = 0.0;
	this->mouseY = 0.0;
	this->mouseOffsetX = 0.0;
	this->mouseOffsetY = 0.0;
	this-> firstMouse = true;


	this->initGLFW();
	this->initwindow(title, res);
	this->initGLEW();
	this->initopengl();
	this->initmatrix();
	this->initshaders();
	this->inittekstures();
	this->initmaterials();
	this->initobj();
	this->initmeshes();
	
	this->initmodels();
	this->teren();
	this->initlights();
	this->inituniform();
	this->initobj();
}

Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	for (size_t i = 0; i < this-> shaders.size(); i++)
	{
		delete this->shaders[i];
	}
	for (size_t i = 0; i < this->Textrures.size(); i++)
	{
		delete this->Textrures[i];
	}
	for (size_t i = 0; i < this->materials.size(); i++)
	{
		delete this->materials[i];
	}
	/*
	for (size_t i = 0; i < this->meshes.size(); i++)
	{
		delete this->meshes[i];*/
	for (auto*& i : this->models)
	{
		delete i;
	}
	
	
	
	for (size_t i = 0; i < this->lights.size(); i++)
	{
		delete this->lights[i];
	}
}

int Game::getwindowshouldclose()
{
	return glfwWindowShouldClose(this->window);
}

void Game::setwindowshouldclose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

void Game::updatedt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;

	

}
















void Game::updatemouseinput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;




}

void Game::updatekeyboardinput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

		this->setwindowshouldclose();
	}


	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {

		this->camera.move(this->dt, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {

		this->camera.move(this->dt, DOWNWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {

		this->camera.move(this->dt, LEFT);
	}


	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {

		this->camera.move(this->dt,RIGHT);
	}

	if (glfwGetKey(this->window, GLFW_KEY_2) == GLFW_PRESS) {

		this->camera.move(this->dt, UP);
	}
	if (glfwGetKey(this->window, GLFW_KEY_8) == GLFW_PRESS) {

		this->camera.move(this->dt, DOWN);
	}
	if (glfwGetKey(this->window, GLFW_KEY_C) == GLFW_PRESS) {

		this->camPosition.y += 0.05f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		this->camPosition.y -= 0.05f;
	}
}

void Game::updateinput()
{
	glfwPollEvents();
	this->updatekeyboardinput();
	this->updatemouseinput();
	this->camera.updateinput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);

}






























void Game::update()
{
	this->updatedt();
	this->updateinput();
	//if
	
	glm::vec3 rotowanko = glm::vec3(0.0f, 0.f, 0.f);
	if (glfwGetKey(this->window, GLFW_KEY_8) == GLFW_PRESS) {
		//this->models[4]->rotate(glm::vec3(0.f, 0.f, -0.5f));

		this->models[4]->muf(glm::vec3(0.0f, -0.1f, 0.0f));
		//this->models[1]->rotate(glm::vec3(0.0f, 1.0f, 0.f));
	}

	
	
	if (glfwGetKey(this->window, GLFW_KEY_2) == GLFW_PRESS) {
		
		//this->models[4]->rotate(glm::vec3(0.0f, 0.f, 0.3f));
		this->models[4]->muf(glm::vec3(0.0f, 0.1f, 0.0f));
		//this->models[4]->rotate(glm::vec3(0.0f, 0.f, -0.5f));
		//this->models[1]->rotate(glm::vec3(0.0f, 1.0f, 0.f));
	}
	if (glfwGetKey(this->window, GLFW_KEY_2) != GLFW_PRESS) {

		this->models[4]->rotateback();
	}
	

	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
		//this->models[4]->rotate(glm::vec3(0.f, 0.5f, 0.f));

		this->models[4]->muf(glm::vec3(-0.0f, +0.f, -0.1f));
		//this->models[1]->rotate(glm::vec3(0.0f, 1.0f, 0.f));
	}




	if (glfwGetKey(this->window, GLFW_KEY_A) != GLFW_PRESS) {
		this->models[4]->rotateback();
	}
	


	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
		//this->models[4]->rotate(glm::vec3(+0.05f, 0.0f, 0.f));

		this->models[4]->muf(glm::vec3(-0.0f, +0.00f, +0.1f));
		//this->models[1]->rotate(glm::vec3(0.0f, 1.0f, 0.f));
	}

	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
		//this->models[4]->rotate(glm::vec3(0.f, 0.05, 0.f));

		this->models[4]->muf(glm::vec3(+0.1f, +0.f, -0.0f));
		//this->models[1]->rotate(glm::vec3(0.0f, 1.0f, 0.f));
	}


	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
		//this->models[4]->rotate(glm::vec3(0.f, -0.05, 0.f));

		this->models[4]->muf(glm::vec3(-0.1f, +0.f, +0.0f));
		//this->models[1]->rotate(glm::vec3(0.0f, 1.0f, 0.f));
	}








}

void Game::render()
{

	//update input
	
	//update
	//update(window);
	//draw
	//clear
	//draw
	//enddraw
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	this->updateuniforms();
	//use porgram

	
	for (auto&i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);



	
	
	//this->meshes[1]->render(this->shaders[SHADER_CORE_PROGRAM]);
	glfwSwapBuffers(this->window);
	glFlush();
	
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Game::rozszerzanko(GLFWwindow* window, int neww, int newl)
{
	glViewport(0, 0, neww, newl);
};

