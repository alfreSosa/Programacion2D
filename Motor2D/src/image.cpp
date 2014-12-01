#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

#include "../include/renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

Image::Image(uint8 *buffer,uint16 width, uint16 height, uint16 hframes, uint16 vframes)
{
  //this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
  this->width = width;
  this->height = height;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;
	// Generamos la textura
	if ( buffer ) {
      gltex = RENDER.GenImage(buffer, width, height);
  }
}
Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	// TAREA: Cargar el buffer de la imagen
  int x,y;
  uint8 *buffer = stbi_load(filename.ToCString(), &x, &y, NULL, 4);
  width = static_cast<uint16>(x);
  height = static_cast<uint16>(y);
	// Generamos la textura
	if ( buffer ) {
    uint16 escalaX = static_cast<uint16>(pow(2, ceil(Log2(width))));
    uint16 escalaY = static_cast<uint16>(pow(2, ceil(Log2(height))));
    if (width != escalaX || height != escalaY)
    {
      uint8 *newBuffer = (uint8 *)calloc(escalaX * escalaY * 4, sizeof(uint8));
      if (newBuffer)
      {
        int tamPixelNuevo = escalaX * 4;
        int tamPixel = width * 4;

        for (int i = 0; i < height; i++)
          memcpy(&newBuffer[i *tamPixelNuevo], &buffer[i * tamPixel],tamPixel);

        lastU = float(width) / escalaX;
        lastV = float(height) / escalaY;
        gltex = RENDER.GenImage(newBuffer, escalaX, escalaY);
        free(newBuffer);
      }
    }
    else
    {
      gltex = RENDER.GenImage(buffer, width, height);
    }
	}
  stbi_image_free(buffer);
}

Image::~Image() {
  RENDER.DeleteImage(gltex);
}

void Image::Bind() const {
  RENDER.BindImage(gltex);
}
