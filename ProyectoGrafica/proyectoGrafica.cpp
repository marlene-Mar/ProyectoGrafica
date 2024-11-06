/* PROYECTO DE COMPUTACIÓN GRÁFICA E INTERACCIÓN HUMANO COMPUTADORA
* SEMESTRE 2025-1 
* EQUIPO 2 
* INTEGRANTES: 
* Azuara López Laura Paola 
* De la Cruz Padilla Marlene Mariana 
* Domínguez Reyes Cynthia Berenice
*/

// Std. Includes
#include <string>
#include <iostream>
#include <cmath>

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
const GLuint WIDTH = 1200, HEIGHT = 1000;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 10.0f, 20.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//////////////////ANIMACIÓN ALBERCA////////////////

float tiempo; //Variable para caluclar el tiempo de animación
bool dir = true; //Varirble para verificar el cambio en tiempo

//////////////////////////////////////////////////

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f,2.0f, 0.0f),
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f,  0.0f),
    glm::vec3(0.0f,0.0f, 0.0f)
};


glm::vec3 Light1 = glm::vec3(0);

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Grafica - Hotel OASIS DEL SOL", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    //////////////////ANIMACIÓN ALBERCA////////////////

    //Sheaders de control de animación para el agua y el flotador 
    Shader AlbShader("Shader/shaderAgua.vs", "Shader/shaderAgua.frag");
    Shader FlotShader("Shader/ShaderFlotador.vs", "Shader/ShaderFlotador.frag");

    ///////////////////////////////////////////////////
    
    // Load models
    Model areaAlberca((char*)"Models/AreaAlberca.obj");
    Model agua((char*)"Models/agua.obj");
    Model flotador((char*)"Models/flotador.obj");
    Model edificio((char*)"Models/EdificioPrincipal.obj");
    Model cristales((char*)"Models/Cristales.obj");
    Model suelo((char*)"Models/Plano.obj");
    Model areaJuegos((char*)"Models/areaJuegos.obj");
    Model spa((char*)"Models/areaSpa/spaCompleto2.obj"); 
    Model pelota((char*)"Models/areaGYM/ball.obj");

    
    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // Set texture units
    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //////////////////ANIMACIÓN ALBERCA////////////////

        if (dir) { //Si existe un cambio de la dirección del tiempo
            tiempo += deltaTime; //Se incrementa el tiempo con deltaTime
            if (tiempo >= 14.0f) {  // Limite del valor máximo del tiempo
                tiempo = 14.0f; //Tiempo máximo = 14
                dir = false; //Cambia el valor de dir 
            }
        }
        else { //Disminuye el tiempo
            tiempo -= deltaTime; //Se reduce el tiempo con deltaTime
            if (tiempo <= -14.0f) { // Limite del valor minimo del tiempo
                tiempo = -14.0f; //Tiempo minimo = -14
                dir = true; //Cambia el valor de dir
            }
        }

        ///////////////////////////////////////////////////

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        // OpenGL options
        glEnable(GL_DEPTH_TEST);

        lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


        // Point light 1
        glm::vec3 lightColor;
        lightColor.x = abs(sin(glfwGetTime() * Light1.x));
        lightColor.y = abs(sin(glfwGetTime() * Light1.y));
        lightColor.z = sin(glfwGetTime() * Light1.z);


        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.1f, 0.0f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.1f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.1f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.5f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(0.1f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(0.1f)));

       

        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");


        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the loaded model
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        
        ////////////// PLANO DEL SUELO ///////////////
        glm::mat4 modelSuelo(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSuelo));
        suelo.Draw(lightingShader);


        ////////////// EDIFICIO sin transparencia en ventanas y con mal texturizado en su suelo ///////////////
        glm::mat4 modelEdificio(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelEdificio));
        edificio.Draw(lightingShader);

        glm::mat4 modelCristales(1);
        glEnable(GL_BLEND); //Activa la funcionalidad para trabajar en el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1); //Se pone 1 para poder visualizar la transparencia 
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCristales));
        cristales.Draw(lightingShader);
        glDisable(GL_BLEND);
    
        //Modelo de area alberca
        glm::mat4 modelAlberca(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelAlberca));
        areaAlberca.Draw(lightingShader);


       /////////////////////Modelo de area juegos////////////////
       
        glm::mat4 modelJuegos(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelJuegos));
        areaJuegos.Draw(lightingShader);
     

        ////////////////////Modelo pelota////////////////
        glm::mat4 modelPelota(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPelota));
        pelota.Draw(lightingShader);


        ////////////////////////ÁREA SPA/////////////////////////
        glm::mat4 modelSpa(1);
        modelSpa = glm::translate(model, glm::vec3(12.433f, 0.0f, -9.896f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelSpa));
        spa.Draw(lightingShader);

  
        ////////////////////////////////////////////////////////////
        

        //////////////////ANIMACIÓN ALBERCA////////////////

        AlbShader.Use(); //Llama al shader de shaderAgua

        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        viewLoc = glGetUniformLocation(AlbShader.Program, "view");
        projLoc = glGetUniformLocation(AlbShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Modelo agua de la alberca
        glm::mat4 modelAgua(1);
        glEnable(GL_BLEND); //Activa la funcionalidad para trabajar en el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAgua));
        glUniform1i(glGetUniformLocation(AlbShader.Program, "transparency"), 1); //Se pone 1 para poder visualizar la transparencia 
        glUniformMatrix4fv(glGetUniformLocation(AlbShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelAgua));
        glUniform1f(glGetUniformLocation(AlbShader.Program, "time"), tiempo); //Se envia el valor de tiempo al shader
        agua.Draw(AlbShader);
        glDisable(GL_BLEND);

        FlotShader.Use(); // Llama al shader de ShaderFlotador

        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        viewLoc = glGetUniformLocation(FlotShader.Program, "view");
        projLoc = glGetUniformLocation(FlotShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Modelo del flotador
        glm::mat4 modelFlotador(1);
        glUniformMatrix4fv(glGetUniformLocation(FlotShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelFlotador));
        glUniform1f(glGetUniformLocation(FlotShader.Program, "time"), tiempo); //Se envia el valor de tiempo al shader
        flotador.Draw(FlotShader);


        ///////////////////////////////////////////////////
      
        // Swap the buffers
        glDeleteVertexArrays(1, &VAO);
        glfwSwapBuffers( window ); 
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

