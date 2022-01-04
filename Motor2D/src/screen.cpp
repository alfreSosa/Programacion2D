#include "../include/screen.h"
#include "../include/glinclude.h"
#include <iostream>

Screen* Screen::m_screen = nullptr;

void Screen::CloseCallback(GLFWwindow* window) {
    Screen::Instance().m_opened = false;
}

Screen::Screen() {

    if (!glfwInit())
    {
        std::cout << "Could not initialize GLFW" << std::endl;
    }

    m_opened = false;
}

Screen::~Screen() {
    glfwTerminate();
}

Screen& Screen::Instance() {
    if (!m_screen)
        m_screen = new Screen();
    return *m_screen;
}

void Screen::Open(uint16 width, uint16 height, bool fullscreen) {

    // Abrimos la ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_mainWindow = glfwCreateWindow(width, height, "", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    glfwMakeContextCurrent(m_mainWindow);


    // MAC OS X
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //m_mainMonitor = glfwGetWindowMonitor(m_mainWindow);
    
    /*glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindow(int(width), int(height), 8, 8, 8, 8, 0, 0, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW );*/
    /*if ( !fullscreen )
        glfwSetWindowPos(mainWindow, (GetDesktopWidth()-width)/2, (GetDesktopHeight()-height)/2);*/
   // glfwSetWindowCloseCallback(m_mainWindow, GLFWwindowclosefun(CloseCallback));
    glfwSwapInterval(1);
    SetTitle("");
    m_opened = true;

    // Inicializamos OpenGL
    // TAREA: Inicializar estados
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    // Configuramos viewport
    // TAREA: Inicializar viewport
    // 
    glfwGetFramebufferSize(m_mainWindow, &m_width, &m_height);
    //this->m_width = width;
    //this->m_height = height;
    glViewport(0, 0, m_width, m_height);
    // Configuramos matriz de proyeccion
    // TAREA: Configurar matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, m_width, m_height, 0.0f, 0.0f, 1000.0f);
    // Configuramos matriz de modelado
    // TAREA: Configurar matriz de modelado
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicializamos temporizador
    m_lastTime = glfwGetTime();
    m_elapsed = 0;
}

void Screen::Close() {
    glfwDestroyWindow(m_mainWindow);
    m_mainWindow = nullptr;
}

void Screen::SetTitle(const String &title) {
    glfwSetWindowTitle(m_mainWindow, title.ToCString());
}

void Screen::Refresh() {
    glfwSwapBuffers(m_mainWindow);
    glfwPollEvents();
    glfwGetCursorPos(m_mainWindow, &m_mousex, &m_mousey);
    m_elapsed = glfwGetTime() - m_lastTime;
    m_lastTime = glfwGetTime();
}

uint16 Screen::GetDesktopWidth() const {
    int count = 0;
    const GLFWvidmode* mode = glfwGetVideoModes(m_mainMonitor, &count);
    return uint16(mode->width);
}

uint16 Screen::GetDesktopHeight() const {
    int count = 0;
    const GLFWvidmode* mode = glfwGetVideoModes(m_mainMonitor, &count);
    return uint16(mode->height);
}

bool Screen::MouseButtonPressed(int button) const {
    return glfwGetMouseButton(m_mainWindow, button) == GLFW_PRESS;
}

bool Screen::KeyPressed(int key) const {
    return glfwGetKey(m_mainWindow, key) == GLFW_PRESS;
}
