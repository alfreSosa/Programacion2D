#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//ESCONDE LA CONSOLA
#include <math.h>
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
void practica6();
void practica6B();
void practica6C();
void practica7();
void practica7B();
void practica8();
void practica8B();
void practica9();
void practica9B();



//Estructura para ejercicio4A-6
struct Velocidades
{
  double x;
  double y;
};

int main(int argc, char* argv[]) {
  practica9B();
  //practica9();
  return 0;
}
void practica9B()
{
  SCREEN.Open(800, 600, false);
  Image *pel = RESOURCE.LoadImage("data/ball.png");
  pel->SetMidHandle();
  Image *caja = RESOURCE.LoadImage("data/box.jpg");
  caja->SetMidHandle();
  Image *circle = RESOURCE.LoadImage("data/circle.png");
  circle->SetMidHandle();
  Image *rect = RESOURCE.LoadImage("data/rect.png");
  rect->SetMidHandle();
  Image *alien = RESOURCE.LoadImage("data/alien.png");
  alien->SetMidHandle();

  Scene *escena = new Scene();

  Sprite *ball = escena->CreateSprite(pel);
  ball->SetPosition(SCREEN.GetWidth() / 4, SCREEN.GetHeight() / 4);
  ball->SetRadius(pel->GetHeight() / 2.0);
  ball->SetCollision(Sprite::COLLISION_CIRCLE);

  Sprite *box = escena->CreateSprite(caja);
  box->SetPosition(SCREEN.GetWidth() * 3 / 4, SCREEN.GetHeight() * 3 / 4);
  box->SetCollision(Sprite::COLLISION_RECT);

  Sprite *puntero = escena->CreateSprite(circle);
  puntero->SetRadius(circle->GetHeight() / 2.0);
  puntero->SetCollision(Sprite::COLLISION_CIRCLE);

  Sprite *heli = escena->CreateSprite(alien);
  heli->SetPosition(SCREEN.GetWidth() / 4, SCREEN.GetHeight() * 3 / 4);
  CollisionPixelData *col = new CollisionPixelData("data/aliencol.png");
  heli->SetCollisionPixelData(col);
  heli->SetCollision(Sprite::COLLISION_PIXEL);
  
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);
    puntero->SetPosition(SCREEN.GetMouseX(), SCREEN.GetMouseY());
    if (SCREEN.MouseButtonPressed(GLFW_MOUSE_BUTTON_1)){
      puntero->SetImage(circle);
      puntero->SetRadius(circle->GetHeight() / 2.0);
      puntero->SetCollision(Sprite::COLLISION_CIRCLE);
    }
    if (SCREEN.MouseButtonPressed(GLFW_MOUSE_BUTTON_2)){
      puntero->SetImage(rect);
      puntero->SetCollision(Sprite::COLLISION_RECT);
    }
   if (SCREEN.KeyPressed(GLFW_KEY_TAB)){
      puntero->SetImage(alien);
      puntero->SetCollisionPixelData(col);
      puntero->SetCollision(Sprite::COLLISION_PIXEL);
      
    }

    if (ball->DidCollide()) ball->SetColor(255, 0, 0);
    else ball->SetColor(255, 255, 255);

    if (box->DidCollide()) box->SetColor(255, 0, 0);
    else box->SetColor(255, 255, 255);

    if (puntero->DidCollide()) puntero->SetColor(0, 255, 0);
    else puntero->SetColor(255, 255, 255);

    escena->Update(SCREEN.ElapsedTime());
    escena->Render();
    SCREEN.Refresh();

  }
  delete col;
  delete escena;
  RESOURCE.FreeResources();
}
void practica9()
{
  SCREEN.Open(800, 600, false);
  Image *pel = RESOURCE.LoadImage("data/ball.png");
  pel->SetMidHandle();
  Image *caja = RESOURCE.LoadImage("data/box.jpg");
  caja->SetMidHandle();
  Image *circle = RESOURCE.LoadImage("data/circle.png");
  circle->SetMidHandle();
  Image *rect = RESOURCE.LoadImage("data/rect.png");
  rect->SetMidHandle();

  Scene *escena = new Scene();

  Sprite *ball = escena->CreateSprite(pel);
  ball->SetPosition(SCREEN.GetWidth() / 4, SCREEN.GetHeight() / 4);
  ball->SetRadius(pel->GetHeight() / 2.0);
  ball->SetCollision(Sprite::COLLISION_CIRCLE);

  Sprite *box = escena->CreateSprite(caja);
  box->SetPosition(SCREEN.GetWidth() * 3 / 4, SCREEN.GetHeight() * 3 / 4);
  box->SetCollision(Sprite::COLLISION_RECT);

  Sprite *puntero = escena->CreateSprite(circle);
  puntero->SetRadius(circle->GetHeight() / 2.0);
  puntero->SetCollision(Sprite::COLLISION_CIRCLE);
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);
    puntero->SetPosition(SCREEN.GetMouseX(), SCREEN.GetMouseY());
    if (SCREEN.MouseButtonPressed(GLFW_MOUSE_BUTTON_1)){
      puntero->SetImage(circle);
      puntero->SetRadius(circle->GetHeight() / 2.0);
      puntero->SetCollision(Sprite::COLLISION_CIRCLE);
    }
    if (SCREEN.MouseButtonPressed(GLFW_MOUSE_BUTTON_2)){
      puntero->SetImage(rect);
      puntero->SetCollision(Sprite::COLLISION_RECT);
    }
    

    if (ball->DidCollide()) ball->SetColor(255, 0, 0);
    else ball->SetColor(255, 255, 255);

    if (box->DidCollide()) box->SetColor(255, 0, 0);
    else box->SetColor(255, 255, 255);

    if (puntero->DidCollide()) puntero->SetColor(0, 255, 0);
    else puntero->SetColor(255, 255, 255);

    escena->Update(SCREEN.ElapsedTime());
    escena->Render();
    SCREEN.Refresh();

  }
  delete escena;
  RESOURCE.FreeResources();
}
void practica8B()
{
  SCREEN.Open(800, 600, false);
  Scene *escena1 = new Scene(NULL);
  escena1->GetCamera().SetPosition(0, 0);
  escena1->SetBackgroundColor(0, 0, 0);

  Affector af1(true, false, false, true);
  af1.setAncho(0,SCREEN.GetWidth() / 3.0);
  af1.setAlto(0,SCREEN.GetHeight());

  af1.SetMinColor(0, 0, 0);
  af1.SetMaxColor(255, 255, 0);
  af1.SetAngularVelocity(0, 360);

  Affector af2(true, false, false, true);
  af2.SetMinColor(0, 0, 0);
  af2.SetMaxColor(0, 255, 255);
  af2.SetAngularVelocity(360, 720);

  af2.setAncho(SCREEN.GetWidth() * 2 / 3.0 , SCREEN.GetWidth());
  af2.setAlto(0, SCREEN.GetHeight());

  Image *star = RESOURCE.LoadImage("data/star.png");
  Sprite *generador;
  Emitter *emisor;
  if (star)
  {

    star->SetMidHandle();
    generador = escena1->CreateSprite(star, Scene::LAYER_MIDDLE);
    generador->SetColor(255, 0, 0);
    emisor = escena1->CreateEmitter(star, true, Scene::LAYER_BACK);

    emisor->SetRate(0, 500);
    emisor->SetAngularVelocity(0, 360);
    emisor->SetVelocityX(-128, 128);
    emisor->SetVelocityY(-128, 128);
    emisor->SetLifetime(1, 2);
    emisor->SetMinColor(0, 0, 0);
    emisor->SetMaxColor(255, 255, 255);

    emisor->addAffector(af1);
    emisor->addAffector(af2);

  }

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    generador->SetPosition(SCREEN.GetMouseX(), SCREEN.GetMouseY());
    emisor->SetX(SCREEN.GetMouseX());
    emisor->SetY(SCREEN.GetMouseY());
    if (SCREEN.MouseButtonPressed(GLFW_MOUSE_BUTTON_2))
      emisor->Start();
    else
      emisor->Stop();
    escena1->Update(SCREEN.ElapsedTime());
    escena1->Render();
    SCREEN.Refresh();

  }
  delete escena1;
  RESOURCE.FreeResources();
}
void practica8()
{
  SCREEN.Open(800, 600, false);
  Scene *escena1 = new Scene(NULL);
  escena1->GetCamera().SetPosition(0, 0);
  escena1->SetBackgroundColor(0, 0, 0);
  
  Image *star = RESOURCE.LoadImage("data/star.png");
  Sprite *generador;
  Emitter *emisor;
  if (star)
  {

    star->SetMidHandle();
    generador = escena1->CreateSprite(star, Scene::LAYER_MIDDLE);
    generador->SetColor(255, 0, 0);
    emisor = escena1->CreateEmitter(star, true,Scene::LAYER_BACK);
    emisor->SetRate(500, 1000);
    emisor->SetAngularVelocity(0, 360);
    emisor->SetVelocityX(-128, 128);
    emisor->SetVelocityY(-128, 128);
    emisor->SetLifetime(1, 2);
    emisor->SetMinColor(0, 0, 0);
    emisor->SetMaxColor(255, 255, 255);
  }

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    generador->SetPosition(SCREEN.GetMouseX(), SCREEN.GetMouseY());
    emisor->SetX(SCREEN.GetMouseX());
    emisor->SetY(SCREEN.GetMouseY());
    if (SCREEN.MouseButtonPressed(GLFW_MOUSE_BUTTON_2))
      emisor->Start();
    else
      emisor->Stop();
    escena1->Update(SCREEN.ElapsedTime());
    escena1->Render();
    SCREEN.Refresh();

  }
  delete escena1;
  RESOURCE.FreeResources();
}
void practica7B()
{
  SCREEN.Open(800, 600, false);
  Image *background = RESOURCE.LoadImage("data/backlayer.png");
  Image *frontground = RESOURCE.LoadImage("data/frontlayer.png");

  ParallaxScene *escena1 = new ParallaxScene(background, frontground);
  escena1->SetBackgroundColor(0, 0, 0);
  //Propiedades Parallax
  escena1->SetAutoBackSpeed(32,32);
  escena1->SetAutoFrontSpeed(-32, -32);
  escena1->SetRelativeBackSpeed(0.8, 0.8);
  escena1->SetRelativeFrontSpeed(1, 1);
  Image *alien = RESOURCE.LoadImage("data/alienanim.png", 8, 1);
  Sprite *personaje;
  if (alien)
  {
    alien->SetMidHandle();
    personaje = escena1->CreateSprite(alien);
    personaje->SetColor(255, 255, 255);
    personaje->SetFPS(16);
    personaje->SetFrameRange(0, 7);
    personaje->SetScale(5,5);
    escena1->GetCamera().FollowSprite(personaje);
  }
  double posX = SCREEN.GetWidth() / 2.0;
  double posY = SCREEN.GetHeight() / 2.0;
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    if (glfwGetKey(GLFW_KEY_UP))
      posY -= 100.0 * SCREEN.ElapsedTime();
    if (glfwGetKey(GLFW_KEY_DOWN))
      posY += 100.0 * SCREEN.ElapsedTime();
    if (glfwGetKey(GLFW_KEY_RIGHT))
      posX += 100.0 * SCREEN.ElapsedTime();
    if (glfwGetKey(GLFW_KEY_LEFT))
      posX -= 100.0 * SCREEN.ElapsedTime();

    personaje->SetPosition(posX, posY);
    escena1->Update(SCREEN.ElapsedTime());
    escena1->Render();
    SCREEN.Refresh();

  }
  delete escena1;
  RESOURCE.FreeResources();
}
void practica7()
{
  SCREEN.Open(800, 600, false);
  Image *background = RESOURCE.LoadImage("data/background.png");
  Scene *escena1 = new Scene(background);
  escena1->GetCamera().SetBounds(0.0, 0.0, background->GetWidth(), background->GetHeight());
  escena1->GetCamera().SetPosition(0, 0);
  escena1->SetBackgroundColor(0, 0, 0);
  Image *alien = RESOURCE.LoadImage("data/alienanim.png", 8, 1);
  Sprite *personaje;
  if (alien)
  {
    alien->SetMidHandle();
    personaje = escena1->CreateSprite(alien);
    personaje->SetColor(255, 255, 255);
    personaje->SetFPS(16);
    personaje->SetFrameRange(0, 7);
    personaje->SetScale(5,5);
    escena1->GetCamera().FollowSprite(personaje);
  }
  double posX = SCREEN.GetWidth() / 2.0;
  double posY = SCREEN.GetHeight() / 2.0;

  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {

    if (glfwGetKey(GLFW_KEY_UP))
      posY -= 100.0 * SCREEN.ElapsedTime();
    if (glfwGetKey(GLFW_KEY_DOWN))
      posY += 100.0 * SCREEN.ElapsedTime();
    if (glfwGetKey(GLFW_KEY_RIGHT))
      posX += 100.0 * SCREEN.ElapsedTime();
    if (glfwGetKey(GLFW_KEY_LEFT))
      posX -= 100.0 * SCREEN.ElapsedTime();

    personaje->SetPosition(posX, posY);
    escena1->Update(SCREEN.ElapsedTime());
    escena1->Render();
    SCREEN.Refresh();

  }
  delete escena1;
  RESOURCE.FreeResources();
}
void practica6C()
{
  SCREEN.Open(800, 600, false);
  Font *hola = RESOURCE.LoadFont("data/stocky.ttf",35);
  double PosX = SCREEN.GetWidth() / 2.0;
  double PosY = SCREEN.GetHeight() / 2.0;
  int direccionX = 1;
  int direccionY = 1;
  uint8 alpha = 255;
  uint8 red = 255;
  uint8 green = 0;
  uint8 blue = 0;
  Velocidades vel;
  vel.x = rand() % (255 - 127) + 128;
  vel.y = rand() % (255 - 127) + 128;
  String texto = "HOLA, mundo g";
  RENDER.SetBlendMode(RENDER.ALPHA);
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    //RENDER.Clear(255, 255, 255);
    RENDER.Clear(0, 0, 0);
    RENDER.SetColor(red, green, blue, alpha);
    
    if (PosX > (SCREEN.GetWidth() - hola->GetTextWidth(texto))){
      direccionX = -1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosX <= 0){
      direccionX = 1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosY >= SCREEN.GetHeight()){
      direccionY = -1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosY <= hola->GetTextHeight(texto)){
      direccionY = 1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }

    PosX += direccionX * vel.x * SCREEN.ElapsedTime();
    PosY += direccionY * vel.y * SCREEN.ElapsedTime();
    hola->Render(texto, PosX, PosY);
    SCREEN.Refresh();

  }
  RESOURCE.FreeResources();
}
void practica6B()
{
  SCREEN.Open(800, 600, false);
  Font *hola = RESOURCE.LoadFont("data/arial16.png");
  double PosX = SCREEN.GetWidth() / 2.0;
  double PosY = SCREEN.GetHeight() / 2.0;
  int direccionX = 1;
  int direccionY = 1;
  uint8 alpha = 255;
  uint8 red = 255;
  uint8 green = 0;
  uint8 blue = 0;
  Velocidades vel;
  vel.x = rand() % (255 - 127) + 128;
  vel.y = rand() % (255 - 127) + 128;
  String texto = "Hola, Mundo";
  RENDER.SetBlendMode(RENDER.ALPHA);
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(255, 255, 255);
    RENDER.SetColor(red, green, blue, alpha);
    
    if (PosX > (SCREEN.GetWidth() - hola->GetTextWidth(texto))){
      direccionX = -1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosX <= 0){
      direccionX = 1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosY > (SCREEN.GetHeight() - hola->GetTextHeight(texto))){
      direccionY = -1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosY <= 0){
      direccionY = 1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }

    PosX += direccionX * vel.x * SCREEN.ElapsedTime();
    PosY += direccionY * vel.y * SCREEN.ElapsedTime();
    
    hola->Render(texto, PosX, PosY);
    SCREEN.Refresh();

  }
  RESOURCE.FreeResources();
}
void practica6()
{
  SCREEN.Open(800, 600, false);
  Font *hola = RESOURCE.LoadFont("data/monospaced.png");
  double PosX = SCREEN.GetWidth() / 2.0;
  double PosY = SCREEN.GetHeight() / 2.0;
  int direccionX = 1;
  int direccionY = 1;
  uint8 alpha = 255;
  uint8 red = 255;
  uint8 green = 0;
  uint8 blue = 0;
  Velocidades vel;
  vel.x = rand() % (255 - 127) + 128;
  vel.y = rand() % (255 - 127) + 128;
  String texto = "Hola Mundo";
  while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
  {
    RENDER.Clear(0, 0, 0);
    RENDER.SetColor(red, green, blue, alpha);

    if (PosX > (SCREEN.GetWidth() - hola->GetTextWidth(texto))){
      direccionX = -1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosX <= 0){
      direccionX = 1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosY > (SCREEN.GetHeight() - hola->GetTextHeight(texto))){
      direccionY = -1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }
    if (PosY <= 0){
      direccionY = 1;
      red = rand() % 255;
      green = rand() % 255;
      blue = rand() % 255;
    }

    PosX += direccionX * vel.x * SCREEN.ElapsedTime();
    PosY += direccionY * vel.y * SCREEN.ElapsedTime();

    hola->Render(texto, PosX, PosY);
    SCREEN.Refresh();

  }
  RESOURCE.FreeResources();
}
void practica5B()
{
  SCREEN.Open(800, 600, false);
  SkeletonSprite latigo("data/animation.xml");
  Image *hueso = RESOURCE.LoadImage("data/bone.png");
  if(hueso){
    latigo.SetImage(hueso);
    latigo.SetColor(255,255,255);
    latigo.SetFPS(32);
    while (SCREEN.IsOpened() && !glfwGetKey(GLFW_KEY_ESC))
    {
      RENDER.Clear(0, 0, 0);
      latigo.SetPosition(SCREEN.GetMouseX(),SCREEN.GetMouseY());
      latigo.Update(SCREEN.ElapsedTime());
      latigo.Render();
      SCREEN.Refresh();

    }
    RESOURCE.FreeResources();
  }
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

  void *data;
  double nPosX;
  double nPosY;
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
