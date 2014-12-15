#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "types.h"
#include "sprite.h"

class Image;

class Particle : public Sprite
{
public:
  Particle();
  Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade);
  virtual ~Particle(){ }
  virtual double GetLifetime() const { return lifetime; }
  virtual void Update(double elapsed);
  virtual void setVelocityX(double vel) { velocityx = vel; }
  virtual void setVelocityY(double vel) { velocityy = vel; }
  virtual void setVelocityAng(double vel) { angularVelocity = vel; }
  virtual void Alter() { afected = true; }
  virtual bool isAfected() const { return afected; }
private:
  double velocityx, velocityy;
  double angularVelocity;
  double lifetime;
  double initialLifetime;
  uint8 initialAplha;
  bool autofade;
  bool afected;
};

#endif