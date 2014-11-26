#ifndef _FONT_H
#define _FONT_H

#include "string.h"
#include "types.h"
#include "image.h"

class Font : public Image
{
public:
  Font(const String& filename) : Image(filename, 16, 16) { };
  virtual uint16 GetSize() const;
  virtual uint32 GetTextWidth(const String& text) const;
  virtual uint32 GetTextHeight(const String& text) const;
  virtual void Render(const String& text, double x, double y);
};
#endif