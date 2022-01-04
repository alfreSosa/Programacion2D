#include "../include/affector.h"
#include "../include/math.h"
#include "../include/particle.h"

Affector::Affector(bool color, bool velX, bool velY, bool velAng)
{
  m_modificarColor = color;
  m_modificarVelX = velX;
  m_modificarVelY = velY;
  m_modificarVelAng = velAng;
  m_origAncho = m_origAlto = m_finAlto = m_finAncho = 0;
  m_minr = m_ming = m_minb = m_maxr = m_maxg = m_maxb = 0;
  m_minangvel = m_minvelx = m_minvely = 0.0;
  m_maxangvel = m_maxvelx = m_maxvely = 0.0;
}

double Affector::getNuevaVelX() const
{
  return (m_minvelx == 0 && m_maxvelx == 0) ? 0 : WrapValue(rand(), m_maxvelx - m_minvelx) + m_minvelx;
}
double Affector::getNuevaVelY() const
{
  return (m_minvely == 0 && m_maxvely == 0) ? 0 : WrapValue(rand(), m_maxvelx - m_minvelx) + m_minvely;
}
double Affector::getNuevaAngleVel() const
{
  return (m_minangvel == 0 && m_maxangvel == 0) ? 0 : WrapValue(rand(), m_maxangvel - m_minangvel) + m_minangvel;
}
uint8 Affector::getNuevoRed() const
{
  if (m_maxr == 0 && m_minr == 0)
    return 0;
  return (m_maxr ==  m_minr) ? m_maxr : rand() % (m_maxr - m_minr) + m_minr;
}
uint8 Affector::getNuevoGreen() const
{
  if (m_maxg == 0 && m_ming == 0)
    return 0;
  return (m_maxg == m_ming) ? m_maxg : rand() % (m_maxg - m_ming) + m_ming;
}
uint8 Affector::getNuevoBlue() const
{
  if (m_maxb == 0 && m_minb == 0)
    return 0;
  return (m_maxb == m_minb) ? m_maxb : rand() % (m_maxb - m_minb) + m_minb;
}

void Affector::Afectar(Particle *particula)
{
  if (particula->GetX() >= m_origAncho && particula->GetX() <= m_finAncho)
    if (particula->GetY() >= m_origAlto && particula->GetY() <= m_finAlto)
    {
      if (m_modificarColor)
        particula->SetColor(getNuevoRed(), getNuevoGreen(), getNuevoBlue());
      if (m_modificarVelX)
        particula->setVelocityX(getNuevaVelX());
      if (m_modificarVelY)
        particula->setVelocityX(getNuevaVelY());
      if (m_modificarVelAng)
        particula->setVelocityAng(getNuevaAngleVel());
      particula->Alter();
    }
}