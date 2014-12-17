#ifndef _ISOMETRICSPRITE_H
#define _ISOMETRICSPRITE_H

#include "types.h"
#include "sprite.h"

class IsometricSprite: public Sprite
{
public:
  IsometricSprite(Image* image);
  virtual ~IsometricSprite() { }
  virtual void SetPosition(double x, double y, double z);
  virtual void SetZ(double z) { this->z = z; }
  virtual double GetZ() const { return z; }
  virtual void SetCollision(CollisionMode mode);
  virtual void Update(double elapsed, const Map* map = NULL);
protected:
  virtual void UpdateCollisionBox();
private:
  double z;

};
#endif