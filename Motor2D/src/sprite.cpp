#include "../include/sprite.h"
#include "../include/rectcollision.h"
#include "../include/image.h"
#include "../include/map.h"
#include "../include/math.h"
#include "../include/pixelcollision.h"
#include "../include/renderer.h"
#include "../include/circlecollision.h"


Sprite::Sprite(Image* image) {
    this->m_image = image;
    m_x = 0;
    m_y = 0;
    m_angle = 0;
    m_scalex = 1;
    m_scaley = 1;
    m_blendMode = Renderer::BlendMode::ALPHA;
    m_r = 255;
    m_g = 255;
    m_b = 255;
    m_a = 255;
    m_userData = NULL;
    m_currentFrame = 0.0;
    m_rotating = false;
    m_rotatingSpeed = 0.0;
    m_anglesToRotate = 0.0;
    m_moving = false;
    m_toX = 0.0;
    m_toY = 0.0;
    m_movingSpeedX = 0.0;
    m_movingSpeedY = 0.0;
    m_prevX = 0.0;
    m_prevY = 0.0;

    m_animFPS = 0;
    m_firstFrame = 0;
    m_lastFrame = 0;
    m_currentFrame = 0.0;

    m_collision = NULL;
    m_collided = false;
    m_colx = m_coly = m_colwidth = m_colheight = m_radius = 0.0;
    m_colPixelData = NULL;
    m_colSprite = NULL;
}

Sprite::~Sprite() {
  if (m_collision) delete m_collision;
}


void Sprite::SetCollision(CollisionMode mode) {
  if (m_collision) delete m_collision;

  switch (mode)
  {
  case Sprite::COLLISION_NONE:
     m_collision = NULL;
    break;
  case Sprite::COLLISION_CIRCLE:
    m_collision = new CircleCollision(&m_x,&m_y, &m_radius);
    break;
  case Sprite::COLLISION_PIXEL:
    m_collision = new PixelCollision(m_colPixelData,&m_colx,&m_coly);
    break;
  case Sprite::COLLISION_RECT:
    m_collision = new RectCollision(&m_colx, &m_coly, &m_colwidth, &m_colheight);
    break;
  default:
    break;
  }
}

bool Sprite::CheckCollision(Sprite* sprite) {
  if (m_collision && sprite->GetCollision())
  {
    if (m_collision->DoesCollide(sprite->GetCollision()))
    {
      m_colSprite = sprite;
      m_collided = true;
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
    if (m_collision)
    {
      m_collided = map->CheckCollision(m_collision);
      return m_collided;
    }
  }
  return false;
}

void Sprite::RotateTo(int32 angle, double speed) {
  
  if(abs(this->m_angle - angle) <= 0.00001)
  {
    m_rotating = false;
    m_rotatingSpeed = 0;
  }else
  {
    m_rotating = true;
    m_toAngle = static_cast<uint16>(WrapValue(angle,360));
    m_anglesToRotate = WrapValue(angle - this->m_angle,360);

    if (WrapValue(angle - this->m_angle,360) <= WrapValue(this->m_angle - angle,360))
      m_rotatingSpeed = abs(speed);
    else 
      m_rotatingSpeed = -abs(speed);
    
  }
  
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {


  if ((abs(this->m_x - x) <= 0.00001) && (abs(this->m_y - y) <= 0.00001)){
    m_moving = false;
  }else
  { 
    m_moving = true;
    m_toX = x;
    m_toY = y;

    m_prevX = abs(x - this->m_x);
    m_prevY = abs(y - this->m_y);

    if(this->m_x > x) m_movingSpeedX = -speedX;
    else m_movingSpeedX = speedX;
 
    if(this->m_y > y) m_movingSpeedY = -speedY;
    else m_movingSpeedY = speedY;
  }
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	m_colSprite = NULL;
	m_collided = false;

	//Actualizar animacion
  if (m_animFPS != 0){
    m_currentFrame += m_animFPS * elapsed;
    if (m_currentFrame <= m_firstFrame) m_currentFrame = DOUBLE(m_lastFrame) + 0.9999 ; //Le damos tiempo a la ultima
    if (m_currentFrame >= (m_lastFrame + 1)) m_currentFrame = DOUBLE(m_firstFrame);
  }
	//Actualizar rotacion animada
  if (m_rotating){
    this->m_angle = WrapValue(this->m_angle + m_rotatingSpeed * elapsed, 360);
    m_anglesToRotate -= abs(m_rotatingSpeed * elapsed);
    if (m_anglesToRotate <= 0)
    {
      this->m_angle = m_toAngle;
      m_rotating = false;
    }
  }
  //Actualizar movimiento
  if (m_moving)
  {
    double auxX = this->m_x;
    double auxY = this->m_y;
    this->m_x += m_movingSpeedX * elapsed;
    bool abortarX = false;
    bool abortarY = false;

    UpdateCollisionBox();
    abortarX = CheckCollision(map);
    if (abortarX)
      this->m_x = auxX;

    this->m_y += m_movingSpeedY * elapsed;
    UpdateCollisionBox();
    abortarY = CheckCollision(map);
    if (abortarY)
      this->m_y = auxY;
    if (abortarX && abortarY) m_moving = false;

    if (!abortarX){
      m_prevX -= m_movingSpeedX * elapsed;
      if (m_prevX <= 0.00001)
      {
        this->m_x = m_toX;
        m_moving = false;
      }
    }
    if (!abortarY){
      m_prevY -= m_movingSpeedY * elapsed;
      if (m_prevY <= 0.00001)
      {
        this->m_y = m_toY;
        m_moving = false;
      }
    }
  }
	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
  RENDER.SetBlendMode(m_blendMode);
  RENDER.SetColor(m_r, m_g, m_b, m_a);
  RENDER.DrawImage(m_image, GetScreenX(), GetScreenY(), static_cast<uint32>(m_currentFrame), m_image->GetWidth() * m_scalex, m_image->GetHeight() * m_scaley, m_angle);
}

void Sprite::UpdateCollisionBox() {
  double cx, cy, cw, ch;
  cx = m_x - m_image->GetHandleX() * fabs(m_scalex);
  cy = m_y - m_image->GetHandleY() * fabs(m_scaley);
  cw = m_image->GetWidth() * fabs(m_scalex);
  ch = m_image->GetHeight() * fabs(m_scaley);
  UpdateCollisionBox(cx, cy, cw, ch);

}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
  m_colx = x;
  m_coly = y;
  m_colwidth = w;
  m_colheight = h;
}
