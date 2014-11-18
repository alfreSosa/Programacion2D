#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//ESCONDE LA CONSOLA
#define RENDER Renderer::Instance()
#define SCREEN Screen::Instance()
#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	SCREEN.Open(800, 600, false);

  RENDER;

  const float rectCenterTam = 50.0f;
  const int rectMouseTam = 10;
  const int circleMouseRadius = 5;

  const float midRectCenterTam = rectCenterTam / 2;
  const int midRectMouseTam = rectMouseTam / 2;
  const int circleDistanciaAlMouse = 30;
  const int posicionFinal = 5;
  int x_mouse;
  int y_mouse;

  float x_mouseCircle;
  float y_mouseCircle;

  float x_midle = SCREEN.GetWidth() / 2.0f - midRectCenterTam;
  float y_midle = SCREEN.GetHeight() / 2.0f - midRectCenterTam;

  float posCircle = 0.0f;
  float senoCircle = 0.0f;
  float cosenoCircle = 1.0f;
  /*Preguntar como esconder el cursor*/

  while ( SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC)) 
  {
    //Obtener posisicion raton
    x_mouse = SCREEN.GetMouseX() - midRectMouseTam;
    y_mouse = SCREEN.GetMouseY() - midRectMouseTam;

    //Calcular posicion circulo
    posCircle += SCREEN.ElapsedTime() * posicionFinal; 
    senoCircle =  DegSin(-posCircle); // negativo para sentido antihorario.
    cosenoCircle =  DegCos(posCircle); 

    x_mouseCircle = x_mouse + cosenoCircle * circleDistanciaAlMouse;
    y_mouseCircle = y_mouse + senoCircle * circleDistanciaAlMouse;

    //Obtener angulo y distancia
    float angulo = Angle(x_mouseCircle, y_mouseCircle, x_mouse + midRectMouseTam, y_mouse + midRectMouseTam);
    float distance = Distance(x_mouse + midRectMouseTam, y_mouse + midRectMouseTam, x_midle + midRectCenterTam, y_midle + midRectCenterTam);

    //pintar titulo
    String tit1 = "Grados: ";
    tit1 += String::FromFloat(angulo);
    tit1 += " Distancia: ";
    tit1 += String::FromFloat(distance);
    SCREEN.SetTitle(tit1);

		// TAREA: Pintar primitivas
    //Pintar Cuadrado Central en Rojo
    RENDER.SetColor(255,0,0,0);
    RENDER.DrawRect(x_midle,y_midle,rectCenterTam,rectCenterTam);

    //fijar color verde y pintar cuadrado en raton.
    RENDER.SetColor(0,255,0,0);
    RENDER.DrawRect(x_mouse,y_mouse,rectMouseTam,rectMouseTam);

    //Fijar color azul, pintar elipse en...
    RENDER.SetColor(0,0,255,0);
    SCREEN.ElapsedTime();
    RENDER.DrawEllipse(x_mouseCircle, y_mouseCircle, circleMouseRadius , circleMouseRadius);
		// Refrescamos la pantalla
		SCREEN.Refresh();
    RENDER.Clear(0,0,0);
   
	}
	
	return 0;
}
