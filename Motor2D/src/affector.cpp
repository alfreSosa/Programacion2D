#include "../include/affector.h"
#include "../include/math.h"

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