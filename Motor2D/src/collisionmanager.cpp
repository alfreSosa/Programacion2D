#include "../include/collisionmanager.h"
#include "../include/collisionpixeldata.h"
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
  return Distance(x1, y1, x2, y2) <= r1 + r2;;
}
bool  CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const
{
  double x;
  double y;
  ClosestPointToRect(cx, cy, rx, ry, rw, rh, &x, &y);
  return Distance(x,y,cx,cy) <= cr;
}

//COLISIONES PIXEL
bool CollisionManager::PixelsToPixel(const CollisionPixelData *p1, double x1, double y1, const CollisionPixelData *p2, double x2, double y2) const
{
  if (RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight()))
  {
    double outx, outy, outwidth, outheight;
    OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &outx, &outy, &outwidth, &outheight);
    
    //obtener las cordenadas relativas dentro de cada figura
    uint32 p1x = DOUBLETOUI32((outx == x1) ? x1 : x1 + p1->GetWidth() - outwidth);
    uint32 p1y = DOUBLETOUI32((outy == y1) ? y1 : y1 + p1->GetHeight() - outheight);
    uint32 p2x = DOUBLETOUI32((outx == x2) ? x2 : x2 + p2->GetWidth() - outwidth);
    uint32 p2y = DOUBLETOUI32((outy == y2) ? y2 : y2 + p2->GetHeight() - outheight);
    for (uint32 i = 0; i < DOUBLETOUI32(outheight); i++)
      for (uint32 j = 0; j < DOUBLETOUI32(outwidth); j++)
        if (p1->GetData(j + p1x, i + p1y) && p1->GetData(j + p2x, i + p2y))
          return true;
  }
  return false;
};
bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData * pixels, double px, double py) const
{ 
  double outx, outy;
  ClosestPointToRect(cx, cy, px, py, pixels->GetWidth(), pixels->GetHeight(), &outx, &outy);
  if (Distance(outx, outy, cx, cy) <= cr)
  {
    //falla en el caso del cuadrado colisione por abajo
    //hacer cuadrado
    for (uint32 i = DOUBLETOUI32(outy); i < DOUBLETOUI32(cr); i++)
      for (uint32 j = DOUBLETOUI32(outx); j < DOUBLETOUI32(cr); j++)
          if(pixels->GetData(j, i)) return true;
  }
  return false;
  
};
bool CollisionManager::PixelsToRect(const CollisionPixelData *pixels, double px, double py, double rx, double ry, double rw, double rh) const
{ 
  if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh))
  {
    double outx, outy, outwidth, outheight;
    OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &outx, &outy, &outwidth, &outheight);
    uint32 p1x = DOUBLETOUI32((outx == px) ? px : px + pixels->GetWidth() - outwidth);
    uint32 p1y = DOUBLETOUI32((outy == py) ? py : py + pixels->GetHeight() - outheight);
    for (uint32 i = p1y; i < DOUBLETOUI32(outheight); i++)
      for (uint32 j = p1x; j < DOUBLETOUI32(outwidth); j++)
        if (pixels->GetData(j, i)) return true;
  }
  return false; 
};
