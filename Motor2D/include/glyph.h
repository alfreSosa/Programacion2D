#ifndef _GLYPH_H
#define _GLYPH_H

#include "string.h"
#include "types.h"
#include "image.h"
class Glyph
{
private:
  uint16 originX;
  uint16 originY;
  uint16 endX;
  uint16 endY;
public:
  Glyph(){ };
  virtual void setOrigin(uint16 originX, uint16 originY){ this->originX = originX; this->originY = originY; };
  virtual uint16 getOriginX() const { return originX; };
  virtual uint16 getOriginY() const{ return originY; };
  virtual void setEnd(uint16 endX, uint16 endY){ this->endX = endX;  this->endY = endY; };
  virtual uint16 getEndX() const { return endX; };
  virtual uint16 getEndY() const { return endY; };
};
#endif