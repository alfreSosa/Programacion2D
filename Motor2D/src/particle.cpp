#include "../include/particle.h"
#include "../include/image.h"
#include "../include/affector.h"

Particle::Particle(): Sprite(NULL){
  velocityx = velocityy = angularVelocity = lifetime = initialLifetime = 0;
  autofade = false;
  afected = false;
  initialAplha = 0;
}

Particle::Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade) : Sprite(image){
  velocityx = velx;
  velocityy = vely;
  angularVelocity = angularVel;
  initialLifetime = lifetime;
  this->lifetime = lifetime;
  this->autofade = autofade;
  afected = false;
  initialAplha = this->GetAlpha();
}
void Particle::Update(double elapsed)
{
  lifetime -= elapsed;
  double nPosX = this->GetX() + velocityx * elapsed;
  double nPosY = this->GetY() + velocityy * elapsed;
  double nAngle = this->GetAngle() + angularVelocity * elapsed;
  this->SetPosition(nPosX, nPosY);
  this->SetAngle(nAngle);
  if (autofade)
    this->SetColor(this->GetRed(), this->GetAlpha(), this->GetBlue(), static_cast<uint8>(initialAplha * (lifetime / initialLifetime)));
}