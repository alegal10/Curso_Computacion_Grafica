//Práctica #4                                     Galindo Granados Abner Alejandro
//Fecha de entrega: 29 febrero de 2026                                   320001567
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Galindo Granados Abner Alejandro", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,1.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,1.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f,1.0f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 1.0f,1.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f,1.0f,

		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		 0.5f,  -0.5f, 0.5f,  1.0f, 1.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,1.0f,
	};

	//Negro
	float vertices2[] = {
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f,0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,0.0f,
	};

	//Gris fuerte
	float vertices3[] = {
	-0.5f, -0.5f, 0.5f, 0.3f, 0.3f,0.3f,//Front
	0.5f, -0.5f, 0.5f,  0.3f, 0.3f,0.3f,
	0.5f,  0.5f, 0.5f,  0.3f, 0.0f,0.3f,
	0.5f,  0.5f, 0.5f,  0.3f, 0.3f,0.3f,
	-0.5f,  0.5f, 0.5f, 0.3f, 0.3f,0.3f,
	-0.5f, -0.5f, 0.5f, 0.3f, 0.3f,0.3f,

	-0.5f, -0.5f,-0.5f, 0.3f, 0.3f,0.3f,//Back
	 0.5f, -0.5f,-0.5f, 0.3f, 0.3f,0.3f,
	 0.5f,  0.5f,-0.5f, 0.3f, 0.3f,0.3f,
	 0.5f,  0.5f,-0.5f, 0.3f, 0.3f,0.3f,
	-0.5f,  0.5f,-0.5f, 0.3f, 0.3f,0.3f,
	-0.5f, -0.5f,-0.5f, 0.3f, 0.3f,0.03f,

	 0.5f, -0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	 0.5f, -0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	 0.5f,  0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	 0.5f,  0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	 0.5f,  0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	 0.5f,  -0.5f, 0.5f,  0.3f, 0.3f,0.3f,

	-0.5f,  0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	-0.5f,  0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	-0.5f, -0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	-0.5f, -0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	-0.5f, -0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	-0.5f,  0.5f,  0.5f,  0.3f, 0.3f,0.3f,

	-0.5f, -0.5f, -0.5f, 0.3f, 0.3f,0.3f,
	0.5f, -0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	0.5f, -0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	0.5f, -0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	-0.5f, -0.5f,  0.5f, 0.3f, 0.3f,0.3f,
	-0.5f, -0.5f, -0.5f, 0.3f, 0.3f,0.3f,

	-0.5f,  0.5f, -0.5f, 0.3f, 0.3f,0.3f,
	0.5f,  0.5f, -0.5f,  0.3f, 0.3f,0.3f,
	0.5f,  0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	0.5f,  0.5f,  0.5f,  0.3f, 0.3f,0.3f,
	-0.5f,  0.5f,  0.5f, 0.3f, 0.3f,0.3f,
	-0.5f,  0.5f, -0.5f, 0.3f, 0.3f,0.3f,
	};

	//Gris claro
	float vertices4[] = {
	-0.5f, -0.5f, 0.5f, 0.7f, 0.7f,0.7f,//Front
	0.5f, -0.5f, 0.5f,  0.7f, 0.7f,0.7f,
	0.5f,  0.5f, 0.5f,  0.7f, 0.7f,0.7f,
	0.5f,  0.5f, 0.5f,  0.7f, 0.7f,0.7f,
	-0.5f,  0.5f, 0.5f, 0.7f, 0.7f,0.7f,
	-0.5f, -0.5f, 0.5f, 0.7f, 0.7f,0.7f,

	-0.5f, -0.5f,-0.5f, 0.7f, 0.7f,0.7f,//Back
	 0.5f, -0.5f,-0.5f, 0.7f, 0.7f,0.7f,
	 0.5f,  0.5f,-0.5f, 0.7f, 0.7f,0.7f,
	 0.5f,  0.5f,-0.5f, 0.7f, 0.7f,0.7f,
	-0.5f,  0.5f,-0.5f, 0.7f, 0.7f,0.7f,
	-0.5f, -0.5f,-0.5f, 0.7f, 0.7f,0.7f,

	 0.5f, -0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	 0.5f, -0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	 0.5f,  0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	 0.5f,  0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	 0.5f,  0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	 0.5f,  -0.5f, 0.5f,  0.7f, 0.7f,0.7f,

	-0.5f,  0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	-0.5f,  0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	-0.5f, -0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	-0.5f, -0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	-0.5f, -0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	-0.5f,  0.5f,  0.5f,  0.7f, 0.7f,0.7f,

	-0.5f, -0.5f, -0.5f, 0.7f, 0.7f,0.7f,
	0.5f, -0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	0.5f, -0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	0.5f, -0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	-0.5f, -0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
	-0.5f, -0.5f, -0.5f, 0.7f, 0.7f,0.7f,

	-0.5f,  0.5f, -0.5f, 0.7f, 0.7f,0.7f,
	0.5f,  0.5f, -0.5f,  0.7f, 0.7f,0.7f,
	0.5f,  0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	0.5f,  0.5f,  0.5f,  0.7f, 0.7f,0.7f,
	-0.5f,  0.5f,  0.5f, 0.7f, 0.7f,0.7f,
	-0.5f,  0.5f, -0.5f, 0.7f, 0.7f,0.7f,
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices
	// Atributos (Posición y Color) - Se configuran igual que el primero
	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	//Segundos vertices
	GLuint VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Desactivamos por seguridad

	//TERCER ARREGLO DE VERTICES
	GLuint VBO3, VAO3;
	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glBindVertexArray(VAO3);
	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Desactivamos por seguridad

	//CUARTO
	GLuint VBO4, VAO4;
	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glBindVertexArray(VAO4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Desactivamos por seguridad

	// Atributos (Posición y Color) - Se configuran igual que el primero

	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.4f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);

		//Cuerpo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(6.0f, 3.0f, 4.0f));
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//adelante
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 2.5f, 4.0f));
		model = glm::translate(model, glm::vec3(30.5f, 1.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//atras
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 2.5f, 4.0f));
		model = glm::translate(model, glm::vec3(-30.5f, 1.2f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(6.0f, 2.5f, 0.1f));
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, 20.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//Derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(6.0f, 2.5f, 0.1f));
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, -20.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata 1
		glBindVertexArray(VAO2);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 2.0f, 0.8f));
		model = glm::translate(model, glm::vec3(-2.3f, 0.7f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 2.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-3.1f, 0.7f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Pata 2
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 2.0f, 0.8f));
		model = glm::translate(model, glm::vec3(-2.3f, 0.7f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 2.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-3.1f, 0.7f, -1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Pata 3
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 2.0f, 0.8f));
		model = glm::translate(model, glm::vec3(2.3f, 0.7f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 2.0f, 1.0f));
		model = glm::translate(model, glm::vec3(3.1f, 0.7f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Pata 4
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.8f, 2.0f, 0.8f));
		model = glm::translate(model, glm::vec3(2.3f, 0.7f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.6f, 2.0f, 1.0f));
		model = glm::translate(model, glm::vec3(3.1f, 0.7f, -1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO);

		//Cabeza
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.3f, 1.8f,3.0f));
		model = glm::translate(model, glm::vec3(-2.8f, 1.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.3f, 2.0f, 2.9f));
		model = glm::translate(model, glm::vec3(-2.8f, 1.17f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 1.8f, 2.9f));
		model = glm::translate(model, glm::vec3(-43.4f, 1.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Nariz
		glBindVertexArray(VAO4);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.5f));
		model = glm::translate(model, glm::vec3(-15.2f, 1.8f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.5f));
		model = glm::translate(model, glm::vec3(-15.2f, 1.8f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 1.0f));
		model = glm::translate(model, glm::vec3(-30.0f, 11.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(VAO2);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(-9.5f, 4.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(-16.0f, 5.7f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Orejas
		//Derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.5f, 0.4f));
		model = glm::translate(model, glm::vec3(-19.5f, 7.0f, 3.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.4f));
		model = glm::translate(model, glm::vec3(-19.5f, 8.6f, 3.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//Izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.5f, 0.4f));
		model = glm::translate(model, glm::vec3(-19.5f, 7.0f, -3.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.4f, 0.4f));
		model = glm::translate(model, glm::vec3(-19.5f, 8.6f, -3.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Cola
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
		model = glm::translate(model, glm::vec3(6.5f, 6.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		 
		//Ojos
		//Derecho Contorno
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 1.1f, 1.0f));
		model = glm::translate(model, glm::vec3(-43.5f, 2.5f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.9f, 0.2f));
		model = glm::translate(model, glm::vec3(-28.2f, 2.8f, 7.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(-27.2f, 6.2f, 7.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-29.1f, 3.3f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Izquierdo Contorno
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 1.1f, 1.0f));
		model = glm::translate(model, glm::vec3(-43.5f, 2.5f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.9f, 0.2f));
		model = glm::translate(model, glm::vec3(-28.2f, 2.8f, -7.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.4f, 0.2f));
		model = glm::translate(model, glm::vec3(-27.2f, 6.2f, -7.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.8f, 0.2f));
		model = glm::translate(model, glm::vec3(-29.1f, 3.3f, -2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Drecho dentro
		glBindVertexArray(VAO);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-21.6f, 12.0f, 5.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO3);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-21.6f, 12.0f, 4.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//Izquierdo dentro
		glBindVertexArray(VAO);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-21.6f, 12.0f, -5.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(VAO3);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::translate(model, glm::vec3(-21.6f, 12.0f, -4.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Lineas del cuerpo (negro) 
		//arriba
		glBindVertexArray(VAO2);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.2f, 0.2f, 4.2f));
		model = glm::translate(model, glm::vec3(-0.4f, 22.05f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//frente
		glBindVertexArray(VAO2);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.2f, 0.5f, 0.2f));
		model = glm::translate(model, glm::vec3(-0.4f, 8.2f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.8f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3(-0.6f, 6.0f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.2f));
		model = glm::translate(model, glm::vec3(-0.82f, 6.1f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.2f, 0.7f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.15f, 3.5f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.7f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.49f, 2.7f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.1f, 1.5f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.3f, 1.5f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//atras
		glBindVertexArray(VAO2);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.2f, 0.5f, 0.2f));
		model = glm::translate(model, glm::vec3(-0.4f, 8.2f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.8f, 0.6f, 0.2f));
		model = glm::translate(model, glm::vec3(-0.6f, 6.0f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.2f));
		model = glm::translate(model, glm::vec3(-0.82f, 6.1f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.2f, 0.7f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.15f, 3.5f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 0.7f, 0.2f));
		model = glm::translate(model, glm::vec3(-1.49f, 2.7f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.1f, 1.5f, 0.2f));
		model = glm::translate(model, glm::vec3(-2.3f, 1.5f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//frente derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.2f, 0.2f));
		model = glm::translate(model, glm::vec3(5.75f, 1.75f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.9f, 0.2f));
		model = glm::translate(model, glm::vec3(4.8f, 2.15f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.2f));
		model = glm::translate(model, glm::vec3(4.0f, 2.65f, 10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//atras derecha
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.2f, 0.2f));
		model = glm::translate(model, glm::vec3(5.75f, 1.75f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.9f, 0.2f));
		model = glm::translate(model, glm::vec3(4.8f, 2.15f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.2f));
		model = glm::translate(model, glm::vec3(4.0f, 2.65f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//lineas cola
		//izq
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.5f));
		model = glm::translate(model, glm::vec3(10.0f, 2.0f, 3.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.7f, 0.5f));
		model = glm::translate(model, glm::vec3(10.0f, 2.65f, 2.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//der
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 1.0f, 0.5f));
		model = glm::translate(model, glm::vec3(10.0f, 2.0f, -3.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.7f, 0.5f));
		model = glm::translate(model, glm::vec3(10.0f, 2.65f, -2.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.4f;
}



