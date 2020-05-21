#pragma once
#include "libs.h"
#include "Camera.h"
#include "Model.h"

//enums 
enum shader_enum {SHADER_CORE_PROGRAM = 0 };
enum texture_enum {TEX_PUSHEN0 = 0,TEX_CONTAINER_1 = 1 };
enum material_enum {MAT_1 = 0 };
enum mesh_enum{ MESH_QUAD = 0};


class Game
{
private:
	GLFWwindow * window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferwidth;
	int framebufferheight;
	//openGL context
	const int GLVERMAJOR;
	const int GLVERMINOR;

	//Mouse Input
	
	float dt;
	float curTime;
	float lastTime;
	
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;


	Camera camera;













	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldup;
	glm::vec3 camerafront;
	
	glm::mat4 ProjectionMatrix;
	float fov;
	float nearplate;
	float farplane;

	//shaders
	std::vector<Shader*> shaders;
	//texture
	std::vector<Texture*> Textrures;

	//material
	std::vector<Material*> materials;
	//mesh 


	
	std::vector<Model*> models;
	//light
	std::vector<glm::vec3*> lights;
	//std::vector<Shader*> shaders;










//PRIVATE FUNCJTIONS	
	
	void initGLFW();
	void initwindow(const char* title,
		bool resisable);
	void initGLEW();
	void initopengl();
	void initmatrix();
	void initshaders();
	void inittekstures();
	void initmaterials();
	void initmeshes();
	void initmodels();
	void teren();
	void initobj();
	void initlights();
	void inituniform();
	void updateuniforms();
	
public:
	Game(
		const char* title,
		const int WINDOW_WIDTH,
		const int WINDOW_HEIGHT,
		int glmajor,
		int glminor,
		bool res);
	virtual ~Game();
	int getwindowshouldclose();
	void setwindowshouldclose();

	void updatedt();


	void updatemouseinput();
	
	void updatekeyboardinput();
	void updateinput();
	void update();

	void render();
	


	static void rozszerzanko(GLFWwindow* window, int neww, int newl);
	
};


