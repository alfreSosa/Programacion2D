#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//ESCONDE LA CONSOLA
#include <math.h>
#define RENDER Renderer::Instance()
#define SCREEN Screen::Instance()
#define RESOURCE ResourceManager::Instance()
//Macro para ejercicio4A
#define VEL(data) reinterpret_cast<Velocidades *>(data)
#include "include/u-gine.h"
//Declaración de funciones para ejecutar ejercicio
void practica1();
void practica2();
void practica2B();
void practica3();
void practica3B();
void practica4();
void practica4B();
void practica5();
void practica5B();
//Estructura para ejercicio4A
struct Velocidades
{
  double x;
  double y;
};

int main(int argc, char* argv[]) {
  //Entregar con practica4
  //practica5();
 // practica5B();
  //practica4();
  //practica4B();
  return 0;
}
void practica5B()
{
  SCREEN.Open(800, 600, false);

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);

    SCREEN.Refresh();

  }
  RESOURCE.FreeResources();

}
void practica5()
{
  SCREEN.Open(800, 600, false);
  int anchoMaximo;
  int altoMaximo;
  const double rotateVel = 50.0;
  const double moveVelX = 100.0;
  const double moveVelY = 100.0;
  //CARGAR IMAGEN
  Sprite **buffer;
  buffer = new Sprite*[5];
  Array<Sprite *> sprites(5);
  Image *alien = RESOURCE.LoadImage("data/alienanim.png", 8, 1);
  if (alien)
  {
    anchoMaximo = static_cast<int>(SCREEN.GetWidth() - alien->GetWidth() / 2.0);
    altoMaximo = static_cast<int>(SCREEN.GetHeight() - alien->GetHeight() / 2.0);

    for (unsigned int i = 0; i < 5; i++)
    {
      buffer[i] = new Sprite(alien);
      sprites.Add(buffer[i]);
      sprites[i]->SetScaleX(5);
      sprites[i]->SetScaleY(5);
      sprites[i]->SetFPS(-16);
      sprites[i]->SetFrameRange(0, 7);
      double posX = rand() % (anchoMaximo)+alien->GetWidth();
      double posY = rand() % (altoMaximo)+alien->GetHeight();
      sprites[i]->SetPosition(posX, posY);
      if (i == 0) sprites[i]->SetColor(255, 0, 0);
      if (i == 1) sprites[i]->SetColor(0, 255, 0);
      if (i == 2) sprites[i]->SetColor(0, 0, 255);
      if (i == 3) sprites[i]->SetColor(255, 0, 128);
      if (i == 4) sprites[i]->SetColor(255, 255, 255);
    }

  }

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);

    for (unsigned int i = 0; i < 5; i++)
    {
      if (SCREEN.GetMouseX() > sprites[i]->GetX()) sprites[i]->RotateTo(-15, rotateVel);
      else if (SCREEN.GetMouseX() < sprites[i]->GetX()) sprites[i]->RotateTo(15, rotateVel);
      else sprites[i]->RotateTo(0, 15);

      sprites[i]->MoveTo(SCREEN.GetMouseX(), SCREEN.GetMouseY(), moveVelX * (i + 1), moveVelY * (i + 1));

      sprites[i]->Update(SCREEN.ElapsedTime(), NULL);
      sprites[i]->Render();
      //FUSIONAR ALIENS!!
    }
    SCREEN.Refresh();

  }
  RESOURCE.FreeResources();
  //Revisar
  for (unsigned int i = 0; i < 5; i++)
    delete buffer[i];
  delete[]buffer;

}
void practica4()
{
  SCREEN.Open(800, 600, false);

  Velocidades **vel = new Velocidades*[5];

  Sprite **buffer;
  buffer = new Sprite*[5];
  Array<Sprite *> sprites(5);
  Image *pelota = RESOURCE.LoadImage("data/ball.png");
  int anchoMaximo,altoMaximo;
  const int velMax = 400;
  const int velMin = 150;
  if (pelota)
  {
    pelota->SetMidHandle();
    anchoMaximo = static_cast<int>(SCREEN.GetWidth() - pelota->GetWidth() / 2.0);
    altoMaximo = static_cast<int>(SCREEN.GetHeight() - pelota->GetHeight() / 2.0);
    for(int i =0 ; i < 5; i++)
    {
      buffer[i] = new Sprite(pelota);
      sprites.Add(buffer[i]);
      double posX = rand() % (anchoMaximo);
      double posY = rand() % (altoMaximo);
      sprites[i]->SetPosition(posX,posY);
      sprites[i]->SetColor(255,255,255);
      vel[i] = new Velocidades;
      vel[i]->x = rand() % velMax + velMin;
      vel[i]->y = rand() % velMax + velMin;
      sprites[i]->SetUserData(vel[i]);
    }
    
  }
  double direccionX = 1.0;
  double direccionY = 1.0;
  void *data;
  double nPosX;
  double nPosY;
  double error = 0.0001;
  double resta = 0.0;
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    

    RENDER.Clear(0, 0, 0);
    for(unsigned int i = 0; i < sprites.Size(); i++)
    {

      data = sprites[i]->GetUserData();
      nPosX = sprites[i]->GetX() + VEL(data)->x * SCREEN.ElapsedTime();
      nPosY = sprites[i]->GetY() + VEL(data)->y * SCREEN.ElapsedTime();
      //X
      if(nPosX > (SCREEN.GetWidth() - sprites[i]->GetImage()->GetWidth() / 2.0))
      {
        VEL(data)->x = -1 * rand() % velMax + velMin;
        sprites[i]->SetUserData(data);
      }
      if(nPosX < (sprites[i]->GetImage()->GetWidth() / 2.0))
      {
        VEL(data)->x = rand() % velMax + velMin;
        sprites[i]->SetUserData(data);
      }
      //Y
      if(nPosY > (SCREEN.GetHeight() - sprites[i]->GetImage()->GetHeight() / 2.0))
      {
        VEL(data)->y = -1 * rand() % velMax + velMin;
        sprites[i]->SetUserData(data);
      }
      if(nPosY < (sprites[i]->GetImage()->GetHeight() / 2.0))
      {
        VEL(data)->y = rand() % velMax + velMin;
        sprites[i]->SetUserData(data);
      }
      sprites[i]->SetPosition(nPosX,nPosY);

      sprites[i]->Render();
    }
    SCREEN.Refresh();
      
  }
  RESOURCE.FreeResources();
 //Revisar
  for (unsigned int i = 0; i < 5; i++)
  {
    delete buffer[i];
    delete vel[i];
  }
  delete []vel;
  delete []buffer;
}

void practica4B()
{
  SCREEN.Open(800, 600, false);
  int anchoMaximo;
  int altoMaximo;
  const double rotateVel = 50.0;
  const double moveVelX = 100.0;
  const double moveVelY = 100.0;
  //CARGAR IMAGEN
  Sprite **buffer;
  buffer = new Sprite*[5];
  Array<Sprite *> sprites(5);
  Image *alien = RESOURCE.LoadImage("data/alien.png");
  if (alien)
  {
    anchoMaximo = static_cast<int>(SCREEN.GetWidth() - alien->GetWidth() / 2.0);
    altoMaximo = static_cast<int>(SCREEN.GetHeight() - alien->GetHeight() / 2.0);
    alien->SetMidHandle();

    for(unsigned int  i = 0; i < 5; i++)
    {
      buffer[i] = new Sprite(alien);
      sprites.Add(buffer[i]);
      double posX = rand() % (anchoMaximo) + alien->GetWidth();
      double posY = rand() % (altoMaximo) + alien->GetHeight();
      sprites[i]->SetPosition(posX,posY);
      if(i == 0) sprites[i]->SetColor(255,0,0);
      if(i == 1) sprites[i]->SetColor(0,255,0);
      if(i == 2) sprites[i]->SetColor(0,0,255);
      if(i == 3) sprites[i]->SetColor(255,0,128);
      if(i == 4) sprites[i]->SetColor(255,255,255);
    }

  }

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);

    for(unsigned int  i = 0; i < 5; i++)
    {
      if (SCREEN.GetMouseX() > sprites[i]->GetX()) sprites[i]->RotateTo(-15,rotateVel);
      else if (SCREEN.GetMouseX() < sprites[i]->GetX()) sprites[i]->RotateTo(15,rotateVel);
      else sprites[i]->RotateTo(0,15);

      sprites[i]->MoveTo(SCREEN.GetMouseX(),SCREEN.GetMouseY(),moveVelX,moveVelY);

      sprites[i]->Update(SCREEN.ElapsedTime(),NULL);
      sprites[i]->Render();
      //FUSIONAR ALIENS!!
    }
    SCREEN.Refresh();
      
  }
  RESOURCE.FreeResources();
  //Revisar
  for(unsigned int i = 0; i < 5; i++)
    delete buffer[i];
  delete []buffer;

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

      RENDER.DrawImage(pelota, SCREEN.GetMouseX(), SCREEN.GetMouseY(),0, tamX * escala , tamY * escala, angRotation);
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
      angRotation += SCREEN.ElapsedTime() * 30; //30 grados un segundo
      angRotation = WrapValue(angRotation, 360); // Modulo 360 para que no incremente continuamente.

      if (escala >= 5.0) incremento *= -1;
      else if (escala <= 0.5) incremento *= -1;

      escala += SCREEN.ElapsedTime() * incremento;

      RENDER.DrawImage(pelota, SCREEN.GetMouseX(), SCREEN.GetMouseY(), 0, tamX * escala, tamY * escala, angRotation);
      SCREEN.Refresh();
      RENDER.Clear(0, 0, 0);
    }
    RESOURCE.FreeResources();
  }

}
void practica3()
{
  SCREEN.Open(800, 600, false);

  double acnhoFranja = SCREEN.GetWidth()/ 3.0f;
  const double radio = 30.0;

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);
    RENDER.SetBlendMode(RENDER.SOLID);
    RENDER.SetColor(255, 255, 255, 0);
    RENDER.DrawRect(acnhoFranja, 0, acnhoFranja, SCREEN.GetHeight());

    RENDER.SetBlendMode(RENDER.SOLID);
    RENDER.SetColor(255, 0, 0, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 2, SCREEN.GetHeight() / 4, radio, radio);
    RENDER.SetColor(0, 255, 0, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 2 - radio / 2, SCREEN.GetHeight() / 4 + radio, radio, radio);
    RENDER.SetColor(0, 0, 255, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 2 + radio / 2, SCREEN.GetHeight() / 4 + radio, radio, radio);

    RENDER.SetBlendMode(RENDER.MULTIPLICATIVE);
    RENDER.SetColor(255, 0, 0, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 2, SCREEN.GetHeight() * 3 / 4, radio, radio);
    RENDER.SetColor(0, 255, 0, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 2 - radio / 2, SCREEN.GetHeight() * 3 / 4 + radio, radio, radio);
    RENDER.SetColor(0, 0, 255, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 2 + radio / 2, SCREEN.GetHeight() * 3 / 4 + radio, radio, radio);

    RENDER.SetBlendMode(RENDER.ALPHA);
    RENDER.SetColor(255, 0, 0, 128);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 6, SCREEN.GetHeight() / 2, radio, radio);
    RENDER.SetColor(0, 255, 0, 128);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 6 - radio / 2, SCREEN.GetHeight() / 2 + radio, radio, radio);
    RENDER.SetColor(0, 0, 255, 128);
    RENDER.DrawEllipse(SCREEN.GetWidth() / 6 + radio / 2, SCREEN.GetHeight() / 2 + radio, radio, radio);

    RENDER.SetBlendMode(RENDER.ADDITIVE);
    RENDER.SetColor(255, 0, 0, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() * 5 / 6, SCREEN.GetHeight() / 2, radio, radio);
    RENDER.SetColor(0, 255, 0, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() * 5 / 6 - radio / 2, SCREEN.GetHeight() / 2 + radio, radio, radio);
    RENDER.SetColor(0, 0, 255, 255);
    RENDER.DrawEllipse(SCREEN.GetWidth() * 5 / 6 + radio / 2, SCREEN.GetHeight() / 2 + radio, radio, radio);
    SCREEN.Refresh();
    RENDER.Clear(0, 0, 0);
  }

}
void practica3B()
{
  SCREEN.Open(800, 800, false);
  Image *caja = RESOURCE.LoadImage("data/box.jpg");
  Image *luz = RESOURCE.LoadImage("data/light.png");
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);
    RENDER.SetBlendMode(RENDER.SOLID);
    for (int x = 0; x < SCREEN.GetWidth(); x += SCREEN.GetWidth() / 8)
      for (int y = 0; y < SCREEN.GetHeight();y += SCREEN.GetHeight() / 8)
        RENDER.DrawImage(caja, x + caja->GetWidth() / 2, y + caja->GetHeight() / 2);

    double luzX = 0;
    double luzY = 0;
    glBlendFunc(GL_ZERO, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;

    glBlendFunc(GL_ONE, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;

    glBlendFunc(GL_SRC_COLOR, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY = 0;
    luzX += SCREEN.GetWidth() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ZERO);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);
    luzY += SCREEN.GetHeight() / 8;
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    RENDER.DrawImage(luz, luzX + luz->GetWidth() / 2, luzY + luz->GetHeight() / 2);

    SCREEN.Refresh();
    RENDER.Clear(0, 0, 0);
  }
  RESOURCE.FreeResources();

}
