#ifndef _AFFECTOR_H
#define _AFFECTOR_H

#include "types.h"
class Affector
{
public:
  virtual void setAncho(double orig, double fin) { origAncho = orig; finAncho = fin; };
  virtual void setAlto(double orig, double fin) { origAlto = orig; finAlto = fin; };
  virtual void SetVelocityX(double minvelx, double maxvelx)  { this->minvelx = minvelx; this->maxvelx = maxvelx; };
  virtual void SetVelocityY(double minvely, double maxvely)  { this->minvely = minvely; this->maxvely = maxvely; };
  virtual void SetAngularVelocity(double minangvel, double maxangvel) { this->minangvel = minangvel; this->maxangvel = maxangvel; };
  virtual void SetMinColor(uint8 r, uint8 g, uint8 b){ minr = r; ming = g; minb = b; };
  virtual void SetMaxColor(uint8 r, uint8 g, uint8 b){ maxr = r; maxg = g; maxb = b; };
  virtual double getOrigenAncho() const { return origAncho; };
  virtual double getFinAncho() const { return finAncho; };
  virtual double getOrigenAlto() const { return origAlto; };
  virtual double getFinAlto() const { return finAlto; };
  virtual double getNuevaVelX() const;
  virtual double getNuevaVelY() const;
  virtual double getNuevaAngleVel() const;
  virtual uint8 getNuevoRed() const;
  virtual uint8 getNuevoGreen() const;
  virtual uint8 getNuevoBlue() const;

private:
  double origAncho, finAncho;
  double origAlto, finAlto;
  uint8 minr, ming, minb;
  uint8 maxr, maxg, maxb;
  double minvelx, maxvelx;
  double minvely, maxvely;
  double minangvel, maxangvel;
};
#endif