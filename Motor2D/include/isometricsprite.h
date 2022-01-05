#ifndef _ISOMETRICSPRITE_H
#define _ISOMETRICSPRITE_H

#include "types.h"
#include "sprite.h"

class IsometricSprite : public Sprite
{
public:
  IsometricSprite(Image* image);
  virtual ~IsometricSprite() { }
  virtual void SetPosition(double x, double y, double z);
  virtual void SetZ(double z) { this->m_z = z; }
  virtual double GetZ() const { return m_z; }
  virtual void SetCollision(CollisionMode mode);
  virtual void Update(double elapsed, const Map* map = NULL);
  virtual void SetCollisionTam(double width = 0.0, double height = 0.0) { m_wColission = width; m_hColission = height; }
  virtual double GetScreenX() const { return m_screenX; }
  virtual double GetScreenY() const { return m_screenY; }
protected:
  virtual void UpdateCollisionBox();
private:
  double m_screenX, m_screenY;
  double m_z;
  double m_wColission;
  double m_hColission;


};
#endif