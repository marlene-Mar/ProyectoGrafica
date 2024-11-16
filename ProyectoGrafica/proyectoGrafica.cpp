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

//libreria para el skybox
#include "Texture.h"

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
void BallAnimation(); // Nueva función para la animación de la pelota
void Animation(); //Función para los frames 


// Camera
Camera camera( glm::vec3( 0.0f, 10.0f, 20.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

//Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//////////////////ANIMACIÓN ALBERCA////////////////

float tiempo; //Variable para caluclar el tiempo de animación
bool dir = true; //Varirble para verificar el cambio en tiempo

//////////////////////////////////////////////////


/////////////////////////////// ANIMACIÓN AVE ///////////////////////////////////

bool animAve = false;
//int animAve = 0;

float cola = 0.0f;
float cuerpo = 0.0f;
float alaDer = 0.0f;
float alaIzq = 0.0f;
glm::vec3 avePos(-3.411f, 1.346f, 10.143f); // posición inicial del ave 
bool step = false;
float rotPaj = 0.0f;
//float avePosX = -3.411f;
//float avePosY = 1.346f;
//float avePosZ = 10.143f;

//-----------------------ANIMACION BOY-------------------------------

bool animBoy = false;

glm::vec3 boyPos(-12.768f, 0.913f, -8.331f); // posición inicial del ave  

float cuerpoBoy = 0.0f;
float pantIzq= 0.0f; 
float pantDer = 0.0f;
float piernaIzq = 0.0f;
float piernaDer = 0.0f;
float brazoDer = 0.0f;
float brazoIzq = 0.0f;
float bicepDer = 0.0f;
float bicepIzq = 0.0f;

//patineta
float skate = 0.0f;


bool stepBoy = false;
float rotBoy = 0.0f;


//////////////////////////////////////////////////////////

/////////////////////// FRAMES ///////////////////////////

//Variables para las animaciones por KeyFrames 

//--------------------AVE-------------------------------
float rotPajX = 0; //Variable para rotación

/*Variables de posición */
//KeyFrames
//float avePosX, avePosY, avePosZ;

float avePosX = -3.411f;
float avePosY = 1.346f;
float avePosZ = 10.143f;

//--------------------BOY-------------------------------
float rotBoyX = 0; //Variable para rotación

float boyPosX = -12.768f;
float boyPosY = 0.913f;
float boyPosZ = -8.331f;

//patineta

float sktPosX = -12.788f; 
float sktPosY = 0.118f;    
float sktPosZ = -7.11f;    


#define MAX_FRAMES 50 //Cuadros permitidos para grabar
int i_max_steps = 190;
int i_curr_steps = 0; // linea de tiempo que vamos a utilizar

//variables que controlan al modelo
typedef struct _frame {

    //rotación del ave
    float rotPaj;
    float rotPajInc;

    //rotacion del niño
    float rotBoy;
    float rotBoyInc;

    //posicion del ave
    float avePosX;
    float avePosY;
    float avePosZ;


    float incX; //cambio que hay desde un keyframe a otro //incremento que hay en la línea de tiempo. 
    float incY;
    float incZ;

    //-----------------------AVE---------------------------

    // ------------------------- CUERPO ----------------*
    float cuerpo;
    float cuerpoInc;

    // ---------------------- COLA ------------------* 
    float cola;
    float colaInc;
    //--------------------- ALA DERECHA ------------*

    float alaDer;
    float alaDerInc;


    //------------------- ALA IZQUIERDA ---------------------*
    float alaIzq;
    float alaIzqInc;


    //Variables para la rotación
    float rotPajX; //////////// rotación en x 
    float rotPajXInc;


    //-----------------------BOY----------------------------
   


    //Variables rotación niño
    float rotBoyX; //////////// rotación en x 
    float rotBoyXInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false; //indicador de si se reproduce o no la animación
int playIndex = 0; //indica en que paso de la animación se encuentra el modelo 


//Frame BOY
typedef struct _frameBoy {
    float incX; //cambio que hay desde un keyframe a otro //incremento que hay en la línea de tiempo. 
    float incY;
    float incZ;

    float boyPosX, boyPosY, boyPosZ;
    float sktPosX, sktPosY, sktPosZ;
    float rotBoy;
    float rotBoyInc;
    float rotBoyX;
    float rotBoyXInc;
    float cuerpoBoy;
    float cuerpoBoyInc;
    float pantIzq;
    float pantIzqInc;
    float pantDer;
    float pantDerInc;
    float piernaDer;
    float piernaDerInc;
    float piernaIzq;
    float piernaIzqInc;
    float brazoDer;
    float brazoDerInc;
    float brazoIzq;
    float brazoIzqInc;
    float bicepDer;
    float bicepDerInc;
    float bicepIzq;
    float bicepIzqInc;


} FRAME_BOY;

#define MAX_FRAMES_BOY 50
FRAME_BOY KeyFrameBoy[MAX_FRAMES_BOY];
int FrameIndexBoy = 0; // Índice de KeyFrames del niño
int playIndexBoy = 0;  // Índice de reproducción para el niño
bool playBoy = false;  // Bandera para controlar la animación del niño
int i_curr_steps_boy = 0; // Pasos actuales en la interpolación del niño





//FUnción que guarda toda esa función //GUARDA LOS KEYFRAMES

//Función para guardar los datos de un archivo de texto 
void saveAnimation(const char* filename = "animKeyF.txt") {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar." << std::endl;
        return;
    }

    for (int i = 0; i < FrameIndex; i++) {
        file << KeyFrame[i].avePosX << " "
            << KeyFrame[i].avePosY << " "
            << KeyFrame[i].avePosZ << " "
            << KeyFrame[i].rotPaj << " "
            << KeyFrame[i].cuerpo << " "
            << KeyFrame[i].cola << " "
            << KeyFrame[i].alaDer << " "
            << KeyFrame[i].alaIzq << " "
            << KeyFrame[i].rotPajX << "\n";
    }
    file.close();
    std::cout << "Animación guardada" << std::endl;
}


// Función para cargar los KeyFrames ---AVE
void obtenerAnimation(const char* filename = "animKeyF.txt") {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar." << std::endl;
        return;
    }

    FrameIndex = 0;
    while (FrameIndex < MAX_FRAMES &&
        file
        >> KeyFrame[FrameIndex].avePosX
        >> KeyFrame[FrameIndex].avePosY
        >> KeyFrame[FrameIndex].avePosZ
        >> KeyFrame[FrameIndex].rotPaj
        >> KeyFrame[FrameIndex].cuerpo
        >> KeyFrame[FrameIndex].cola
        >> KeyFrame[FrameIndex].alaDer
        >> KeyFrame[FrameIndex].alaIzq
        >> KeyFrame[FrameIndex].rotPajX){
        FrameIndex++;
    }
}


void saveFrame(void)
{

    printf("frameindex %d\n", FrameIndex);

    //Guarda el estado actual del modelo en la estructura que se definio previamente 
    KeyFrame[FrameIndex].avePosX = avePosX;
    KeyFrame[FrameIndex].avePosY = avePosY;
    KeyFrame[FrameIndex].avePosZ = avePosZ;

    KeyFrame[FrameIndex].rotPaj = rotPaj;

    //variables para la cabeza 
    KeyFrame[FrameIndex].cuerpo = cuerpo;
    //printf("%.2f", KeyFrame[FrameIndex].head); //nos imprime los valores que vamos a necesitar guardar en el archivo para ejecutar el keyframe 

    //Cola
    KeyFrame[FrameIndex].cola = cola;

    //----------------------------- ALAS -------------* 

    KeyFrame[FrameIndex].alaDer = alaDer;
    KeyFrame[FrameIndex].alaIzq = alaIzq;


    //imprimir el frame para observar los datos que nos da, estos valores son los que se van a guardar en el archivo 

    FrameIndex++;


}

//////////////////////BOY KEYFRAMES///////////////////////////////////////////

// Función para guardar los datos de un archivo de texto --BOY
void saveAnimation2(const char* filename = "animBoy.txt") {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar." << std::endl;
        return;
    }

    for (int i = 0; i < FrameIndexBoy; i++) {
        file
            << KeyFrameBoy[i].boyPosX << " "
            << KeyFrameBoy[i].boyPosY << " "
            << KeyFrameBoy[i].boyPosZ << " "
            << KeyFrameBoy[i].sktPosX << " "
            << KeyFrameBoy[i].sktPosY << " "
            << KeyFrameBoy[i].sktPosZ << " "
            << KeyFrameBoy[i].rotBoy << " "
            << KeyFrameBoy[i].cuerpoBoy << " "
            << KeyFrameBoy[i].pantIzq << " "
            << KeyFrameBoy[i].pantDer << " "
            << KeyFrameBoy[i].piernaIzq << " "
            << KeyFrameBoy[i].piernaDer << " "
            << KeyFrameBoy[i].brazoIzq << " "
            << KeyFrameBoy[i].brazoDer << " "
            << KeyFrameBoy[i].bicepIzq << " "
            << KeyFrameBoy[i].bicepDer << " "
            << KeyFrameBoy[i].rotBoyX << "\n";
    }
    file.close();
    std::cout << "Animación boy guardada" << std::endl;

}


//Función para cargar los KeyFrames ---BOY
void obtenerAnimation2(const char* filename = "animBoy.txt") {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar." << std::endl;
        return;
    }

    FrameIndexBoy = 0;
    while (FrameIndexBoy < MAX_FRAMES_BOY &&
        file
        >> KeyFrameBoy[FrameIndexBoy].boyPosX
        >> KeyFrameBoy[FrameIndexBoy].boyPosY
        >> KeyFrameBoy[FrameIndexBoy].boyPosZ
        >> KeyFrameBoy[FrameIndexBoy].sktPosX
        >> KeyFrameBoy[FrameIndexBoy].sktPosY
        >> KeyFrameBoy[FrameIndexBoy].sktPosZ
        >> KeyFrameBoy[FrameIndexBoy].rotBoy
        >> KeyFrameBoy[FrameIndexBoy].cuerpoBoy
        >> KeyFrameBoy[FrameIndexBoy].pantIzq
        >> KeyFrameBoy[FrameIndexBoy].pantDer
        >> KeyFrameBoy[FrameIndexBoy].piernaIzq
        >> KeyFrameBoy[FrameIndexBoy].piernaDer
        >> KeyFrameBoy[FrameIndexBoy].brazoIzq
        >> KeyFrameBoy[FrameIndexBoy].brazoDer
        >> KeyFrameBoy[FrameIndexBoy].bicepIzq
        >> KeyFrameBoy[FrameIndexBoy].bicepDer
        >> KeyFrameBoy[FrameIndexBoy].rotBoyX) {
        FrameIndexBoy++;
    }
}



void saveFrameBoy(void)
{

    printf("frameindex %d\n", FrameIndexBoy);


    //-----------------------------BOY-------------------------------
    KeyFrameBoy[FrameIndexBoy].boyPosX = boyPosX;
    KeyFrameBoy[FrameIndexBoy].boyPosY = boyPosY;
    KeyFrameBoy[FrameIndexBoy].boyPosZ = boyPosZ;

    //patineta
    KeyFrameBoy[FrameIndexBoy].sktPosX = sktPosX;
    KeyFrameBoy[FrameIndexBoy].sktPosY = sktPosY;
    KeyFrameBoy[FrameIndexBoy].sktPosZ = sktPosZ;

    //partes del cuerpo
    KeyFrameBoy[FrameIndexBoy].rotBoy = rotBoy;
    KeyFrameBoy[FrameIndexBoy].rotBoyX = rotBoyX;

    KeyFrameBoy[FrameIndexBoy].cuerpoBoy = cuerpoBoy;
    KeyFrameBoy[FrameIndexBoy].pantIzq = pantIzq;
    KeyFrameBoy[FrameIndexBoy].pantDer = pantDer;
    KeyFrameBoy[FrameIndexBoy].piernaIzq = piernaIzq;
    KeyFrameBoy[FrameIndexBoy].piernaDer = piernaDer;
    KeyFrameBoy[FrameIndexBoy].brazoIzq = brazoIzq;
    KeyFrameBoy[FrameIndexBoy].brazoDer = brazoDer;
    KeyFrameBoy[FrameIndexBoy].bicepIzq = bicepIzq;
    KeyFrameBoy[FrameIndexBoy].bicepDer = bicepDer;


    //imprimir el frame para observar los datos que nos da, estos valores son los que se van a guardar en el archivo 

    FrameIndexBoy++;

}

//Función que reinicia a la posicióninicial 
void resetElements(void)
{
    //--------------------------AVE---------------------
    avePosX = KeyFrame[0].avePosX;
    avePosY = KeyFrame[0].avePosY;
    avePosZ = KeyFrame[0].avePosZ;

    //rotaciones
    rotPaj = KeyFrame[0].rotPaj;
    rotPajX = KeyFrame[0].rotPajX;

    //variable para el cuerpo
    cuerpo = KeyFrame[0].cuerpo; //inicializamos

    //variable cola
    cola = KeyFrame[0].cola;

    //Alas 
    alaDer = KeyFrame[0].alaDer;
    alaIzq = KeyFrame[0].alaIzq;


}

//Función que reinicia a la posicióninicial 
void resetElementsBoy(void)
{
    //--------------------------BOY--------------------

    boyPosX = KeyFrameBoy[0].boyPosX;
    boyPosY = KeyFrameBoy[0].boyPosY;
    boyPosZ = KeyFrameBoy[0].boyPosZ;

    //patineta
    sktPosX = KeyFrameBoy[0].sktPosX;
    sktPosY = KeyFrameBoy[0].sktPosY;
    sktPosZ = KeyFrameBoy[0].sktPosZ;

    //Partes del cuerpo

    //rotaciones
    rotBoy = KeyFrameBoy[0].rotBoy;
    rotBoyX = KeyFrameBoy[0].rotBoyX;

    cuerpoBoy = KeyFrameBoy[0].cuerpoBoy;
    pantDer = KeyFrameBoy[0].pantDer;
    pantIzq = KeyFrameBoy[0].pantIzq;
    piernaIzq = KeyFrameBoy[0].piernaIzq;
    piernaDer = KeyFrameBoy[0].piernaDer;
    brazoIzq = KeyFrameBoy[0].brazoIzq;
    brazoDer = KeyFrameBoy[0].brazoDer;
    bicepIzq = KeyFrameBoy[0].bicepIzq;
    bicepDer = KeyFrameBoy[0].bicepDer;

}

//diferencia en las variables (rotaciones y posiciones) //REPRODUCE LOS KEFRAMES
void interpolation(void)
{

    KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].avePosX - KeyFrame[playIndex].avePosX) / i_max_steps;
    KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].avePosY - KeyFrame[playIndex].avePosY) / i_max_steps;
    KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].avePosZ - KeyFrame[playIndex].avePosZ) / i_max_steps;
    //ROTACIONES
    KeyFrame[playIndex].rotPajInc = (KeyFrame[playIndex + 1].rotPaj - KeyFrame[playIndex].rotPaj) / i_max_steps;
    KeyFrame[playIndex].rotPajXInc = (KeyFrame[playIndex + 1].rotPaj - KeyFrame[playIndex].rotPajX) / i_max_steps;

    //variable para la cabeza
    KeyFrame[playIndex].cuerpoInc = (KeyFrame[playIndex + 1].cuerpo - KeyFrame[playIndex].cuerpo) / i_max_steps;

    //variable cola
    KeyFrame[playIndex].colaInc = (KeyFrame[playIndex + 1].cola - KeyFrame[playIndex].cola) / i_max_steps;


    //----------------------- ALAS

    //variable pata derecha

    KeyFrame[playIndex].alaDerInc = (KeyFrame[playIndex + 1].alaDer - KeyFrame[playIndex].alaDer) / i_max_steps;
    KeyFrame[playIndex].alaIzqInc = (KeyFrame[playIndex + 1].alaIzq - KeyFrame[playIndex].alaIzq) / i_max_steps;


}

void interpolationBoy(void)
{
    //------------------------------BOY---------------------------
    KeyFrameBoy[playIndexBoy].incX = (KeyFrameBoy[playIndexBoy + 1].boyPosX - KeyFrameBoy[playIndexBoy].boyPosX) / i_max_steps;
    KeyFrameBoy[playIndexBoy].incY = (KeyFrameBoy[playIndexBoy + 1].boyPosY - KeyFrameBoy[playIndexBoy].boyPosY) / i_max_steps;
    KeyFrameBoy[playIndexBoy].incZ = (KeyFrameBoy[playIndexBoy + 1].boyPosZ - KeyFrameBoy[playIndexBoy].boyPosZ) / i_max_steps;

    KeyFrameBoy[playIndexBoy].incX = (KeyFrameBoy[playIndexBoy + 1].sktPosX - KeyFrameBoy[playIndexBoy].sktPosX) / i_max_steps;
    KeyFrameBoy[playIndexBoy].incY = (KeyFrameBoy[playIndexBoy + 1].sktPosY - KeyFrameBoy[playIndexBoy].sktPosY) / i_max_steps;
    KeyFrameBoy[playIndexBoy].incZ = (KeyFrameBoy[playIndexBoy + 1].sktPosZ - KeyFrameBoy[playIndexBoy].sktPosZ) / i_max_steps;

    KeyFrameBoy[playIndexBoy].rotBoyInc = (KeyFrameBoy[playIndexBoy + 1].rotBoy - KeyFrameBoy[playIndexBoy].rotBoy) / i_max_steps;
    KeyFrameBoy[playIndexBoy].rotBoyXInc = (KeyFrameBoy[playIndexBoy + 1].rotBoyX - KeyFrameBoy[playIndexBoy].rotBoyX) / i_max_steps;

    KeyFrameBoy[playIndexBoy].cuerpoBoyInc = (KeyFrameBoy[playIndexBoy + 1].cuerpoBoy - KeyFrameBoy[playIndexBoy].cuerpoBoy) / i_max_steps;
    KeyFrameBoy[playIndexBoy].pantDerInc = (KeyFrameBoy[playIndexBoy + 1].pantDer - KeyFrameBoy[playIndexBoy].pantDer) / i_max_steps;
    KeyFrameBoy[playIndexBoy].pantIzqInc = (KeyFrameBoy[playIndexBoy + 1].pantIzq - KeyFrameBoy[playIndexBoy].pantIzq) / i_max_steps;
    KeyFrameBoy[playIndexBoy].piernaDerInc = (KeyFrameBoy[playIndexBoy + 1].piernaDer - KeyFrameBoy[playIndexBoy].piernaDer) / i_max_steps;
    KeyFrameBoy[playIndexBoy].piernaIzqInc = (KeyFrameBoy[playIndexBoy + 1].piernaIzq - KeyFrameBoy[playIndexBoy].piernaIzq) / i_max_steps;
    KeyFrameBoy[playIndexBoy].brazoDerInc = (KeyFrameBoy[playIndexBoy + 1].brazoDer - KeyFrameBoy[playIndexBoy].brazoDer) / i_max_steps;
    KeyFrameBoy[playIndexBoy].brazoIzqInc = (KeyFrameBoy[playIndexBoy + 1].brazoIzq - KeyFrameBoy[playIndexBoy].brazoIzq) / i_max_steps;
    KeyFrameBoy[playIndexBoy].bicepDerInc = (KeyFrameBoy[playIndexBoy + 1].bicepDer - KeyFrameBoy[playIndexBoy].bicepDer) / i_max_steps;
    KeyFrameBoy[playIndexBoy].bicepIzqInc = (KeyFrameBoy[playIndexBoy + 1].bicepIzq - KeyFrameBoy[playIndexBoy].bicepIzq) / i_max_steps;

}



// Función para imprimir el contenido del archivo animBoy.txt en consola
void PrintAnimationBoy(const char* filename = "animBoy.txt") {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para imprimir." << std::endl;
        return;
    }

    std::string line;
    std::cout << "Contenido del archivo " << filename << ":\n";
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}
//////////////////////////////////// FIN FRAMES ///////////////////////////////



// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f,2.0f, 0.0f),
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f,  0.0f),
    glm::vec3(0.0f,0.0f, 0.0f)
};


glm::vec3 Light1 = glm::vec3(0);

///////////////// Variables para la animación de la pelota//////////////////
glm::vec3 pelotaPos = glm::vec3(0.0f, 1.0f, 0.0f); // Posición inicial
float tiempoAnimacion = 0.0f; // Tiempo para la animación
bool animacionActiva = false; // Control de la animación

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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Grafica - Hotel OASIS DEL SOL", nullptr, nullptr);

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
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");

    //////////////////ANIMACIÓN ALBERCA////////////////

    //Sheaders de control de animación para el agua y el flotador 
    Shader AlbShader("Shader/shaderAgua.vs", "Shader/shaderAgua.frag");
    Shader FlotShader("Shader/ShaderFlotador.vs", "Shader/ShaderFlotador.frag");

    ///////////////////////////////////////////////////

    ////////////////// Shader para el skybox ///////////////////////////
    Shader skyboxShader("Shader/SkyBox.vs", "Shader/SkyBox.frag");

    // Load models
    Model areaAlberca((char*)"Models/AreaAlberca.obj");
    Model agua((char*)"Models/agua.obj");
    Model flotador((char*)"Models/flotador.obj");

    //Edificio
    Model edificio((char*)"Models/EdificioPrincipal.obj");
    Model cristales((char*)"Models/Cristales.obj");
    Model suelo((char*)"Models/Plano.obj");

    //SpaArea
    Model spa((char*)"Models/areaSpa/CompleteSpa.obj");
    Model cristalSpa((char*)"Models/spaCristales.obj");



    //Juegos
    Model areaJuegos((char*)"Models/areaJuegos.obj");
    Model columpio((char*)"Models/Columpios.obj");

    //GYM
    Model GYM((char*)"Models/gym.obj");
    Model cristalesGYM((char*)"Models/CristalesGYM.obj");
    Model GYMElements((char*)"Models/gymElementos.obj");
    Model pelota((char*)"Models/areaGYM/ball.obj");

    //Adicionales - Plantas
    Model plantas((char*)"Models/plantas.obj");

    ////------------------ Modelos ave 
    Model colaPaj((char*)"Models/pajaro/cola.obj");
    Model cuerpoPaj((char*)"Models/pajaro/cuerpo.obj");
    Model alaDerPaj((char*)"Models/pajaro/alaDer.obj");
    Model alaIzqPaj((char*)"Models/pajaro/alaIzq.obj");


    //------------------- MODELOS BOY
    Model bicepD((char*)"Models/boy/bicepDER.obj");
    Model bicepI((char*)"Models/boy/bicepIZQ.obj");
    Model brazoD((char*)"Models/boy/brazoDER.obj");
    Model brazoI((char*)"Models/boy/brazoIZQ.obj");
    Model piernaD((char*)"Models/boy/piernaDER.obj");
    Model piernaI((char*)"Models/boy/piernaIZQ.obj");
    Model pantD((char*)"Models/boy/pantDER.obj");
    Model pantI((char*)"Models/boy/pantIZQ.obj");
    Model body((char*)"Models/boy/cuerpo.obj");
    Model skate((char*)"Models/boy/ball.obj");



    ////////////////////////// KEYFRAMES //////////////////////////////////

    /*Iniciarlizar todos los frames en 0 */
    //KeyFrames
    for (int i = 0; i < MAX_FRAMES; i++)
    {

        //--------AVE-----------
        KeyFrame[i].avePosX = 0;
        KeyFrame[i].avePosY = 0;
        KeyFrame[i].avePosZ = 0;
        KeyFrame[i].incX = 0;
        KeyFrame[i].incY = 0;
        KeyFrame[i].incZ = 0;
        KeyFrame[i].rotPaj = 0;
        KeyFrame[i].rotPajInc = 0;

        KeyFrame[i].rotPajX = 0;
        KeyFrame[i].rotPajXInc = 0;

        // Cuerpo
        KeyFrame[i].cuerpo = 0;
        KeyFrame[i].cuerpoInc = 0;

        // Cola
        KeyFrame[i].cola = 0;
        KeyFrame[i].colaInc = 0;

        //Ala derecha
        KeyFrame[i].alaDer = 0;
        KeyFrame[i].alaDerInc = 0;

        //Ala izquierda
        KeyFrame[i].alaIzq = 0;
        KeyFrame[i].alaIzqInc = 0;

    }

    for (int i = 0; i < MAX_FRAMES_BOY; i++)
    {
        //----------BOY------------

        KeyFrameBoy[i].boyPosX = 0;
        KeyFrameBoy[i].boyPosY = 0;
        KeyFrameBoy[i].boyPosZ = 0;

        KeyFrameBoy[i].sktPosX = 0;
        KeyFrameBoy[i].sktPosY = 0;
        KeyFrameBoy[i].sktPosZ = 0;

        KeyFrameBoy[i].rotBoy = 0;
        KeyFrameBoy[i].rotBoyInc = 0;
        KeyFrameBoy[i].rotBoyX = 0;
        KeyFrameBoy[i].rotBoyXInc = 0;

        KeyFrameBoy[i].cuerpoBoy = 0;
        KeyFrameBoy[i].cuerpoBoyInc = 0;
        KeyFrameBoy[i].bicepDer = 0;
        KeyFrameBoy[i].bicepDerInc = 0;
        KeyFrameBoy[i].bicepIzq = 0;
        KeyFrameBoy[i].bicepIzqInc = 0;
        KeyFrameBoy[i].brazoDer = 0;
        KeyFrameBoy[i].brazoDerInc = 0;
        KeyFrameBoy[i].brazoIzq = 0;
        KeyFrameBoy[i].brazoIzqInc = 0;
        KeyFrameBoy[i].piernaDer = 0;
        KeyFrameBoy[i].piernaDerInc = 0;
        KeyFrameBoy[i].piernaIzq = 0;
        KeyFrameBoy[i].piernaIzqInc = 0;
        KeyFrameBoy[i].pantDer = 0;
        KeyFrameBoy[i].pantDerInc = 0;
        KeyFrameBoy[i].pantIzq = 0;
        KeyFrameBoy[i].pantIzqInc = 0;

    }


    /////////////////////////////////////////////////////////////////////


    /////////////////////////// Vertices para el skybox ////////////////////////////

    GLfloat skyboxVertices[] = {
        // Positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    GLuint indices[] =
    {  // Note that we start from 0!
        0,1,2,3,
        4,5,6,7,
        8,9,10,11,
        12,13,14,15,
        16,17,18,19,
        20,21,22,23,
        24,25,26,27,
        28,29,30,31,
        32,33,34,35
    };

    ///////////////////////////////////////////////////////////////////////////////

    
    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /////////////// BUFFER PARA SKYBOX ////////////
    glGenBuffers(1, &EBO);
    ///////////////////////////////////////////////

    ///// SKYBOX /////
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //////////////////////////////////////////////////////////////////////////////////////////


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

    ////////////// SKYBOX ////////////
    GLuint skyBoxVBO, skyBoxVAO;
    glGenVertexArrays(1, &skyBoxVAO);
    glGenBuffers(1, &skyBoxVBO);
    glBindVertexArray(skyBoxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    /////////////////////////// CARGA TEXTURAS SKYBOX //////////////////////////////////
    vector < const GLchar*> faces;
    faces.push_back("SkyBox/izq.jpg");
    faces.push_back("SkyBox/der.jpg");
    faces.push_back("SkyBox/arriba.jpg");
    faces.push_back("SkyBox/debajo.jpg");
    faces.push_back("SkyBox/atras.jpg");
    faces.push_back("SkyBox/frente.jpg");

    GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);




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

        ////////////// Actualiza el modelo de ave ////////////
        Animation();

        ///////////////////// Actualizar la posición de la pelota
        BallAnimation();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OpenGL options
        glEnable(GL_DEPTH_TEST);

        glm::mat4 modelTemp = glm::mat4(1.0f); // Matriz Temporal 
        glm::mat4 modelTemp2 = glm::mat4(1.0f); // Matriz Temporal 
        glm::mat4 modelTemp3 = glm::mat4(1.0f); // Matriz Temporal 

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
         ///////// ----------------------- AVE ---------------------*

        glm::mat4 modelAve(1);

        modelAve = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAve));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);

        //Body
        modelTemp = modelAve = glm::translate(modelAve, glm::vec3(avePosX, avePosY, avePosZ));
        modelTemp = modelAve = glm::rotate(modelAve, glm::radians(rotPaj), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp = modelAve = glm::rotate(modelAve, glm::radians(rotPajX), glm::vec3(1.0f, 0.0f, 0.0f)); //mueve el cuerpo arriba abajo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAve));
        cuerpoPaj.Draw(lightingShader);

        //cola
        modelAve = modelTemp;
        modelAve = glm::translate(modelAve, glm::vec3(-3.927f + 3.411f, 1.343f - 1.346f, 10.143f - 10.143f)); // se aplican los valores del sistema de referencia que se tiene desde 3DMax 
        modelAve = glm::rotate(modelAve, glm::radians(cola), glm::vec3(0.0f, 0.0f, 1.0f)); // en la rotación se le pasa la variable que va a ayudar a rotar esa sección del cuerpo y en que eje se realiza la rotación
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAve));
        colaPaj.Draw(lightingShader);

        //Ala derecho 
        modelAve = modelTemp;
        modelAve = glm::translate(modelAve, glm::vec3(-3.433f + 3.411f, 1.32f - 1.346f, 9.851f - 9.551f)); // se aplican los valores del sistema de referencia que se tiene desde 3DMax 
        modelAve = glm::rotate(modelAve, glm::radians(alaDer), glm::vec3(-1.0f, 0.0f, 0.0f)); // en la rotación se le pasa la variable que va a ayudar a rotar esa sección del cuerpo y en que eje se realiza la rotación 
        modelAve = glm::rotate(modelAve, glm::radians(alaDer), glm::vec3(0.0f, 0.0f, 1.0f)); //mueve el ala de arriba abajo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAve));
        alaDerPaj.Draw(lightingShader);

        // Ala izquierda
        modelAve = modelTemp;
        modelAve = glm::translate(modelAve, glm::vec3(-3.433f + 3.411f, 1.32f - 1.346f, -9.851f + 9.551f)); // se aplican los valores del sistema de referencia que se tiene desde 3DMax 
        modelAve = glm::rotate(modelAve, glm::radians(alaIzq), glm::vec3(-1.0f, 0.0f, 0.0f)); // en la rotación se le pasa la variable que va a ayudar a rotar esa sección del cuerpo y en que eje se realiza la rotación
        modelAve = glm::rotate(modelAve, glm::radians(alaIzq), glm::vec3(0.0f, 0.0f, 1.0f)); //mueve el ala de arriba abajo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelAve));
        alaIzqPaj.Draw(lightingShader);

        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        //--------------------------------ANIMACIÓN NIÑO 1---------------------------------

        glm::mat4 modelBoy(1);

        //Body
        modelTemp2 = modelBoy = glm::translate(modelBoy, glm::vec3(boyPosX, boyPosY, boyPosZ));
        modelTemp2 = modelBoy = glm::rotate(modelBoy, glm::radians(rotBoy), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = modelBoy = glm::rotate(modelBoy, glm::radians(rotBoyX), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBoy));
        body.Draw(lightingShader);

        //BRAZOS
        
        //Bíceps Izquierdo 
        glm::mat4 modelBicepIzq = modelTemp2;
        modelBicepIzq = glm::translate(modelBicepIzq, glm::vec3(-12.634f + 12.768f, 1.006f - 0.913f, -8.383f + 8.352f));
        modelBicepIzq = glm::rotate(modelBicepIzq, glm::radians(bicepIzq), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBicepIzq));
        bicepI.Draw(lightingShader); // Dibuja el bíceps izquierdo

        //Brazo Izquierdo
        glm::mat4 modelBrazoIzq = modelBicepIzq;
        modelBrazoIzq = glm::translate(modelBrazoIzq, glm::vec3(-12.591f + 12.634, 0.844f - 1.006f, -8.389f + 8.383f));
        modelBrazoIzq = glm::rotate(modelBrazoIzq, glm::radians(brazoIzq), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBrazoIzq));
        brazoI.Draw(lightingShader); // Dibuja el brazo izquierdo

        // Bíceps Derecho
        glm::mat4 modelBicepDer = modelTemp2;
        modelBicepDer = glm::translate(modelBicepDer, glm::vec3(-12.88f + 12.768f, 1.006f - 0.913f, -8.383f + 8.352f));
        modelBicepDer = glm::rotate(modelBicepDer, glm::radians(bicepDer), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBicepDer));
        bicepD.Draw(lightingShader); // Dibuja el bíceps derecho

        // Brazo Derecho
        glm::mat4 modelBrazoDer = modelBicepDer;
        modelBrazoDer = glm::translate(modelBrazoDer, glm::vec3(-12.946f + 12.88, 0.859f - 1.006f, -8.408f + 8.383f));
        modelBrazoDer = glm::rotate(modelBrazoDer, glm::radians(brazoDer), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBrazoDer));
        brazoD.Draw(lightingShader); // Dibuja el brazo derecho

        //PIERNAS

        // Pierna Izquierda
        glm::mat4 modelPiernaIzq = modelTemp2;
        modelPiernaIzq = glm::translate(modelPiernaIzq, glm::vec3(-12.691f + 12.768f, 0.595f - 0.913f, -8.352f + 8.352f));
        modelPiernaIzq = glm::rotate(modelPiernaIzq, glm::radians(piernaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPiernaIzq));
        piernaI.Draw(lightingShader); // Dibuja la pierna izquierda

        //Pantorrilla Izquierda
        glm::mat4 modelPantIzq = modelPiernaIzq; // Aplica la transformación del cuerpo
        modelPantIzq = glm::translate(modelPantIzq, glm::vec3(-12.663f + 12.691f, 0.274f - 0.595f, -8.413f + 8.352f));
        modelPantIzq = glm::rotate(modelPantIzq, glm::radians(pantIzq), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPantIzq));
        pantI.Draw(lightingShader); // Dibuja la pantorrilla izquierda

        // Pierna Derecha
        glm::mat4 modelPiernaDer = modelTemp2;
        modelPiernaDer = glm::translate(modelPiernaDer, glm::vec3(-12.827f + 12.768f, 0.592f - 0.913f, -8.348f + 8.352f));
        modelPiernaDer = glm::rotate(modelPiernaDer, glm::radians(piernaDer), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPiernaDer));
        piernaD.Draw(lightingShader); // Dibuja la pierna derecha

        // Pantorrilla Derecha
        glm::mat4 modelPantDer = modelPiernaDer;
        modelPantDer = glm::translate(modelPantDer, glm::vec3(-12.872f + 12.827f, 0.27f - 0.592f, -8.405f + 8.348f));
        modelPantDer = glm::rotate(modelPantDer, glm::radians(pantDer), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPantDer));
        pantD.Draw(lightingShader); // Dibuja la pantorrilla derecha


        //Patineta 
        glm::mat4 modelPatineta = modelTemp3; 
        modelTemp3 = modelPatineta = glm::translate(modelPatineta, glm::vec3(sktPosX + 12.768f, sktPosY, sktPosZ + 8.352f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPatineta));
        skate.Draw(lightingShader);


        //----------------------------------------------------------------------------------
        
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

        glm::mat4 modelColumpio(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelColumpio));
        columpio.Draw(lightingShader);

        ////////////////////////GYM/////////////////////////////////
        glm::mat4 modelGYM(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelGYM));
        GYM.Draw(lightingShader);

        glm::mat4 modelGYME(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelGYME));
        GYMElements.Draw(lightingShader);

        ////////////////////Modelo pelota////////////////
        glm::mat4 modelPelota(1);
        modelPelota = glm::translate(model, pelotaPos);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPelota));
        pelota.Draw(lightingShader);

        glm::mat4 modelCrisGYM(1);
        glEnable(GL_BLEND); //Activa la funcionalidad para trabajar en el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1); //Se pone 1 para poder visualizar la transparencia 
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCrisGYM));
        cristalesGYM.Draw(lightingShader);
        glDisable(GL_BLEND);

        ////////////////////////////////////////////////////////////
        


        ////////////////////////ÁREA SPA/////////////////////////

        glm::mat4 modelSpa(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSpa));
        spa.Draw(lightingShader);

        glm::mat4 modelCristalesSPA(1);
        glEnable(GL_BLEND); //Activa la funcionalidad para trabajar en el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1); //Se pone 1 para poder visualizar la transparencia 
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCristalesSPA));
        cristalSpa.Draw(lightingShader);
        glDisable(GL_BLEND);

  
        ////////////////////////////////////////////////////////////
        

        //Plantas
        glm::mat4 modelPlantas(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPlantas));
        plantas.Draw(lightingShader);

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


        //////////// SKYBOX ///////////////
        glDepthFunc(GL_LEQUAL); //hace que no interfiera con otros objetos //Función de profundidad
        skyboxShader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(skyBoxVAO);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

      
        // Swap the buffers
        glDeleteVertexArrays(1, &VAO);
        glfwSwapBuffers( window ); 




    }
    
    /////////////////Borramos buffers 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &skyBoxVAO);
    glDeleteBuffers(1, &skyBoxVAO);


    glfwTerminate( );
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

    ///////////////////////////////////////////////////// TECLAS PARA EL AVE ////////////////////////////////

    //---------------------------------------- CUERPO -------------*

    /*//Movimiento en X (arriba abajo )
    if (keys[GLFW_KEY_Z])
    {
        rotPajX += 0.2f;
    }

    if (keys[GLFW_KEY_X])
    {
        rotPajX -= 0.2f;
    }

    //Movimiento en Y (a los lados)
    if (keys[GLFW_KEY_C])
    {
        rotPaj += 1.0f;
    }

    if (keys[GLFW_KEY_V]) //Para rotar en sentido contrario 
    {
        rotPaj -= 1.0f;
    }

    //Movimiento enfrente y atras
    if (keys[GLFW_KEY_B])
    {
        avePosX -= 0.01;
    }

    if (keys[GLFW_KEY_N])
    {
        avePosX += 0.01;
    }

    //Movimiento arriba y abajo 
    if (keys[GLFW_KEY_M])
    {
        avePosY += 0.01;
    }

    if (keys[GLFW_KEY_P])
    {
        avePosY -= 0.01;
    }


    //----------------------------- ALAS -----------------*

    //Ala derecha 

    if (keys[GLFW_KEY_4])
    {
        alaDer += 0.2f;
    }

    if (keys[GLFW_KEY_5])
    {
        alaDer -= 0.2f;
    }
    // Ala izquierda
    if (keys[GLFW_KEY_6]) {
        alaIzq += 1.0f;
    }
    if (keys[GLFW_KEY_7]) {
        alaIzq -= 1.0f;
    }


    //------------------------- COLA ----------------------*
    if (keys[GLFW_KEY_8])
    {
        cola += 0.2f;
    }

    if (keys[GLFW_KEY_9])
    {
        cola -= 0.2f;
    }
    */

    /////////////////////////////////////////////////////////////////////////////////////

    //---------------------------BOY----------------------

    //CUERPO
    if (keys[GLFW_KEY_Z])   boyPosZ += 0.01f; //enfrente
    if (keys[GLFW_KEY_X])   boyPosZ -= 0.01f; //atras

    if (keys[GLFW_KEY_C])   boyPosX += 0.001f; //enfrente
    if (keys[GLFW_KEY_V])   boyPosX -= 0.001f; //atras

    //BRAZOS
    if (keys[GLFW_KEY_B])   brazoIzq += 0.1f; //atras
    if (keys[GLFW_KEY_N])   brazoIzq -= 0.1f; //adelante

    if (keys[GLFW_KEY_M])   brazoDer += 0.1f; //atras
    if (keys[GLFW_KEY_J])   brazoDer -= 0.1f; //adelante

    //BICEP
    if (keys[GLFW_KEY_F])   bicepIzq += 0.1f; //atras
    if (keys[GLFW_KEY_4])   bicepIzq -= 0.1f; //adelante

    if (keys[GLFW_KEY_E])   bicepDer += 0.1f; //atras
    if (keys[GLFW_KEY_6])   bicepDer -= 0.1f; //delante

    //PIERNAS
    if (keys[GLFW_KEY_T])   piernaDer += 0.1f; //atras
    if (keys[GLFW_KEY_Y])   piernaDer -= 0.1f; //adelante

    if (keys[GLFW_KEY_U])   piernaIzq += 0.1f; //atras
    if (keys[GLFW_KEY_I])   piernaIzq -= 0.1f; //adelante

    //PANTORRILLA
    if (keys[GLFW_KEY_O])   pantDer += 0.1f; //atras
    if (keys[GLFW_KEY_P])   pantDer -= 0.1f; //adelante

    if (keys[GLFW_KEY_0])   pantIzq += 0.1f; //atras
    if (keys[GLFW_KEY_9])   pantIzq -= 0.1f; //adelante

    //PANTINETA
    if (keys[GLFW_KEY_8])   sktPosZ += 0.1f; //enfrentE
    if (keys[GLFW_KEY_7])   sktPosX -= 0.1f; //de lado a lado
}

void BallAnimation()
{
    if (animacionActiva)
    {
        tiempoAnimacion += deltaTime; // Incrementar el tiempo de animación
        float altura = abs(cos(tiempoAnimacion) * exp(-0.1f * tiempoAnimacion)); // Función cosenoidal para la altura
        pelotaPos.y = altura * 1.0f; // Ajustar la altura de la pelota

        // Movimiento en el eje X con decaimiento exponencial
        float desplazamientoX = sin(tiempoAnimacion) * exp(-0.1f * tiempoAnimacion) * 0.5f; // Función seno con decaimiento
        pelotaPos.x = desplazamientoX; // Ajustar la posición en X de la pelota
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    ///////////////////////////////////////////// KEYFRAMES ////////////////////////////
    if (keys[GLFW_KEY_L])
    {		//si la variable no se está reproduciendo 
        if (play == false && (FrameIndex > 1))
        {

            resetElements();
            //First Interpolation				
            interpolation();
            //aqui ya se esta reproduciendo la animación 
            play = true;
            playIndex = 0;
            i_curr_steps = 0;
        }
        else
        {
            play = false;
        }
    }

    if (keys[GLFW_KEY_L])
    {
        if (playBoy == false && (FrameIndexBoy > 1))
        {

            resetElementsBoy();
            //First Interpolation				
            interpolationBoy();
            //aqui ya se esta reproduciendo la animación 
            playBoy = true;
            playIndexBoy = 0;
            i_curr_steps_boy = 0;
        }
        else
        {
            playBoy = false;
        }
    }

    if (keys[GLFW_KEY_K])
    {
        if (FrameIndex < MAX_FRAMES)
        {
            saveFrame(); //guarda el estado actual de los keyframes 
        }

        if (FrameIndexBoy < MAX_FRAMES_BOY)
        {
            saveFrameBoy(); //guarda el estado actual de los keyframes 
        }
    }

//--------------------------ANIMACIONES POR KEYFRAMES--------------------------------------
    //IF para guardar los keyFrames en el archivo
    if (key == GLFW_KEY_G) {
        saveAnimation(); // Guarda la animación en "AnimKey.txt"
    }

    if (key == GLFW_KEY_1 && GLFW_PRESS == action) {

        resetElements();  // Resetear los elementos a los primeros keyframes cargados
        obtenerAnimation(); //Carga la animación por medio del archivo previamente guardado
    }

    //ANIMACION 2 - BOY 
    if (key == GLFW_KEY_Q) {
        saveAnimation2(); // Guarda la animación en "AnimBoy.txt"
    }

    if (key == GLFW_KEY_3 && GLFW_PRESS == action) {

        //resetElementsBoy();  // Resetear los elementos a los primeros keyframes cargados
        obtenerAnimation2(); //Carga la animación del niño por medio del archivo previamente guardado
        PrintAnimationBoy(); //Imprime en terminar los valores del archivo


    }

    //////////////////////////////////////////////////////////////////////////////////////////////


    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_R)
    {
        animacionActiva = true;
        tiempoAnimacion = 0.0f; 
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

void Animation() {

        /////////////////////////////////////////////////// KEYFRAMES ///////////////////////////////////////////////////////////
    if (play)
    {
        if (i_curr_steps >= i_max_steps) //end of animation between frames?
        {
            playIndex++;
            if (playIndex > FrameIndex - 2)	//end of total animation?
            {
                printf("termina anim\n");
                playIndex = 0;
                play = false;
            }
            else //Next frame interpolations
            {
                i_curr_steps = 0; //Reset counter
                //Interpolation
                interpolation();
            }
        }
        else
        {
            //-----------------AVE----------------------
            //Draw animation
            avePosX += KeyFrame[playIndex].incX;
            avePosY += KeyFrame[playIndex].incY;
            avePosZ += KeyFrame[playIndex].incZ;

            rotPaj += KeyFrame[playIndex].rotPajInc;
            rotPajX += KeyFrame[playIndex].rotPajXInc;

            //para observar la animación del cuerpo
            cuerpo += KeyFrame[playIndex].cuerpoInc;

            //Cola
            cola += KeyFrame[playIndex].colaInc;


            //para observar la animación de las patas
            alaDer += KeyFrame[playIndex].alaDerInc;
            alaIzq += KeyFrame[playIndex].alaIzqInc;

            i_curr_steps++;

        }
    }

    if (playBoy) {
        if (i_curr_steps_boy >= i_max_steps) //end of animation between frames?
        {
            playIndexBoy++;
            if (playIndexBoy > FrameIndexBoy - 2)	//end of total animation?
            {
                printf("termina anim\n");
                playIndexBoy = 0;
                playBoy = false;
            }
            else //Next frame interpolations
            {
                i_curr_steps_boy = 0; //Reset counter
                //Interpolation
                interpolationBoy();
            }
        }
        else
        {
            //-----------------BOY----------------------

            boyPosX += KeyFrameBoy[playIndexBoy].incX;
            boyPosY += KeyFrameBoy[playIndexBoy].incY;
            boyPosZ += KeyFrameBoy[playIndexBoy].incZ;

            sktPosX += KeyFrameBoy[playIndexBoy].incX;
            sktPosY += KeyFrameBoy[playIndexBoy].incY;
            sktPosZ += KeyFrameBoy[playIndexBoy].incZ;

            rotBoy += KeyFrameBoy[playIndexBoy].rotBoyInc;
            rotBoyX += KeyFrameBoy[playIndexBoy].rotBoyXInc;

            cuerpoBoy += KeyFrameBoy[playIndexBoy].cuerpoBoyInc;
            pantIzq += KeyFrameBoy[playIndexBoy].pantIzqInc;
            pantDer += KeyFrameBoy[playIndexBoy].pantDerInc;
            piernaIzq += KeyFrameBoy[playIndexBoy].piernaIzqInc;
            piernaDer += KeyFrameBoy[playIndexBoy].piernaDerInc;
            brazoIzq += KeyFrameBoy[playIndexBoy].brazoDerInc;
            brazoDer += KeyFrameBoy[playIndexBoy].brazoIzqInc;
            bicepIzq += KeyFrameBoy[playIndexBoy].bicepIzqInc;
            bicepDer += KeyFrameBoy[playIndexBoy].bicepDerInc;

            i_curr_steps_boy++;

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

