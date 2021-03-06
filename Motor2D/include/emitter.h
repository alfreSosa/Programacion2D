#ifndef _EMITTER_H
#define _EMITTER_H

#include "types.h"
#include "renderer.h"
#include "particle.h"

class Image;
class Particle;
class Affector;

class Emitter {
public:
  Emitter(Image* image, bool autofade);
  virtual void SetPosition(double x, double y) { this->x = x; this->y = y; }
  virtual void SetX(double x) { this->x = x; }
  virtual void SetY(double y) { this->y = y; }
  virtual double GetX() const { return x; }
  virtual double GetY() const { return y; }
  virtual void SetRate(double minrate, double maxrate);
  virtual void SetVelocityX(double minvelx, double maxvelx);
  virtual void SetVelocityY(double minvely, double maxvely);
  virtual void SetAngularVelocity(double minangvel, double maxangvel);
  virtual void SetLifetime(double minlifetime, double maxlifetime);
  virtual void SetMinColor(uint8 r, uint8 g, uint8 b);
  virtual void SetMaxColor(uint8 r, uint8 g, uint8 b);
  virtual void SetBlendMode(Renderer::BlendMode mode) { blendMode = mode; }
  virtual void Start() { emitting = true; }
  virtual void Stop() { emitting = false; }
  virtual bool IsEmitting() const { return emitting; }
  virtual void Update(double elapsed);
  virtual void Render() const;
  virtual void addAffector(Affector *afectador);
private:
  Image* image;
  bool autofade;
  double x, y;
  double minrate, maxrate;
  double minvelx, maxvelx;
  double minvely, maxvely;
  double minangvel, maxangvel;
  double minlifetime, maxlifetime;
  uint8 minr, ming, minb;
  uint8 maxr, maxg, maxb;
  Renderer::BlendMode blendMode;
  bool emitting;
  Array<Particle *> particles;
  Array<Affector *> afectores;
};
#endif