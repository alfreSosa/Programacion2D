#include "../include/affector.h"
#include "../include/math.h"
#include "../include/particle.h"

Affector::Affector(bool color, bool velX, bool velY, bool velAng)
{
  modificarColor = color;
  modificarVelX = velX;
  modificarVelY = velY;
  modificarVelAng = velAng;
  origAncho = origAlto = finAlto = finAncho = 0;
  minr = ming = minb = maxr = maxg = maxb = 0;
  minangvel = minvelx = minvely = 0.0;
  maxangvel = maxvelx = maxvely = 0.0;
}
double Affector::getNuevaVelX() const
{
  return WrapValue(rand(), maxvelx - minvelx) + minvelx;
}
double Affector::getNuevaVelY() const
{
  return WrapValue(rand(), maxvelx - minvelx) + minvely;
}
double Affector::getNuevaAngleVel() const
{
  return WrapValue(rand(), maxangvel - minangvel) + minangvel;
}
uint8 Affector::getNuevoRed() const
{
  return rand() % (maxr - minr) + minr;
}
uint8 Affector::getNuevoGreen() const
{
  return rand() % (maxg - ming) + ming;
}
uint8 Affector::getNuevoBlue() const
{
  return rand() % (maxb - minb) + minb;
}

Particle Affector::Afectar(Particle particula)
{
   
  if (!particula.isAfected())
  {
    if (particula.GetX() >= origAncho && particula.GetX() <= finAncho)
      if (particula.GetY() >= origAlto && particula.GetY() <= finAlto)
      {
        if (modificarColor)
          particula.SetColor(getNuevoRed(), getNuevoGreen(), getNuevoBlue());
        if (modificarVelX)
          particula.setVelocityX(getNuevaVelX());
        if (modificarVelY)
          particula.setVelocityX(getNuevaVelY());
        if (modificarVelAng)
          particula.setVelocityAng(getNuevaAngleVel());
        particula.Alter();
      }
  }
  return particula;
}