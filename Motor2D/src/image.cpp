#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

#include "../include/renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"


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
        for (int i = 0; i < height; i++)
          for (int j = 0; j < width; j++)
          {
            //pixel 4 bytes
            newBuffer[(i*escalaX + j) * 4] = buffer[(i*width + j) * 4];
            newBuffer[(i*escalaX + j) * 4 + 1] = buffer[(i*width + j) * 4 + 1];
            newBuffer[(i*escalaX + j) * 4 + 2] = buffer[(i*width + j) * 4 + 2];
            newBuffer[(i*escalaX + j) * 4 + 3] = buffer[(i*width + j) * 4 + 3];
          }
        lastU = float(width) / escalaX;
        lastV = float(height) / escalaY;
        width = escalaX;
        height = escalaY;
        gltex = Renderer::Instance().GenImage(newBuffer, width, height);
        free(newBuffer);
      }
    }
    else
    {
      gltex = Renderer::Instance().GenImage(buffer, width, height);
    }
	}
  stbi_image_free(buffer);
}

Image::~Image() {
  Renderer::Instance().DeleteImage(gltex);
}

void Image::Bind() const {
  Renderer::Instance().BindImage(gltex);
}
