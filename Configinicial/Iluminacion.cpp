//Práctica 8                                      Galindo Granados Abner Alejandro
//Fecha de entrega: 29 de marzo 2026              320001567
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 lightPos(0.5f, 4.0f, 0.0f);
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

float lightAngle = 3.1416f;
float lightRadius = 8.0f;
bool modoDia = true;        

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Galindo Granados Abner Alejandro", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag");
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model red_dog((char*)"Models/RedDog.obj");
    Model car((char*)"Models/carro.obj");
    Model aeropuerto((char*)"Models/aeropuerto.obj");
    Model humano((char*)"Models/humano.obj");
    Model maleta((char*)"Models/maleta.obj");
    Model moon((char*)"Models/Moon.obj");
    Model sun((char*)"Models/sun.obj");

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    image = stbi_load("Models/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        if(modoDia)
            glClearColor(0.3f, 0.5f, 0.7f, 1.0f);
		else
            glClearColor(0.05f, 0.05f, 0.15f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // --- Cálculo de trayectoria circular --
        lightPos.x = cos(lightAngle) * lightRadius;
        lightPos.y = sin(lightAngle) * lightRadius;
        lightPos.z = 0.0f;

        lightingShader.Use();
        
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        if (modoDia) {
            GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.4f, 0.4f, 0.35f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 1.0f, 0.95f, 0.8f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 0.9f);
            //Material
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
        }
        else {
            GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.1f, 0.1f, 0.2f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.4f, 0.4f, 0.7f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.9f, 0.9f, 1.0f);
            //Material
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.7f, 0.7f, 0.7f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.7f, 0.7f, 0.7f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.8f, 0.8f, 1.0f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);
        }
        
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        // --- Dibujar Aeropuerto ---
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        aeropuerto.Draw(lightingShader);

        // --- Dibujar Humano ---
        model = glm::translate(model, glm::vec3(1000.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        humano.Draw(lightingShader);

        //--- Dibujar Maleta ---
        glm::mat4 modelmaleta = glm::mat4(1.0f);
        modelmaleta = glm::scale(modelmaleta, glm::vec3(0.05f, 0.05f, 0.05f));
        modelmaleta = glm::translate(modelmaleta, glm::vec3(20.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelmaleta));
        maleta.Draw(lightingShader);

        //---Dibujar Carro---
        glm::mat4 modelcarro = glm::mat4(1.0f);
        modelcarro = glm::translate(modelcarro, glm::vec3(1.0f, 0.0f, 0.5f));
        modelcarro = glm::scale(modelcarro, glm::vec3(0.2f, 0.2f, 0.2f));
        modelcarro = glm::rotate(modelcarro, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelcarro));
        car.Draw(lightingShader);

        //Dibujar Perro
        glm::mat4 modelperro = glm::mat4(1.0f);
        modelperro = glm::translate(modelperro, glm::vec3(1.05f, 0.03f, 0.0f));
        modelperro = glm::scale(modelperro, glm::vec3(0.07f, 0.07f, 0.07f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelperro));
        red_dog.Draw(lightingShader);

        glBindVertexArray(0);


        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  
        if (modoDia) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.7f));
            glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            sun.Draw(lampshader);  // Solo se dibuja el sol
        }
        else {
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos); // La posición de la nueva luz
            model = glm::scale(model, glm::vec3(0.2f));
            glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            moon.Draw(lampshader); // Solo se dibuja la luna
        }
          
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (activanim)
    {
        if (rot > -90.0f)
            rot -= 0.1f;
    }

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        modoDia = !modoDia;
    }

    if (keys[GLFW_KEY_O])
    {
       
       lightAngle += 0.1f;
    }

    if (keys[GLFW_KEY_L])
    {
        
        lightAngle -= 0.1f;
    }
    if (lightAngle > 3.14159f) lightAngle = 3.14159f;
    if (lightAngle < 0.0f) lightAngle = 0.0f;
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


