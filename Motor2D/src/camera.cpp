#include "../include/camera.h"
#include "../include/sprite.h"
#include "../include/screen.h"

Camera::Camera()
{
  x = 0;
  y = 0;
  boundx0 = 0;
  boundx1 = 0;
  boundy0 = 0;
  boundy1 = 0;
  followingSprite = NULL;
}
void Camera::SetPosition(double x, double y)
{
  if (!this->HasBounds()){ 
    this->x = x; this->y = y; 
  }
  else{
    if (x >= boundx0 && x <= (boundx1 - SCREEN.GetWidth())) this->x = x;
    if (y >= boundy0 && y <= (boundy1 - SCREEN.GetHeight())) this->y = y;
  }
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1)
{
  boundx0 = bx0; boundy0 = by0;
  boundx1 = bx1; boundy1 = by1;
}

void Camera::SetX(double x)
{
  if (!this->HasBounds())
    this->x = x;
  else
    if (x >= boundx0 && x <= (boundx1 - SCREEN.GetWidth())) this->x = x;
}

void Camera::SetY(double y)
{
  if (!this->HasBounds())
    this->y = y;
  else
    if (y >= boundy0 && y <= (boundy1 - SCREEN.GetHeight())) this->y = y;
}

double Camera::GetX() const
{
  return x;
}

double Camera::GetY() const
{
  return y;
}

bool Camera::HasBounds() const
{
  if (boundx0 != boundx1 || boundy0 != boundy1 ) return true;
  else return false;
}

void Camera::FollowSprite(const Sprite *sprite)
{
  followingSprite = sprite;
}
double Camera::GetMaxX() const 
{
  return boundx1 - SCREEN.GetWidth();
}
double Camera::GetMaxY() const
{
  return boundy1 - SCREEN.GetHeight();
}
double Camera::GetMinX() const
{
  return boundx0;
}
double Camera::GetMinY() const
{
  return boundy0;
}

void Camera::Update()
{
  if (followingSprite)
  {
    //seguir al sprite
    this->SetX(followingSprite->GetScreenX()); //menos la mitad del ancho
    this->SetY(followingSprite->GetScreenY()); //menos la mitad del alto
  }
}