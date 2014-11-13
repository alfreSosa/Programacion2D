#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#define RENDER Renderer::Instance()
#define SCREEN Screen::Instance()
#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	SCREEN.Open(800, 600, false);

  RENDER;

  const float rectCenterTam = 50.0f;
  const int rectMouseTam = 10;

  int x_mouse;
  int y_mouse;

  float x_midle = SCREEN.GetWidth() / 2.0f - (rectCenterTam / 2);
  float y_midle = SCREEN.GetHeight() / 2.0f - (rectCenterTam / 2);
  
  while ( SCREEN.IsOpened() ) 
  {
		// TAREA: Pintar primitivas
    //Pintar Cuadrado Central en Rojo
    RENDER.SetColor(255,0,0,0);
    RENDER.DrawRect(x_midle,y_midle,rectCenterTam,rectCenterTam);

    //Obtener posicion raton, fijar color verde y pintar cuadrado en raton.
    x_mouse = SCREEN.GetMouseX() - (rectMouseTam / 2);
    y_mouse = SCREEN.GetMouseY() - (rectMouseTam / 2);
    RENDER.SetColor(0,255,0,0);
    RENDER.DrawRect(x_mouse,y_mouse,rectMouseTam,rectMouseTam);

    //Fijar color azul, pintar elipse en...
    RENDER.SetColor(0,0,255,0);
    RENDER.DrawEllipse(x_mouse - 10, y_mouse - 10, 5 ,5);
		// Refrescamos la pantalla
		SCREEN.Refresh();
    RENDER.Clear(0,0,0);
   
	}
	
	return 0;
}
