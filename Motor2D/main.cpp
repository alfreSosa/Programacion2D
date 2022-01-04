//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/examples.h"
#include <iostream>

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void TestGLFW3()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, Screen::Framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void TestGLFW3_V2()
{
    SCREEN.Open(800, 600, false);
   
    const float rectCenterTam = 50.0f;
    const int rectMouseTam = 10;
    const int circleMouseRadius = 5;

    const float midRectCenterTam = rectCenterTam / 2;
    const int midRectMouseTam = rectMouseTam / 2;
    const int circleDistanciaAlMouse = 30;
    const int posicionFinal = 20;
    double x_mouse;
    double y_mouse;

    double x_mouseCircle;
    double y_mouseCircle;

    double x_midle = SCREEN.GetWidth() / 2.0f - midRectCenterTam;
    double y_midle = SCREEN.GetHeight() / 2.0f - midRectCenterTam;

    double posCircle = 0.0f;
    double senoCircle = 0.0f;
    double cosenoCircle = 1.0f;

    while (SCREEN.IsOpened())
    {

       // processInput(window);
         //Obtener posisicion raton
        x_mouse = SCREEN.GetMouseX() - midRectMouseTam;
        y_mouse = SCREEN.GetMouseY() - midRectMouseTam;

        //Calcular posicion circulo
        posCircle += SCREEN.ElapsedTime() * posicionFinal;
        senoCircle = DegSin(posCircle); // negativo para sentido antihorario.
        cosenoCircle = DegCos(posCircle);

        x_mouseCircle = x_mouse + cosenoCircle * circleDistanciaAlMouse;
        y_mouseCircle = y_mouse + senoCircle * circleDistanciaAlMouse;

        //Obtener angulo y distancia
        float angulo = static_cast<float>(Angle(x_mouse + midRectMouseTam, y_mouse + midRectMouseTam, x_mouseCircle, y_mouseCircle));
        float distance = static_cast<float>(Distance(x_mouse + midRectMouseTam, y_mouse + midRectMouseTam, x_midle + midRectCenterTam, y_midle + midRectCenterTam));

        //pintar titulo
        String tit1 = "Grados: ";
        tit1 += String::FromFloat(angulo);
        tit1 += " Distancia: ";
        tit1 += String::FromFloat(distance);
        SCREEN.SetTitle(tit1);

        //Pintar Cuadrado Central en Rojo
        RENDER.SetColor(255, 0, 0, 0);
        RENDER.DrawRect(x_midle, y_midle, rectCenterTam, rectCenterTam);

        //fijar color verde y pintar cuadrado en raton.
        RENDER.SetColor(0, 255, 0, 0);
        RENDER.DrawRect(x_mouse, y_mouse, rectMouseTam, rectMouseTam);

        //Fijar color azul, pintar elipse en...
        RENDER.SetColor(0, 0, 255, 0);
        SCREEN.ElapsedTime();
        RENDER.DrawEllipse(x_mouseCircle, y_mouseCircle, circleMouseRadius, circleMouseRadius);

        RENDER.Clear(0.2f, 0.3f, 0.3f);

        SCREEN.Refresh();

    }
    glfwTerminate();
}

/*Si se van cerrando las ventanas pulsando a la "X", se cierra y se abre la siguiente practica.
Si no simplemente comentar la funcion a la práctica que no se desee ejecutar*/
int main(int argc, char* argv[]) {
    TestGLFW3_V2();
    return 0;
}