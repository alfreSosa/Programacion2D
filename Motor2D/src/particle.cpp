#include "../include/particle.h"
#include "../include/image.h"

Particle::Particle(): Sprite(NULL){
  velocityx = velocityy = angularVelocity = lifetime = initialLifetime = 0;
  autofade = false;
}

Particle::Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade) : Sprite(image){
  velocityx = velx;
  velocityy = vely;
  angularVelocity = angularVel;
  initialLifetime = lifetime;
  this->lifetime = lifetime;
  this->autofade = autofade;
}
void Particle::Update(double elapsed)
{
  //xejemplo
  lifetime -= elapsed;
}