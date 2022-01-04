#include "../include/camera.h"
#include "../include/sprite.h"
#include "../include/screen.h"

Camera::Camera()
{
  m_x = 0;
  m_y = 0;
  m_boundx0 = 0;
  m_boundx1 = 0;
  m_boundy0 = 0;
  m_boundy1 = 0;
  m_followingSprite = NULL;
}
void Camera::SetPosition(double x, double y)
{
  if (!this->HasBounds()){ 
    this->m_x = x; this->m_y = y; 
  }
  else{
    if (x < m_boundx0) this->m_x = m_boundx0;
    else if (x > m_boundx1 - SCREEN.GetWidth()) this->m_x = m_boundx1 - SCREEN.GetWidth();
    else this->m_x = x;

    if (y < m_boundy0) this->m_y = m_boundy0;
    else if (y > m_boundy1 - SCREEN.GetHeight()) this->m_y = m_boundy1 - SCREEN.GetHeight();
    else this->m_y = y;
  }
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1)
{
  m_boundx0 = bx0; m_boundy0 = by0;
  m_boundx1 = bx1; m_boundy1 = by1;
}

void Camera::SetX(double x)
{
  if (!this->HasBounds())
    this->m_x = x;
  else
    if (x < m_boundx0) this->m_x = m_boundx0;
    else if (x > m_boundx1 - SCREEN.GetWidth()) this->m_x = m_boundx1 - SCREEN.GetWidth();
    else  this->m_x = x;
}

void Camera::SetY(double y)
{
  if (!this->HasBounds())
    this->m_y = y;
  else
    if (y < m_boundy0) this->m_y = m_boundy0;
    else if (y > m_boundy1 - SCREEN.GetHeight()) this->m_y = m_boundy1 - SCREEN.GetHeight();
    else this->m_y = y;
}

double Camera::GetX() const
{
  return m_x;
}

double Camera::GetY() const
{
  return m_y;
}

bool Camera::HasBounds() const
{
  if (m_boundx0 != m_boundx1 || m_boundy0 != m_boundy1 ) return true;
  else return false;
}

void Camera::FollowSprite(const Sprite *sprite)
{
  m_followingSprite = sprite;
}
double Camera::GetMaxX() const 
{
  return m_boundx1 - SCREEN.GetWidth();
}
double Camera::GetMaxY() const
{
  return m_boundy1 - SCREEN.GetHeight();
}
double Camera::GetMinX() const
{
  return m_boundx0;
}
double Camera::GetMinY() const
{
  return m_boundy0;
}

void Camera::Update()
{
  if (m_followingSprite)
  {
    this->SetX(m_followingSprite->GetScreenX() - SCREEN.GetWidth() / 2.0); //menos la mitad del ancho
    this->SetY(m_followingSprite->GetScreenY() - SCREEN.GetHeight()/ 2.0); //menos la mitad del alto
  }
}