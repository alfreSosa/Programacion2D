#ifndef _AFFECTOR_H
#define _AFFECTOR_H

#include "string.h"
#include "types.h"
class Particle;
class Affector
{
public:
  Affector(bool color = false, bool velX = false, bool velY = false, bool velAng = false);
  virtual ~Affector() { }
  virtual void setAncho(double orig, double fin) { m_origAncho = orig; m_finAncho = fin; }
  virtual void setAlto(double orig, double fin) { m_origAlto = orig; m_finAlto = fin; }
  virtual void SetVelocityX(double minvelx, double maxvelx)  { this->m_minvelx = (maxvelx == minvelx) ? 0 : minvelx; this->m_maxvelx = maxvelx; }
  virtual void SetVelocityY(double minvely, double maxvely)  { this->m_minvely = (maxvely == minvely) ? 0 : minvely; this->m_maxvely = maxvely; }
  virtual void SetAngularVelocity(double minangvel, double maxangvel) { this->m_minangvel = (maxangvel == minangvel) ? 0 : minangvel; this->m_maxangvel = maxangvel; }
  virtual void SetMinColor(uint8 r, uint8 g, uint8 b){ m_minr = r; m_ming = g; m_minb = b; }
  virtual void SetMaxColor(uint8 r, uint8 g, uint8 b){ m_maxr = r; m_maxg = g; m_maxb = b; }
  virtual double getOrigenAncho() const { return m_origAncho; }
  virtual double getFinAncho() const { return m_finAncho; }
  virtual double getOrigenAlto() const { return m_origAlto; }
  virtual double getFinAlto() const { return m_finAlto; }
  virtual void Afectar(Particle *particula);
  virtual double getNuevaVelX() const;
  virtual double getNuevaVelY() const;
  virtual double getNuevaAngleVel() const;
  virtual uint8 getNuevoRed() const;
  virtual uint8 getNuevoGreen() const;
  virtual uint8 getNuevoBlue() const;
  virtual void enableColor() { m_modificarColor = true; }
  virtual void enableVelX() { m_modificarVelX = true; }
  virtual void enableVelY() { m_modificarVelY = true; }
  virtual void enableVelAngle() { m_modificarVelAng = true; }


private:
  double m_origAncho, m_finAncho;
  double m_origAlto, m_finAlto;
  bool m_modificarColor;
  uint8 m_minr, m_ming, m_minb;
  uint8 m_maxr, m_maxg, m_maxb;
  bool m_modificarVelX;
  double m_minvelx, m_maxvelx;
  bool m_modificarVelY;
  double m_minvely, m_maxvely;
  bool m_modificarVelAng;
  double m_minangvel, m_maxangvel;
};
#endif