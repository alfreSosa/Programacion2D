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
  virtual void SetPosition(double x, double y) { this->m_x = x; this->m_y = y; }
  virtual void SetX(double x) { this->m_x = x; }
  virtual void SetY(double y) { this->m_y = y; }
  virtual double GetX() const { return m_x; }
  virtual double GetY() const { return m_y; }
  virtual void SetRate(double minrate, double maxrate);
  virtual void SetVelocityX(double minvelx, double maxvelx);
  virtual void SetVelocityY(double minvely, double maxvely);
  virtual void SetAngularVelocity(double minangvel, double maxangvel);
  virtual void SetLifetime(double minlifetime, double maxlifetime);
  virtual void SetMinColor(uint8 r, uint8 g, uint8 b);
  virtual void SetMaxColor(uint8 r, uint8 g, uint8 b);
  virtual void SetBlendMode(Renderer::BlendMode mode) { m_blendMode = mode; }
  virtual void Start() { m_emitting = true; }
  virtual void Stop() { m_emitting = false; }
  virtual bool IsEmitting() const { return m_emitting; }
  virtual void Update(double elapsed);
  virtual void Render() const;
  virtual void addAffector(Affector *afectador);
private:
  Image* m_image;
  bool m_autofade;
  double m_x, m_y;
  double m_minrate, m_maxrate;
  double m_minvelx, m_maxvelx;
  double m_minvely, m_maxvely;
  double m_minangvel, m_maxangvel;
  double m_minlifetime, m_maxlifetime;
  uint8 m_minr, m_ming, m_minb;
  uint8 m_maxr, m_maxg, m_maxb;
  Renderer::BlendMode m_blendMode;
  bool m_emitting;
  Array<Particle *> m_particles;
  Array<Affector *> m_afectores;
};
#endif