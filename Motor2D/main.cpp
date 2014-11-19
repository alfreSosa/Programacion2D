#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//ESCONDE LA CONSOLA
#define RENDER Renderer::Instance()
#define SCREEN Screen::Instance()
#define RESOURCE ResourceManager::Instance()

#include "include/u-gine.h"
//MOTOR2D es UGINE
void practica1();
void practica2();
void practica2B();

int main(int argc, char* argv[]) {
  //practica1();
  //practica2();
  practica2B();
  return 0;
}

void practica1()
{
  SCREEN.Open(800, 600, false);

  RENDER;

  const float rectCenterTam = 50.0f;
  const int rectMouseTam = 10;
  const int circleMouseRadius = 5;

  const float midRectCenterTam = rectCenterTam / 2;
  const int midRectMouseTam = rectMouseTam / 2;
  const int circleDistanciaAlMouse = 30;
  const int posicionFinal = 20;
  int x_mouse;
  int y_mouse;

  double x_mouseCircle;
  double y_mouseCircle;

  double x_midle = SCREEN.GetWidth() / 2.0f - midRectCenterTam;
  double y_midle = SCREEN.GetHeight() / 2.0f - midRectCenterTam;

  double posCircle = 0.0f;
  double senoCircle = 0.0f;
  double cosenoCircle = 1.0f;
  /*Preguntar como esconder el cursor*/

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
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

    // TAREA: Pintar primitivas
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
    // Refrescamos la pantalla
    SCREEN.Refresh();
    RENDER.Clear(0, 0, 0);
  }


}
void practica2()
{
  SCREEN.Open(800, 600, false);

  double angRotation = 0.0;
  double escala = 1.0;
  double incremento = 2.0;
  //CARGAR IMAGEN
  Image *pelota = RESOURCE.LoadImage("data/ball.png");
  if (pelota)
  {
    double tamX = pelota->GetWidth();
    double tamY = pelota->GetHeight();
    //CENTRAR IMAGEN
    pelota->SetMidHandle();
    while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
    {
      angRotation += SCREEN.ElapsedTime() * 30; //30 grados un segundo
      angRotation = WrapValue(angRotation, 360); // Modulo 360 para que no incremente continuamente.

      if (escala >= 5.0) incremento *= -1;
      else if (escala <= 0.5) incremento *= -1;

      escala += SCREEN.ElapsedTime() * incremento;

      RENDER.DrawImage(pelota, SCREEN.GetMouseX(), SCREEN.GetMouseY(),1, tamX * escala , tamY * escala, angRotation);
      SCREEN.Refresh();
      RENDER.Clear(0, 0, 0);
    }
    RESOURCE.FreeResources();
  }

}
void practica2B()
{
  SCREEN.Open(800, 600, false);

  double angRotation = 0.0;
  double escala = 1.0;
  double incremento = 2.0;
  //CARGAR IMAGEN
  Image *pelota = RESOURCE.LoadImage("data/soccer_npot.png");
  if (pelota)
  {
    double tamX = pelota->GetWidth();
    double tamY = pelota->GetHeight();
    //CENTRAR IMAGEN
    pelota->SetMidHandle();
    while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
    {
     // angRotation += SCREEN.ElapsedTime() * 30; //30 grados un segundo
     // angRotation = WrapValue(angRotation, 360); // Modulo 360 para que no incremente continuamente.

      if (escala >= 5.0) incremento *= -1;
      else if (escala <= 0.5) incremento *= -1;

      escala += SCREEN.ElapsedTime() * incremento;

      RENDER.DrawImage(pelota, SCREEN.GetMouseX(), SCREEN.GetMouseY(), 1, tamX * escala, tamY * escala, angRotation);
      SCREEN.Refresh();
      RENDER.Clear(255, 255, 255);
    }
    RESOURCE.FreeResources();
  }

}
