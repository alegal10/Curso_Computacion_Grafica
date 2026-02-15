//Práctica 2                                 Galindo Granados Abner Alejandro
//Fecha de entrega: 15 febrero de 2026        320001567
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//Cuerpo
		//Primer Pentágono
		-0.4f, 0.1f, 0.0f,    1.0f,1.0f,1.0f,
		-0.5f, -0.4f,0.0f,    1.0f,1.0f,1.0f,
		0.0f, -0.6f, 0.0f,    1.0f,1.0f,1.0f,
		0.45f, -0.4f, 0.0f,   1.0f,1.0f,1.0f,
		0.32f, 0.1f, 0.0f,    1.0f,1.0f,1.0f,

		//Primer Trapecio
		-0.4f, 0.1f, 0.0f,    1.0f,1.0f,1.0f,
		0.32f, 0.1f, 0.0f,    1.0f,1.0f,1.0f,
		0.09f, 0.47f, 0.0f,   1.0f,1.0f,1.0f,
		-0.15f, 0.47f, 0.0f,  1.0f,1.0f,1.0f,

		//Segundo trapecio izq
		-0.5f, -0.4f, 0.0f,  0.8f,0.8f,0.8f,
		-0.51f, -0.76f, 0.0f, 0.8f,0.8f,0.8f,
		-0.29f, -0.86f, 0.0f, 0.8f,0.8f,0.8f,
		0.0f, -0.6f, 0.0f,    0.8f,0.8f,0.8f,

		//Tercer trapecio der
		0.0f, -0.6f, 0.0f,    0.8f,0.8f,0.8f,
		0.45f, -0.4f, 0.0f,   0.8f,0.8f,0.8f,
		0.49f, -0.76f, 0.0f,  0.8f,0.8f,0.8f,
		0.27f, -0.86f, 0.0f,  0.8f,0.8f,0.8f,

		//Segundo Pentagono
		0.0f, -0.6f, 0.0f,    0.5f,0.5f,0.5f,
		-0.29f, -0.86f, 0.0f, 0.5f,0.5f,0.5f,
		-0.09f, -0.99f, 0.0f,   0.5f,0.5f,0.5f,
		0.09f, -0.99f, 0.0f,   0.5f,0.5f,0.5f,
		0.27f, -0.86f, 0.0f,  0.5f,0.5f,0.5f,

		//Patas
		//Izquierda
		//Triángulo Izq arriba
		-0.51f, -0.76f, 0.0f, 1.0f,0.65f,0.0f,
		-0.29f, -0.86f, 0.0f, 1.0f,0.65f,0.0f,
		-0.38f, -0.99f, 0.0f, 1.0f,0.65f,0.0f,
		//Triángulo Izq abajo
		-0.29f, -0.86f, 0.0f, 1.0f,0.5f,0.0f,
		-0.38f, -0.99f, 0.0f, 1.0f,0.5f,0.0f,
		-0.09f, -0.99f, 0.0f, 1.0f,0.5f,0.0f,

		//Derecha
		//Triángulo Der arriba
		0.27f, -0.86f, 0.0f,  1.0f,0.65f,0.0f,
		0.49f, -0.76f, 0.0f,  1.0f,0.65f,0.0f,
		0.38f, -0.99f, 0.0f,  1.0f,0.65f,0.0f,
		//Triángulo Der abajo
		0.27f, -0.86f, 0.0f,  1.0f,0.5f,0.0f,
		0.38f, -0.99f, 0.0f,  1.0f,0.5f,0.0f,
		0.09f, -0.99f, 0.0f,  1.0f,0.5f,0.0f,
		
		//Pluma Izq
		-0.5f, -0.4f,0.0f,    1.0f,0.5f,0.0f,
		-0.51f, -0.76f, 0.0f, 1.0f,0.5f,0.0f,
		-0.69f, -0.48f, 0.0f, 1.0f,0.5f,0.0f,
		-0.6f, -0.05f, 0.0f,  1.0f,0.5f,0.0f,
		//Pluma Der
		0.45f, -0.4f, 0.0f,   1.0f,0.5f,0.0f,
		0.49f, -0.76f, 0.0f,  1.0f,0.5f,0.0f,
		0.64f, -0.48f, 0.0f,  1.0f,0.5f,0.0f,
		0.51, -0.05f, 0.0f,   1.0f,0.5f,0.0f,

		//Ala Izquierda
		-0.4f, 0.1f, 0.0f,    0.0f,0.2f,0.6f,
		-0.5f, -0.4f,0.0f,    0.0f,0.2f,0.6f,
		-0.6f, -0.05f, 0.0f,  0.0f,0.2f,0.6f,
		-0.65f, -0.26f, 0.0f, 0.0f,0.2f,0.6f,
		-0.9f, -0.38f, 0.0f,  0.0f,0.2f,0.6f,
		-0.73f, -0.1f, 0.0f,  0.0f,0.2f,0.6f,
		//Segunda parte
		-0.73f, -0.1f, 0.0f,  0.4f,0.6f,1.0f,
		-0.9f, -0.38f, 0.0f,  0.4f,0.6f,1.0f,
		-0.99f, -0.38f, 0.0f, 0.4f,0.6f,1.0f,
		-0.88f, -0.1f, 0.0f,  0.4f,0.6f,1.0f,
		//Tercera parte
		-0.88f, -0.1f, 0.0f,  0.0f,0.2f,0.6f,
		-0.73f, -0.1f, 0.0f,  0.0f,0.2f,0.6f,
		-0.4f, 0.1f, 0.0f,    0.0f,0.2f,0.6f,
		-0.15f, 0.47f, 0.0f,  0.0f,0.2f,0.6f,
		-0.47f, 0.33f, 0.0f,  0.0f,0.2f,0.6f,

		//Ala Derecha
		0.32f, 0.1f, 0.0f,    0.0f,0.2f,0.6f,
		0.45f, -0.4f, 0.0f,   0.0f,0.2f,0.6f,
		0.51, -0.05f, 0.0f,   0.0f,0.2f,0.6f,
		0.58f, -0.26f, 0.0f,  0.0f,0.2f,0.6f,
		0.9f, -0.38f, 0.0f,   0.0f,0.2f,0.6f,
		0.71f, -0.1f, 0.0f,   0.0f,0.2f,0.6f,
		//Segunda parte
		0.71f, -0.1f, 0.0f,   0.4f,0.6f,1.0f,
		0.9f, -0.38f, 0.0f,   0.4f,0.6f,1.0f,
		0.99f, -0.38f, 0.0f,  0.4f,0.6f,1.0f,
		0.85f, -0.1f, 0.0f,   0.4f,0.6f,1.0f,
		//Tercera parte
		0.85f, -0.1f, 0.0f,   0.0f,0.2f,0.6f,
		0.71f, -0.1f, 0.0f,   0.0f,0.2f,0.6f,
		0.32f, 0.1f, 0.0f,    0.0f,0.2f,0.6f,
		0.09f, 0.47f, 0.0f,   0.0f,0.2f,0.6f,
		0.38f, 0.33f, 0.0f,   0.0f,0.2f,0.6f,

		//Cuello
		//Izquierda
	    -0.47f, 0.33f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.15f, 0.47f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.30f, 0.59f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.37f, 0.57f, 0.0f, 0.0f, 0.2f, 0.6f,
		//Centro
		-0.15f, 0.47f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.03f, 0.55f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.09f, 0.47f, 0.0f,  0.0f, 0.2f, 0.6f,
		//Derecha
		0.09f, 0.47f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.38f, 0.33f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.27f, 0.57f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.20f, 0.59f, 0.0f, 0.0f, 0.2f, 0.6f,
		//Arriba Izq
		-0.30f, 0.59f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.37f, 0.57f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.35f, 0.68f, 0.0f, 0.0f, 0.2f, 0.6f,
		-0.31f, 0.78f, 0.0f, 0.0f, 0.2f, 0.6f,
		//Arriba Der
		0.20f, 0.59f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.27f, 0.57f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.25f, 0.68f, 0.0f, 0.0f, 0.2f, 0.6f,
		0.21f, 0.78f, 0.0f, 0.0f, 0.2f, 0.6f,
		
		//Cabeza
		//Parte de arriba
		-0.31f, 0.78f, 0.0f, 0.8f, 0.8f, 0.8f,
		-0.28f, 0.88f, 0.0f, 0.8f, 0.8f, 0.8f,
		-0.14f, 0.99f, 0.0f, 0.8f, 0.8f, 0.8f,
		0.07f, 0.99f, 0.0f,	 0.8f, 0.8f, 0.8f,
		0.18f, 0.88f, 0.0f,  0.8f, 0.8f, 0.8f,
		0.21f, 0.78f, 0.0f,  0.8f, 0.8f, 0.8f,
		0.15f, 0.83f, 0.0f,  0.8f, 0.8f, 0.8f,
		0.1f, 0.78f, 0.0f,   0.8f, 0.8f, 0.8f,
		-0.03f, 0.83f, 0.0f, 0.8f, 0.8f, 0.8f,
		-0.16f, 0.78f, 0.0f, 0.8f, 0.8f, 0.8f,
		-0.22f, 0.83f, 0.0f, 0.8f, 0.8f, 0.8f,
		//Pico
		-0.03f, 0.55f, 0.0f, 1.0f, 0.5f, 0.0f,
		-0.15f, 0.64f, 0.0f, 1.0f, 0.5f, 0.0f,
		-0.03f, 0.73f, 0.0f, 1.0f, 0.5f, 0.0f,
		0.09f, 0.64f, 0.0f,  1.0f, 0.5f, 0.0f,
		//OJO izq
		-0.16f, 0.78f, 0.0f, 0.8f, 0.8f, 0.8f,
		-0.11f, 0.67f, 0.0f, 0.8f, 0.8f, 0.8f,
		//Ojo Der
		0.1f, 0.78f, 0.0f, 0.8f, 0.8f, 0.8f,
		0.05f, 0.67f, 0.0f, 0.8f, 0.8f, 0.8f,
		//Pico centro
		-0.03f, 0.6f, 0.0f,  1.0f, 0.65f, 0.0f,
		-0.09f, 0.64f, 0.0f, 1.0f, 0.65f, 0.0f,
		-0.03f, 0.69f, 0.0f, 1.0f, 0.65F, 0.0f,
		0.03f, 0.64f, 0.0f,  1.0f, 0.65f, 0.0f,

		-0.09f, 0.64f, 0.0f, 1.0f, 0.5f, 0.0f,
		0.03f, 0.64f, 0.0f, 1.0f, 0.5f, 0.0f,
		//Ojo dentro izq
		-0.23f, 0.70f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.27f, 0.74f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.23f, 0.78f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.18f, 0.74f, 0.0f, 0.0f, 0.0f, 0.0f,
		//Ojo dentro der
		0.15f, 0.70f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.11f, 0.74f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.15f, 0.78f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.19f, 0.74f, 0.0f, 0.0f, 0.0f, 0.0f,

		//Cara izq
		-0.31f, 0.78f, 0.0f, 1.0f, 1.0f, 1.0f,//124
		-0.22f, 0.83f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.16f, 0.78f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.11f, 0.67f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.15f, 0.64f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.03f, 0.55f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.15f, 0.47f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.30f, 0.59f, 0.0f, 1.0f, 1.0f, 1.0f,
		//Cara Der
		0.21f, 0.78f, 0.0f,  1.0f, 1.0f, 1.0f,//132
		0.15f, 0.83f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.1f, 0.78f, 0.0f,   1.0f, 1.0f, 1.0f,
		0.05f, 0.67f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.09f, 0.64f, 0.0f,  1.0f, 1.0f, 1.0f,
		-0.03f, 0.55f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.09f, 0.47f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.20f, 0.59f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.27f, 0.57f, 0.0f,  1.0f, 1.0f, 1.0f,
		



	};
	unsigned int indices[] = {  // note that we start from 0!
		//Patas
		//Triángulo Izq arriba
		22,23,24,
		//Color primer pentagono
		0,2,3,
		//Color primer trapecio
		7,8,5,
		//Color segundo trapecio izq
		11,12,9,
		//Color tercer trapecio der
		15,16,13,
		//Segundo pentagono
		20,21,17,
		19,20,17,
		//Pluma izq
		36,37,34,
		//Pluma Der
		40,41,38,
		//Ala izq
		44,47,42,
		47,45,44,
		50,51,48,
		52,54,56,
		//Ala der
		57,59,62,
		59,60,62,
		65,66,63,
		67,69,71,
		//Cuello
		72,74,75,
		81,82,79,
		85,86,83,
		89,90,87,
		//Cabeza
		91,92,101,
		94,95,92,
		92,93,101,
		101,93,99,
		99,97,94,
		93,94,99,
		94,95,97,
		//Pico
		104,105,102,
		112,113,110,
		//Cara IZq
		130,131,128,
		124,126,127,
		124,128,131,
		124,126,128,
		//CARA DER
		134,132,136,
		136,139,138,
		136,132,139,

		//Ojo dentro izq
		118,119,116,
		//ojo dentro der
		122,123,120,
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);

		//Primer Pentágono
		glDrawArrays(GL_LINE_LOOP, 0, 5);
		//Color
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

		//Segundo Trapecio
		glDrawArrays(GL_LINE_LOOP, 5, 4);
		//Color
		glDrawArrays(GL_TRIANGLES, 5, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

		//Tercer trapecio Izq
		glDrawArrays(GL_LINE_LOOP, 9, 4);
		glDrawArrays(GL_TRIANGLES, 9, 3);
		//Color
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(9 * sizeof(unsigned int)));

		//Cuarto trapecio Der
		glDrawArrays(GL_LINE_LOOP, 13, 4);
		glDrawArrays(GL_TRIANGLES, 13, 3);
		//Color
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));

		//Pentágono
		glDrawArrays(GL_LINE_LOOP, 17, 5);
		//Color
		glDrawArrays(GL_TRIANGLES, 17, 3);

		//Pata Izquierda Arriba
		glDrawElements(GL_TRIANGLES, 22,GL_UNSIGNED_INT,0);
		//Pata Izquierda Abajo
		glDrawArrays(GL_TRIANGLES, 25, 3);

		//Pata Derecha Arriba
		glDrawArrays(GL_TRIANGLES, 28, 3);
		//Pata Derecha Abajo
		glDrawArrays(GL_TRIANGLES, 31, 3);

		//Pluma Izq
		glDrawArrays(GL_LINE_LOOP, 34, 4);
		//Color
		glDrawArrays(GL_TRIANGLES, 34, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(21 * sizeof(unsigned int)));
		//Pluma Der
		glDrawArrays(GL_LINE_LOOP, 38, 4);
		//Color
		glDrawArrays(GL_TRIANGLES, 38, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));

		//Ala izquierda
		glDrawArrays(GL_LINE_LOOP, 42, 6);
		glDrawArrays(GL_LINE_LOOP, 48, 4);
		glDrawArrays(GL_LINE_LOOP, 52, 5);
		//Color
		glDrawArrays(GL_TRIANGLES, 42, 3);
		glDrawArrays(GL_TRIANGLES, 45, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(27 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 48, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(33 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 52, 3);
		glDrawArrays(GL_TRIANGLES, 54, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(36 * sizeof(unsigned int)));

		//Ala Derecha
		glDrawArrays(GL_LINE_LOOP, 57, 6);
		glDrawArrays(GL_LINE_LOOP, 63, 4);
		glDrawArrays(GL_LINE_LOOP, 67, 5);
		//Color
		glDrawArrays(GL_TRIANGLES, 57, 3);
		glDrawArrays(GL_TRIANGLES, 60, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(39 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(42 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 63, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(45 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 67, 3);
		glDrawArrays(GL_TRIANGLES, 69, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(48 * sizeof(unsigned int)));


		//Cuello
		glDrawArrays(GL_LINE_LOOP, 72, 4);
		glDrawArrays(GL_TRIANGLES, 76, 3);
		glDrawArrays(GL_LINE_LOOP, 79, 4);
		glDrawArrays(GL_LINE_LOOP, 83, 4);
		glDrawArrays(GL_LINE_LOOP, 87, 4);
		//Color
		glDrawArrays(GL_TRIANGLES, 72, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(51 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 79, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(54 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 83, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(57 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 87, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(60 * sizeof(unsigned int)));

		//Cabeza
		glDrawArrays(GL_LINE_LOOP, 91, 11);
		//PICO
		//Color
		glDrawArrays(GL_TRIANGLES, 102, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(84 * sizeof(unsigned int)));

		//CARA izq color
		glDrawArrays(GL_LINES, 106, 2);
		glDrawArrays(GL_TRIANGLES, 124, 3);
		glDrawArrays(GL_TRIANGLES, 126, 3);
		glDrawArrays(GL_TRIANGLES, 128, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(90 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(93 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(96 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(99 * sizeof(unsigned int)));

		//Cara Der color
		glDrawArrays(GL_LINES, 108, 2);
		glDrawArrays(GL_TRIANGLES, 132, 3);
		glDrawArrays(GL_TRIANGLES, 134, 3);
		glDrawArrays(GL_TRIANGLES, 136, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(102 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(105 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(108 * sizeof(unsigned int)));
		

		// PICO CENTRO
		glDrawArrays(GL_TRIANGLES, 110, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(87 * sizeof(unsigned int)));

		glDrawArrays(GL_LINES, 114, 2);
		//Color
		glDrawArrays(GL_TRIANGLES, 92, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(63 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(66 * sizeof(unsigned int)));
		glDrawArrays(GL_TRIANGLES, 95, 3);
		glDrawArrays(GL_TRIANGLES, 97, 3);
		glDrawArrays(GL_TRIANGLES, 99, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(69 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(72 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(75 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(78 * sizeof(unsigned int)));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(81 * sizeof(unsigned int)));


		//Ojo dentro Izq
		glDrawArrays(GL_TRIANGLES, 116, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(111 * sizeof(unsigned int)));
		
		//Ojo dentro der
		glDrawArrays(GL_TRIANGLES, 120, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(114 * sizeof(unsigned int)));
		

		//Punto azul en el origen
        glPointSize(10);     
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}