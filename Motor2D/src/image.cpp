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
	this->m_hframes = hframes;
	this->m_vframes = vframes;
  this->m_width = width;
  this->m_height = height;
	m_handlex = 0;
	m_handley = 0;
	m_gltex = 0;
	m_lastU = 1.0;
	m_lastV = 1.0;
	// Generamos la textura
	if ( buffer ) {
      m_gltex = RENDER.GenImage(buffer, width, height);
  }
}
Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->m_filename = filename;
	this->m_hframes = hframes;
	this->m_vframes = vframes;
	m_width = 0;
	m_height = 0;
	m_handlex = 0;
	m_handley = 0;
	m_gltex = 0;
	m_lastU = 1.0;
	m_lastV = 1.0;

	// TAREA: Cargar el buffer de la imagen
  int x,y;
  uint8 *buffer = stbi_load(filename.ToCString(), &x, &y, NULL, 4);
  m_width = static_cast<uint16>(x);
  m_height = static_cast<uint16>(y);
	// Generamos la textura
	if ( buffer ) {
    uint16 escalaX = static_cast<uint16>(pow(2, ceil(Log2(m_width))));
    uint16 escalaY = static_cast<uint16>(pow(2, ceil(Log2(m_height))));
    if (m_width != escalaX || m_height != escalaY)
    {
      uint8 *newBuffer = (uint8 *)calloc(escalaX * escalaY * 4, sizeof(uint8));
      if (newBuffer)
      {
        int tamPixelNuevo = escalaX * 4;
        int tamPixel = m_width * 4;

        for (int i = 0; i < m_height; i++)
          memcpy(&newBuffer[i *tamPixelNuevo], &buffer[i * tamPixel],tamPixel);

        m_lastU = float(m_width) / escalaX;
        m_lastV = float(m_height) / escalaY;
        m_gltex = RENDER.GenImage(newBuffer, escalaX, escalaY);
        free(newBuffer);
      }
    }
    else
    {
      m_gltex = RENDER.GenImage(buffer, m_width, m_height);
    }
	}
  stbi_image_free(buffer);
}

Image::~Image() {
  RENDER.DeleteImage(m_gltex);
}

void Image::Bind() const {
  RENDER.BindImage(m_gltex);
}
