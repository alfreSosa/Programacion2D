#ifndef _FONT_H
#define _FONT_H

#include "string.h"
#include "types.h"
#include "image.h"
#include "glyph.h"

class Font : public Image
{
private:
  Array<Glyph> letters;
public:
  Font(const String& filename);
  virtual uint16 GetSize() const;
  virtual uint32 GetTextWidth(const String& text) const;
  virtual uint32 GetTextHeight(const String& text) const;
  virtual void Render(const String& text, double x, double y);
};
#endif