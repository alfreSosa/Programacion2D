#include "../include/font.h"
#include "../include/renderer.h"
#include "../lib/stb_image.h"
Font::Font(const String& filename) : Image(filename, 16, 16) 
{
  int x, y;
  uint8 *buffer = stbi_load(filename.ToCString(), &x, &y, NULL, 4);
  uint16 width = static_cast<uint16>(x);
  uint16 height = static_cast<uint16>(y);
  // Generamos la textura
  if (buffer){
    //aqui recorremos el buffer y creamos los glyph
    //Recorrer la celda del ancho
   
    int tamCeldasX = width / 16;
    int tamCeldasY = height / 16;
    for (y = 0; y < height; y+=tamCeldasY)
      for (x = 0; x < width; x += tamCeldasX)
      {
        Glyph car;
        //int oriX, oriY;
        for (uint16 j = 0; j < tamCeldasY; j++)
        {
          for (uint16 i = 0; i < tamCeldasX; i++)
          {
            //int it = (i * 4 + j * width) + (x + y * tamCeldasY);

            int it = ((y + j) * width + (x + i)) * 4;
            if (buffer[it] == 255 && buffer[it + 1] == 255 && buffer[it + 2] == 0)
            {
              //es amarillo
              buffer[it + 3] = 0;
              car.setOrigin(i, j);
             // oriX = i;
              //oriY = j;
            }
            else if (buffer[it] == 255 && buffer[it + 1] == 0 && buffer[it + 2] == 0)
            {
              //es rojo
              buffer[it + 3] = 0;
              car.setEnd(i,j);
              letters.Add(car);
            }
            else if (buffer[it] != 255 || buffer[it + 1] != 255 || buffer[it + 2] != 255)
            {
              //cualquier cosa que no es blanco, hacer transparente
              buffer[it + 3] = 0;
            }
          }
        }
      }
    RENDER.TexImage2D(this->GetTexId(), width, height, buffer);
  }
  stbi_image_free(buffer);

};
uint16 Font::GetSize() const
{
  return this->GetHeight();
}

uint32 Font::GetTextHeight(const String& text) const
{
  if (letters.Size() > 0){
    //buscamos la mas alta
    uint16 iniY, finY;
    uint16 max = 0;
    for (int i = 0; i < text.Length(); i++){
      iniY = letters[text[i]].getOriginY();
      finY = letters[text[i]].getEndY();
      if (finY - iniY > max)
      {
        max = finY - iniY;
      }
    }
    return max;
  }
  else{
    return this->GetHeight();
  }
}

uint32 Font::GetTextWidth(const String& text) const
{
  if (letters.Size() > 0){
    //buscamos la mas alta
    uint16 iniX, finX;
    uint16 max = 0;
    for (int32 i = 0; i < text.Length(); i++){
      iniX = letters[text[i]].getOriginX();
      finX = letters[text[i]].getEndX();
        max += finX - iniX;
    }
    return max;
  }
  else{
    return this->GetWidth() * text.Length();
  }
  
}

void Font::Render(const String& text, double x, double y)
{
  if (letters.Size() == 0){
    double offset = 0.0;
    uint32 anchoCaracter = this->GetWidth();
    for (int32 i = 0; i < text.Length(); i++){
      RENDER.DrawImage(this, x + offset, y, CHARTOUI32(text[i]));
      offset += anchoCaracter;
    }
  }
  else
  {
    double offsetX = 0.0;
    uint32 anchoCaracter;
    for (int32 i = 0; i < text.Length(); i++){
      uint16 eX = letters[text[i]].getEndX();
      uint16 oY = letters[text[i]].getOriginY();
      RENDER.DrawImage(this, x + offsetX, y + oY, CHARTOUI32(text[i]));
      anchoCaracter = this->GetWidth() - (this->GetWidth() - eX);
      offsetX += anchoCaracter;
    }
  }
}