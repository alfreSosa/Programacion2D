#ifndef _GLYPH_H
#define _GLYPH_H

#include "string.h"
#include "types.h"
#include "image.h"
class Glyph
{
private:
  uint16 m_originX;
  uint16 m_originY;
  uint16 m_endX;
  uint16 m_endY;
  double m_yoffset;
  bool m_isTTF;
  Image * m_charTTF;
public:
  Glyph() { m_charTTF = nullptr; }
  ~Glyph() { if(m_charTTF) delete m_charTTF; }
  virtual void setOrigin(uint16 originX, uint16 originY){ this->m_originX = originX; this->m_originY = originY; }
  virtual uint16 getOriginX() const { return m_originX; }
  virtual uint16 getOriginY() const{ return m_originY; }
  virtual void setEnd(uint16 endX, uint16 endY){ this->m_endX = endX;  this->m_endY = endY; }
  virtual uint16 getEndX() const { return m_endX; }
  virtual uint16 getEndY() const { return m_endY; }
  virtual void setYOffset(double offset) { m_yoffset = offset; }
  virtual double getYOffset() const { return m_yoffset; }
  virtual bool getisTTF() const { return m_isTTF; }
  virtual void setIsTTF (bool ttf) { m_isTTF = ttf; }
  virtual Image * getcharTTF() const { return m_charTTF; }
  virtual void setcharTTF (uint8 *buffer, uint16 width, uint16 height) { m_charTTF = new Image(buffer, width, height); }
};
#endif