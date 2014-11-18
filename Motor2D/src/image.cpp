#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include <math.h>
#include <stdlib.h>


Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = 0;
	this->vframes = 0;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	// TAREA: Cargar el buffer de la imagen

	// Generamos la textura
//	if ( buffer ) {
		// TAREA: Generar la textura de OpenGL
	//}
}

Image::~Image() {
	// TAREA: Eliminar la imagen de la memoria de OpenGL
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
}
