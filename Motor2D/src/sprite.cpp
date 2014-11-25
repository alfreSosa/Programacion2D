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
    rotating = false;
    rotatingSpeed = 0.0;
    anglesToRotate = 0.0;
    moving = false;
    toX = 0.0;
    toY = 0.0;
    movingSpeedX = 0.0;
    movingSpeedY = 0.0;
    prevX = 0.0;
    prevY = 0.0;
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
  
  if(abs(this->angle - angle) <= 0.00001)
  {
    rotating = false;
    rotatingSpeed = 0;
  }else
  {
    rotating = true;
    toAngle = WrapValue(angle,360);
    anglesToRotate = WrapValue(angle - this->angle,360);

    if (WrapValue(angle - this->angle,360) <= WrapValue(this->angle - angle,360))
      rotatingSpeed = abs(speed);
    else 
      rotatingSpeed = -abs(speed);
    
  }
  
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {


  if ((abs(this->x - x) <= 0.00001) && (abs(this->y - y) <= 0.00001)){
    moving = false;
  }else
  { 
    moving = true;
    toX = x;
    toY = y;

    prevX = abs(x - this->x);
    prevY = abs(y - this->y);

    if(this->x > x) movingSpeedX = -speedX;
    else movingSpeedX = speedX;
 
    if(this->y > y) movingSpeedY = -speedY;
    else movingSpeedY = speedY;
  }
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	// TAREA: Actualizar rotacion animada
  if (rotating){
    this->angle = WrapValue(this->angle + rotatingSpeed * elapsed, 360);
    anglesToRotate -= abs(rotatingSpeed * elapsed);
    if(anglesToRotate <= 0)
      this->angle = toAngle;
  }
	// TAREA: Actualizar movimiento animado
  if (moving)
  {
    //if(abs(prevX) <= 0.00001)
    this->x += movingSpeedX * elapsed;
    //if(abs(prevY) <= 0.00001)
    this->y += movingSpeedY * elapsed;

    prevX -= movingSpeedX * elapsed;
    if (prevX <= 0.00001)
      this->x = toX;

    prevY -= movingSpeedY * elapsed;
    if (prevY <= 0.00001) 
      this->y = toY;
  }
	// Informacion final de colision
	//UpdateCollisionBox();
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
