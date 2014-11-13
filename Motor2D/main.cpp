#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

  Renderer::Instance();

  const float rectCenterTam = 50.0f;
  const int rectMouseTam = 10;

  int x_mouse;
  int y_mouse;

  float x_midle = Screen::Instance().GetWidth() / 2.0f - (rectCenterTam / 2);
  float y_midle = Screen::Instance().GetHeight() / 2.0f - (rectCenterTam / 2);
  
  while ( Screen::Instance().IsOpened() ) 
  {
		// TAREA: Pintar primitivas
    
    Renderer::Instance().DrawRect(x_midle,y_midle,rectCenterTam,rectCenterTam);
    x_mouse = Screen::Instance().GetMouseX() - (rectMouseTam / 2);
    y_mouse = Screen::Instance().GetMouseY() - (rectMouseTam / 2);
    Renderer::Instance().DrawRect(x_mouse,y_mouse,rectMouseTam,rectMouseTam);
		// Refrescamos la pantalla
		Screen::Instance().Refresh();
	}
	
	return 0;
}
