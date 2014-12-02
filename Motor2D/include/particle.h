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
  virtual double GetLifetime() const { return lifetime; };
  virtual void Update(double elapsed);
private:
  double velocityx, velocityy;
  double angularVelocity;
  double lifetime;
  double initialLifetime;
  bool autofade;
};

#endif