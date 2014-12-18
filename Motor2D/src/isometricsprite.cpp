#include "../include/isometricsprite.h"
#include "../include/math.h"
#include "../include/image.h"

IsometricSprite::IsometricSprite(Image *image): Sprite(image)
{
  z = wColission = hColission = 0.0;
  
}

void IsometricSprite::SetPosition(double x, double y, double z)
{
  Sprite::SetPosition(x, y);
  this->z = z;
}

void IsometricSprite::SetCollision(CollisionMode mode)
{
  if (mode == Sprite::COLLISION_PIXEL)
    Sprite::SetCollision(Sprite::COLLISION_RECT);
  else
    Sprite::SetCollision(mode);
}

void IsometricSprite::Update(double elapsed, const Map* map)
{
  double screenX, screenY;
  Sprite::Update(elapsed, map);
  TransformIsoCoords(GetX(), GetY(), z, &screenX, &screenY);
  SetPositionScreen(screenX, screenY);
}

void IsometricSprite::UpdateCollisionBox()
{
  double x, y, w, h;

  double ancho = (wColission == 0) ? GetImage()->GetWidth() : wColission;
  double alto = (hColission == 0) ? GetImage()->GetWidth() : hColission;

  x = GetX() - GetImage()->GetWidth() * abs(GetScaleX());
  y = GetY() - GetImage()->GetWidth() * abs(GetScaleX());
  w = ancho * abs(GetScaleX());
  h = alto * abs(GetScaleX());

  Sprite::UpdateCollisionBox(x, y, w, h);
}


