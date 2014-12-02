#include "../include/parallaxscene.h"
#include "../include/image.h"
#include "../include/renderer.h"

ParallaxScene::ParallaxScene(Image* imageBack, Image* imageFront) : Scene(imageBack)
{
  backLayer = imageBack; frontLayer = imageFront;
  backX = backY = frontX = frontY = 0.0;
  relBackSpeedX = relFrontSpeedX = 0.0;
  relBackSpeedY = relFrontSpeedY = 0.0;
  autoBackSpeedX = autoFrontSpeedX = 0.0;
  autoBackSpeedY = autoFrontSpeedY = 0.0;
}
const Image* ParallaxScene::GetBackLayer() const
{
  return backLayer;
}
const Image* ParallaxScene::GetFrontLayer() const
{
  return frontLayer;
}
void ParallaxScene::SetRelativeBackSpeed(double x, double y)
{
  relBackSpeedX = x;
  relBackSpeedY = y;
}
void ParallaxScene::SetRelativeFrontSpeed(double x, double y)
{
  relFrontSpeedX = x;
  relFrontSpeedY = y;
}
void ParallaxScene::SetAutoBackSpeed(double x, double y)
{
  autoBackSpeedX = x;
  autoBackSpeedY = y;
}
void ParallaxScene::SetAutoFrontSpeed(double x, double y)
{
  autoFrontSpeedX = x;
  autoFrontSpeedY = y;
}
void ParallaxScene::Update(double elapsed, Map* map)
{
  //aqui actualizar posicion
}
void ParallaxScene::RenderBackground() const
{
  //render pensar luego
}