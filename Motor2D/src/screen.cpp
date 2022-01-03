#include "../include/screen.h"
#include "../include/glinclude.h"

Screen* Screen::screen = NULL;

void Screen::CloseCallback(GLFWwindow* window) {
	Screen::Instance().opened = false;
}

Screen::Screen() {
	glfwInit();

	opened = false;
}

Screen::~Screen() {
	glfwTerminate();
}

Screen& Screen::Instance() {
	if ( !screen )
		screen = new Screen();
	return *screen;
}

void Screen::Open(uint16 width, uint16 height, bool fullscreen) {
	// Abrimos la ventana
    mainWindow = glfwCreateWindow(width, height, "", fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	/*glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(int(width), int(height), 8, 8, 8, 8, 0, 0, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW );*/
	/*if ( !fullscreen )
		glfwSetWindowPos(mainWindow, (GetDesktopWidth()-width)/2, (GetDesktopHeight()-height)/2);*/
	glfwSetWindowCloseCallback(mainWindow, GLFWwindowclosefun(CloseCallback));
	glfwSwapInterval(1);
	SetTitle("");
	opened = true;

	// Inicializamos OpenGL
	// TAREA: Inicializar estados
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
	// Configuramos viewport
	// TAREA: Inicializar viewport
	this->width = width;
	this->height = height;
  glViewport(0,0,this->width,this->height);
	// Configuramos matriz de proyeccion
	// TAREA: Configurar matriz de proyeccion
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, this->width, this->height, 0.0f, 0.0f, 1000.0f);
	// Configuramos matriz de modelado
	// TAREA: Configurar matriz de modelado
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	// Inicializamos temporizador
	lastTime = glfwGetTime();
	elapsed = 0;
}

void Screen::Close() {
	glfwDestroyWindow(mainWindow);
    mainWindow = nullptr;
}

void Screen::SetTitle(const String &title) {
    glfwSetWindowTitle(mainWindow, title.ToCString());
}

void Screen::Refresh() {
	glfwSwapBuffers(mainWindow);
	glfwGetCursorPos(mainWindow, &mousex, &mousey);
	elapsed = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
}

uint16 Screen::GetDesktopWidth() const {
    int count = 0;
    const GLFWvidmode* mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
	return uint16(mode->width);
}

uint16 Screen::GetDesktopHeight() const {
    int count = 0;
    const GLFWvidmode* mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
	return uint16(mode->height);
}

bool Screen::MouseButtonPressed(int button) const {
	return glfwGetMouseButton(mainWindow, button) == GLFW_PRESS;
}

bool Screen::KeyPressed(int key) const {
	return glfwGetKey(mainWindow, key) == GLFW_PRESS;
}
