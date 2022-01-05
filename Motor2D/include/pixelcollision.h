#ifndef _PIXELCOLLISION_H
#define _PIXELCOLLISION_H

#include "collision.h"
#include "../include/collisionmanager.h"

class PixelCollision : public Collision {
public:
  PixelCollision(const CollisionPixelData* pixels, double* x, double* y) : m_pixels(pixels),m_x(x), m_y(y) {}

  virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(m_pixels, *m_x, *m_y); }

  virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx,cy,cradius,m_pixels,*m_x, *m_y); }
  virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(m_pixels, *m_x, *m_y, rx, ry, rwidth, rheight); }
  virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixel(pixels, px, py, this->m_pixels, *m_x, *m_y); }
private:
  double* m_x;
  double* m_y;
  const CollisionPixelData* m_pixels;
};
#endif