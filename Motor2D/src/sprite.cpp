#include "../include/sprite.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"


Sprite::Sprite(Image* image) {
    this->image = image;
    x = 0;
    y = 0;
    screenX = screenY = 0;
    angle = 0;
    scalex = 1;
    scaley = 1;
    blendMode = Renderer::BlendMode::ALPHA;
    r = 255;
    g = 255;
    b = 255;
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

    animFPS = 0;
    firstFrame = 0;
    lastFrame = 0;
    currentFrame = 0.0;

    collision = NULL;
    collided = false;
    colx = coly = colwidth = colheight = radius = 0.0;
    colPixelData = NULL;
    colSprite = NULL;
}

Sprite::~Sprite() {
  if (collision) delete collision;
}


void Sprite::SetCollision(CollisionMode mode) {
  if (collision) delete collision;

  switch (mode)
  {
  case Sprite::COLLISION_NONE:
     collision = NULL;
    break;
  case Sprite::COLLISION_CIRCLE:
    collision = new CircleCollision(&x,&y, &radius);
    break;
  case Sprite::COLLISION_PIXEL:
    collision = new PixelCollision(colPixelData,&colx,&coly);
    break;
  case Sprite::COLLISION_RECT:
    collision = new RectCollision(&colx, &coly, &colwidth, &colheight);
    break;
  default:
    break;
  }
}

bool Sprite::CheckCollision(Sprite* sprite) {
  if (collision && sprite->GetCollision())
  {
    if (collision->DoesCollide(sprite->GetCollision()))
    {
      colSprite = sprite;
      collided = true;
      sprite->SetCollisionSprite(this);
      sprite->SetCollide(true);
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

bool Sprite::CheckCollision(const Map* map) {
  if (map){
    if (collision)
    {
      collided = map->CheckCollision(collision);
      return collided;
    }
  }
  return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
  
  if(abs(this->angle - angle) <= 0.00001)
  {
    rotating = false;
    rotatingSpeed = 0;
  }else
  {
    rotating = true;
    toAngle = static_cast<uint16>(WrapValue(angle,360));
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

	//Actualizar animacion
  if (animFPS != 0){
    currentFrame += animFPS * elapsed;
    if (currentFrame <= firstFrame) currentFrame = DOUBLE(lastFrame) + 0.9999 ; //Le damos tiempo a la ultima
    if (currentFrame >= (lastFrame + 1)) currentFrame = DOUBLE(firstFrame);
  }
	//Actualizar rotacion animada
  if (rotating){
    this->angle = WrapValue(this->angle + rotatingSpeed * elapsed, 360);
    anglesToRotate -= abs(rotatingSpeed * elapsed);
    if (anglesToRotate <= 0)
    {
      this->angle = toAngle;
      rotating = false;
    }
  }
  //Actualizar movimiento
  if (moving)
  {
    double auxX = this->x;
    double auxY = this->y;
    this->x += movingSpeedX * elapsed;
    bool abortarX = false;
    bool abortarY = false;

    UpdateCollisionBox();
    abortarX = CheckCollision(map);
    if (abortarX)
      this->x = auxX;

    this->y += movingSpeedY * elapsed;
    UpdateCollisionBox();
    abortarY = CheckCollision(map);
    if (abortarY)
      this->y = auxY;
    if (abortarX && abortarY) moving = false;

    if (!abortarX){
      prevX -= movingSpeedX * elapsed;
      if (prevX <= 0.00001)
      {
        this->x = toX;
        moving = false;
      }
    }
    if (!abortarY){
      prevY -= movingSpeedY * elapsed;
      if (prevY <= 0.00001)
      {
        this->y = toY;
        moving = false;
      }
    }
  }

  screenX = this->x;
  screenY = this->y;
	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
  RENDER.SetBlendMode(blendMode);
  RENDER.SetColor(r, g, b, a);
  RENDER.DrawImage(image, screenX, screenY, static_cast<uint32>(currentFrame), image->GetWidth() * scalex, image->GetHeight() * scaley, angle);
}

void Sprite::UpdateCollisionBox() {
  double cx, cy, cw, ch;
  cx = x - image->GetHandleX() * fabs(scalex);
  cy = y - image->GetHandleY() * fabs(scaley);
  cw = image->GetWidth() * fabs(scalex);
  ch = image->GetHeight() * fabs(scaley);
  UpdateCollisionBox(cx, cy, cw, ch);

}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
  colx = x;
  coly = y;
  colwidth = w;
  colheight = h;
}
