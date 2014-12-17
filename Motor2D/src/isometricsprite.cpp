#include "../include/isometricsprite.h"
#include "../include/math.h"
#include "../include/image.h"

IsometricSprite::IsometricSprite(Image *image): Sprite(image)
{
  z = 0.0;
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
  x = GetX() - GetImage()->GetWidth() * abs(GetScaleX());
  y = GetY() - GetImage()->GetWidth() * abs(GetScaleX());
  w = GetImage()->GetWidth() * abs(GetScaleX());
  h = GetImage()->GetWidth() * abs(GetScaleX());

  Sprite::UpdateCollisionBox(x, y, w, h);
}
