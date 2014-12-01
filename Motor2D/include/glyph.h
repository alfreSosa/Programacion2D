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
  double yoffset;
  bool isTTF;
  Image * charTTF;
public:
  Glyph() { charTTF = NULL; };
  ~Glyph() { if(charTTF) delete charTTF; };
  virtual void setOrigin(uint16 originX, uint16 originY){ this->originX = originX; this->originY = originY; };
  virtual uint16 getOriginX() const { return originX; };
  virtual uint16 getOriginY() const{ return originY; };
  virtual void setEnd(uint16 endX, uint16 endY){ this->endX = endX;  this->endY = endY; };
  virtual uint16 getEndX() const { return endX; };
  virtual uint16 getEndY() const { return endY; };
  virtual void setYOffset(double offset) { yoffset = offset; };
  virtual double getYOffset() const { return yoffset; };
  virtual bool getisTTF() const { return isTTF; };
  virtual void setIsTTF (bool ttf) { isTTF = ttf; };
  virtual Image * getcharTTF() const { return charTTF; };
  virtual void setcharTTF (uint8 *buffer, uint32 width, uint32 height) { charTTF = new Image(buffer, width, height); };
};
#endif