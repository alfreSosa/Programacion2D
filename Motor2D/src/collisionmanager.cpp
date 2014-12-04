#include "../include/collisionmanager.h"
#include "../include/math.h"
CollisionManager* CollisionManager::manager = NULL;

const CollisionManager& CollisionManager::Instance()
{
  if (!manager)
    manager = new CollisionManager;
  return *manager;
}
bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const
{
  return RectsOverlap(x1, y1, w1, h1, x2, y2, w2, h2);
}
bool  CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const
{
  return false;
}
bool  CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const
{
  return false;
}
