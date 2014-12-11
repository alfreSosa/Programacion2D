#ifndef _AFFECTOR_H
#define _AFFECTOR_H

#include "string.h"
#include "types.h"
class Particle;
class Affector
{
public:
  Affector(bool color = false, bool velX = false, bool velY = false, bool velAng = false);
  ~Affector() { modificarColor = modificarVelX =  modificarVelY = modificarVelAng = false; }
  virtual void setAncho(double orig, double fin) { origAncho = orig; finAncho = fin; }
  virtual void setAlto(double orig, double fin) { origAlto = orig; finAlto = fin; }
  virtual void SetVelocityX(double minvelx, double maxvelx)  { this->minvelx = (maxvelx == minvelx) ? 0 : minvelx; this->maxvelx = maxvelx; }
  virtual void SetVelocityY(double minvely, double maxvely)  { this->minvely = (maxvely == minvely) ? 0 : minvely; this->maxvely = maxvely; }
  virtual void SetAngularVelocity(double minangvel, double maxangvel) { this->minangvel = (maxangvel == minangvel) ? 0 : minangvel; this->maxangvel = maxangvel; }
  virtual void SetMinColor(uint8 r, uint8 g, uint8 b){ minr = r; ming = g; minb = b; }
  virtual void SetMaxColor(uint8 r, uint8 g, uint8 b){ maxr = r; maxg = g; maxb = b; }
  virtual double getOrigenAncho() const { return origAncho; }
  virtual double getFinAncho() const { return finAncho; }
  virtual double getOrigenAlto() const { return origAlto; }
  virtual double getFinAlto() const { return finAlto; }
  virtual Particle Afectar(Particle particula);
  virtual double getNuevaVelX() const;
  virtual double getNuevaVelY() const;
  virtual double getNuevaAngleVel() const;
  virtual uint8 getNuevoRed() const;
  virtual uint8 getNuevoGreen() const;
  virtual uint8 getNuevoBlue() const;
  virtual void enableColor() { modificarColor = true; }
  virtual void enableVelX() { modificarVelX = true; }
  virtual void enableVelY() { modificarVelY = true; }
  virtual void enableVelAngle() { modificarVelAng = true; }


private:
  double origAncho, finAncho;
  double origAlto, finAlto;
  bool modificarColor;
  uint8 minr, ming, minb;
  uint8 maxr, maxg, maxb;
  bool modificarVelX;
  double minvelx, maxvelx;
  bool modificarVelY;
  double minvely, maxvely;
  bool modificarVelAng;
  double minangvel, maxangvel;
};
#endif