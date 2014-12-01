#include "../include/font.h"
#include "../include/renderer.h"
#include "../lib/stb_image.h"
#include "../lib/stb_truetype.h"

Font::Font(const String& filename) : Image(filename, 16, 16) 
{
  int x, y;
  uint8 *buffer = stbi_load(filename.ToCString(), &x, &y, NULL, 4);
  uint16 width = static_cast<uint16>(x);
  uint16 height = static_cast<uint16>(y);
  // Generamos la textura
  if (buffer){
    Glyph *car;
    int tamCeldasX = width / 16;
    int tamCeldasY = height / 16;
    for (y = 0; y < height; y+=tamCeldasY)
      for (x = 0; x < width; x += tamCeldasX)
      {
    
        //int oriX, oriY;
        for (uint16 j = 0; j < tamCeldasY; j++)
        {
          for (uint16 i = 0; i < tamCeldasX; i++)
          {
            int it = ((y + j) * width + (x + i)) * 4;
            if (buffer[it] == 255 && buffer[it + 1] == 255 && buffer[it + 2] == 0)
            {
              //es amarillo
              buffer[it + 3] = 0;
              car = new Glyph;
              car->setOrigin(i, j);
            }
            else if (buffer[it] == 255 && buffer[it + 1] == 0 && buffer[it + 2] == 0)
            {
              //es rojo
              buffer[it + 3] = 0;
              car->setEnd(i,j);
              car->setYOffset(0.0);
              car->setIsTTF(false);
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
  tamFuente = this->GetHeight();
};
Font::Font(const String& filename, uint32 tamFuente)
{
  if(filename.ExtractExt().Lower() == "ttf"){ //to lower case
    this->tamFuente = tamFuente;
    FILE* handle = fopen(filename.ToCString(), "rb");
	  if ( handle )
    {
	    fseek(handle, 0, SEEK_END);
	    long size = ftell(handle);
	    fseek(handle, 0, SEEK_SET);
	  
      uint8* buf = (uint8*)malloc(size);
	    fread(buf, sizeof(uint8), size, handle);
	    fclose(handle);

      stbtt_bakedchar charData[256];
      bool imgPacked = false;
      int imgsize = 32;
      uint8* alphaBuffer = NULL;
      while ( !imgPacked ) {
        alphaBuffer = (uint8*)malloc(imgsize * imgsize);
        if ( stbtt_BakeFontBitmap(buf, 0, static_cast<float>(tamFuente), alphaBuffer, imgsize, imgsize, 0, 256, charData) > 0 ) {
          imgPacked = true;
        } else {
          free(alphaBuffer);
          imgsize *= 2;
        }
      }
	    free(buf);

	    uint8* colorBuffer = (uint8*)malloc(imgsize * imgsize * 4);
	    for ( int i = 0; i < imgsize*imgsize; i++ ) {
		    colorBuffer[i*4 + 0] = alphaBuffer[i];
		    colorBuffer[i*4 + 1] = alphaBuffer[i];
		    colorBuffer[i*4 + 2] = alphaBuffer[i];
		    colorBuffer[i*4 + 3] = alphaBuffer[i];
      }
	    free(alphaBuffer);
      Glyph *car;
      for ( unsigned int i = 0; i < 256; i++ ) {
        car = new Glyph;
        uint32 width = charData[i].x1 - charData[i].x0;
        uint32 height = charData[i].y1 - charData[i].y0;
        if (i == 32) {
          car->setOrigin(0, charData[i].y0);
          car->setEnd(tamFuente / 3, charData[i].y1);
        }
        else{
          car->setOrigin(charData[i].x0, charData[i].y0);
          car->setEnd(charData[i].x1, charData[i].y1);
        }
        car->setYOffset(charData[i].yoff);
        car->setIsTTF(true);

        uint8 *bufferTTF = (uint8*)malloc(width * 4 * height);
        for (uint32 j = 0; j < height; j++)
          memcpy(&bufferTTF[width * 4 * j], &colorBuffer[imgsize * 4 * (j + car->getOriginY()) + car->getOriginX() * 4], width * 4);

        car->setcharTTF(bufferTTF, width, height);
        free(bufferTTF);
        letters.Add(car);
	    }
      free(colorBuffer);
	  }
  }
	
}
uint16 Font::GetSize() const
{
  return tamFuente;
}

uint32 Font::GetTextHeight(const String& text) const
{
  if (letters.Size() > 0){
    //buscamos la mas alta
    uint16 iniY, finY;
    uint16 max = 0;
    for (int i = 0; i < text.Length(); i++){
      iniY = letters[text[i]]->getOriginY();
      finY = letters[text[i]]->getEndY();
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
      iniX = letters[text[i]]->getOriginX();
      finX = letters[text[i]]->getEndX();
        max += finX - iniX;
    }
    return max;
  }
  else{
    return this->GetWidth() * text.Length();
  }
  
}

void Font::Render(const String& text, double x, double y) const
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
    if( letters[0]->getisTTF()){
      double offsetX = 0.0;
      uint32 anchoCaracter;
      for (int32 i = 0; i < text.Length(); i++){
        uint16 eX = letters[text[i]]->getEndX();
        uint16 oX = letters[text[i]]->getOriginX();
        uint16 oY = letters[text[i]]->getOriginY();
        uint16 eY = letters[text[i]]->getEndY();
        double offsetY = letters[text[i]]->getYOffset();
        if (text[i] != 32) RENDER.DrawImage(letters[text[i]]->getcharTTF(), x + offsetX, y + offsetY);
        anchoCaracter = eX - oX;
        offsetX += anchoCaracter;
      }
    }else{
      double offsetX = 0.0;
      uint32 anchoCaracter;
      for (int32 i = 0; i < text.Length(); i++){
        uint16 eX = letters[text[i]]->getEndX();
        uint16 oY = letters[text[i]]->getOriginY();
        RENDER.DrawImage(this, x + offsetX, y + oY, CHARTOUI32(text[i]));
        anchoCaracter = this->GetWidth() - (this->GetWidth() - eX);
        offsetX += anchoCaracter;
      }
    }
  }
}

Font::~Font()
{
  for ( uint32 i = 0; i < letters.Size(); i++ )
    delete letters[i];
  letters.Clear();
}