#include "../include/font.h"
#include "../include/renderer.h"

uint16 Font::GetSize() const
{
  return this->GetHeight();
}

uint32 Font::GetTextHeight(const String& text) const
{
  return this->GetHeight();//en glifos se devuelve la altura del mas alto
}

uint32 Font::GetTextWidth(const String& text) const
{
  return this->GetWidth() * text.Length();
}

void Font::Render(const String& text, double x, double y)
{
  double offset = 0.0;
  uint32 anchoCaracter = this->GetWidth();
  for (int32 i = 0; i < text.Length(); i++){
    RENDER.DrawImage(this, x + offset, y, CHARTOUI32(text[i])); 
    offset += anchoCaracter;
  }
}