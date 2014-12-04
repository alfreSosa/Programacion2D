#ifndef _PIXELCOLLISION_H
#define _PIXELCOLLISION_H

#include "collision.h"
#include "../include/collisionmanager.h"

class PixelCollision : public Collision {
public:
  PixelCollision(const CollisionPixelData* pixels, double* x, double* y) : pixels(pixels), x(x), y(y) {};

  virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(pixels, *x, *y); };

  virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx,cy,cradius,pixels,*x, *y); }
  virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(pixels, *x, *y, rx, ry, rwidth, rheight); }
  virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixel(pixels, px, py, this->pixels, *x, *y); }
private:
  double* x;
  double* y;
  const CollisionPixelData* pixels;
};
#endif