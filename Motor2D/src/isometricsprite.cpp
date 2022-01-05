#include "../include/isometricsprite.h"
#include "../include/math.h"
#include "../include/image.h"

IsometricSprite::IsometricSprite(Image *image): Sprite(image)
{
  m_z = m_wColission = m_hColission = 0.0;
  
}

void IsometricSprite::SetPosition(double x, double y, double z)
{
  Sprite::SetPosition(x, y);
  this->m_z = z;
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
  Sprite::Update(elapsed, map);
  TransformIsoCoords(GetX(), GetY(), m_z, &m_screenX, &m_screenY);
}

void IsometricSprite::UpdateCollisionBox()
{
  double x, y, w, h;

  double ancho = (m_wColission == 0) ? GetImage()->GetWidth() : m_wColission;
  double alto = (m_hColission == 0) ? GetImage()->GetWidth() : m_hColission;

  x = GetX() - GetImage()->GetWidth() * abs(GetScaleX());
  y = GetY() - GetImage()->GetWidth() * abs(GetScaleX());
  w = ancho * abs(GetScaleX());
  h = alto * abs(GetScaleX());

  Sprite::UpdateCollisionBox(x, y, w, h);
}


