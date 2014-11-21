#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image) {
    this->image = image;
    x = 0;
    y = 0;
    angle = 0;
    scalex = 1;
    scaley = 1;
    blendMode = Renderer::BlendMode::ALPHA;
    r = 0;
    g = 0;
    b = 0;
    a = 255;
    userData = NULL;
    currentFrame = 0.0;
}

Sprite::~Sprite() {
  if(userData != NULL){
    delete userData;
    userData = NULL;
  }
}

/*
void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
}
*/

void Sprite::RotateTo(int32 angle, double speed) {
	// TAREA: Implementar
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	// TAREA: Actualizar rotacion animada

	// TAREA: Actualizar movimiento animado

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
  Renderer::Instance().SetBlendMode(blendMode);
  Renderer::Instance().SetColor(r,g,b,a);
  Renderer::Instance().DrawImage(image,x,y,static_cast<uint32>(currentFrame),image->GetWidth() * scalex,image->GetHeight() * scaley,angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
