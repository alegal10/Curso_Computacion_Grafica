//Práctica 2                Galindo Granados Abner Alejandro
//Fecha de entrega:         320001567
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
		//Primer Trapecio
		-0.4f, 0.1f, 0.0f,    0.0f,0.0f,1.0f,
		-0.5f, -0.4f,0.0f,    0.0f,0.0f,1.0f,
		0.0f, -0.6f, 0.0f,    0.0f,0.0f,1.0f,
		0.45f, -0.4f, 0.0f,   0.0f,0.0f,1.0f,
		0.32f, 0.1f, 0.0f,    0.0f,0.0f,1.0f,

		//Segundo Trapecio
		-0.4f, 0.1f, 0.0f,    0.0f,0.0f,1.0f,
		0.32f, 0.1f, 0.0f,    0.0f,0.0f,1.0f,
		0.09f, 0.47f, 0.0f,   0.0f,0.0f,1.0f,
		-0.15f, 0.47f, 0.0f,  0.0f,0.0f,1.0f,

		//Tercer trapacio izq
		-0.5f, -0.4f, 0.0f,  0.0f,0.0f,1.0f,
		-0.51f, -0.76f, 0.0f, 0.0f,0.0f,1.0f,
		-0.29f, -0.86f, 0.0f, 0.0f,0.0f,1.0f,
		0.0f, -0.6f, 0.0f,    0.0f,0.0f,1.0f,

		//Cuarto trapecio der
		0.0f, -0.6f, 0.0f,    0.0f,0.0f,1.0f,
		0.45f, -0.4f, 0.0f,   0.0f,0.0f,1.0f,
		0.49f, -0.76f, 0.0f,  0.0f,0.0f,1.0f,
		0.27f, -0.86f, 0.0f,  0.0f,0.0f,1.0f,

		//Pentagono
		0.0f, -0.6f, 0.0f,    0.0f,0.0f,1.0f,
		-0.29f, -0.86f, 0.0f, 0.0f,0.0f,1.0f,
		-0.09f, -0.99f, 0.0f,   0.0f,0.0f,1.0f,
		0.09f, -0.99f, 0.0f,   0.0f,0.0f,1.0f,
		0.27f, -0.86f, 0.0f,  0.0f,0.0f,1.0f,

		//Patas
		//Izquierda
		//Triángulo Izq arriba
		-0.51f, -0.76f, 0.0f, 0.0f,0.0f,1.0f,
		-0.29f, -0.86f, 0.0f, 0.0f,0.0f,1.0f,
		-0.38f, -0.99f, 0.0f,  0.0f,0.0f,1.0f,
		//Triángulo Izq abajo
		-0.29f, -0.86f, 0.0f, 0.0f,0.0f,1.0f,
		-0.38f, -0.99f, 0.0f,  0.0f,0.0f,1.0f,
		-0.09f, -0.99f, 0.0f,   0.0f,0.0f,1.0f,

		//Derecha
		//Triángulo Der arriba
		0.27f, -0.86f, 0.0f,  0.0f,0.0f,1.0f,
		0.49f, -0.76f, 0.0f,  0.0f,0.0f,1.0f,
		0.38f, -0.99f, 0.0f,  0.0f,0.0f,1.0f,
		//Triángulo Der abajo
		0.27f, -0.86f, 0.0f,  0.0f,0.0f,1.0f,
		0.38f, -0.99f, 0.0f,  0.0f,0.0f,1.0f,
		0.09f, -0.99f, 0.0f,   0.0f,0.0f,1.0f,
		
		//Pluma Izq
		-0.5f, -0.4f,0.0f,    0.0f,0.0f,1.0f,
		-0.51f, -0.76f, 0.0f, 0.0f,0.0f,1.0f,
		-0.69f, -0.48f, 0.0f, 0.0f,0.0f,1.0f,
		-0.6f, -0.05f, 0.0f,  0.0f,0.0f,1.0f,
		//Pluma Der
		0.45f, -0.4f, 0.0f,   0.0f,0.0f,1.0f,
		0.49f, -0.76f, 0.0f,  0.0f,0.0f,1.0f,
		0.64f, -0.48f, 0.0f,  0.0f,0.0f,1.0f,
		0.51, -0.05f, 0.0f,   0.0f,0.0f,1.0f,



		0.5f,  0.5f, 0.0f,    0.0f,0.0f,1.0f,  // top right
		0.5f, -0.5f, 0.0f,    0.0f,1.0f,0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f,0.0f,0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f,0.0f,1.0f, // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		//Patas
		//Triángulo Izq arriba
		22,23,24,
		//0,1,3,
		
		
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

		//Primer Trapecio
		glDrawArrays(GL_LINE_LOOP, 0, 5);

		//Segundo Trapecio
		glDrawArrays(GL_LINE_LOOP, 5, 4);

		//Tercer trapecio Izq
		glDrawArrays(GL_LINE_LOOP, 9, 4);

		//Cuarto trapecio Der
		glDrawArrays(GL_LINE_LOOP, 13, 4);

		//Pentágono
		glDrawArrays(GL_LINE_LOOP, 17, 5);

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
		//Pluma Der
		glDrawArrays(GL_LINE_LOOP, 38, 4);

		//Punto azul en el origen
        glPointSize(10);
		//Tres puntos del arreglo comenzando por el elemento 1
        //glDrawArrays(GL_POINTS,1,3);
        
		//Se dibuja una linea desde el elemento 2
        //glDrawArrays(GL_LINES,2,2);
		
		// Se dibuja un cuadrado
        //glDrawArrays(GL_LINE_LOOP,0,5);
        
		//Triangulo desde el elemento 1
        //glDrawArrays(GL_TRIANGLES,1,3);{
		
		//Triangulos con elementos tomados manualmente
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
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