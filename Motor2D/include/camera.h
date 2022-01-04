#ifndef _CAMERA_H
#define _CAMERA_H

#include "types.h"

class Sprite;
class Camera
{
public:
  Camera();
  virtual void SetPosition(double x, double y);
  virtual void SetX(double x);
  virtual void SetY(double y);
  virtual double GetX() const;
  virtual double GetY() const;
  virtual void SetBounds(double bx0, double by0, double bx1, double by1);
  virtual bool HasBounds() const;
  virtual double GetMinX() const;
  virtual double GetMinY() const;
  virtual double GetMaxX() const;
  virtual double GetMaxY() const;
  virtual void FollowSprite(const Sprite * sprite);
  virtual void Update();
private:
  double m_x, m_y;
  double m_boundx0, m_boundy0, m_boundx1, m_boundy1;
  const Sprite *m_followingSprite;
};
#endif