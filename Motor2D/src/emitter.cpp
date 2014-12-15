#include "../include/emitter.h"
#include "../include/particle.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/affector.h"
#include <math.h>
Emitter::Emitter(Image *image, bool autofade)
{
  this->image = image;
  this->autofade = autofade;
  x = y = minrate = maxrate = minvelx = maxvelx = minvely = maxvely = minangvel = maxangvel = minlifetime, maxlifetime = 0.0;
  emitting = false;
  minr = ming = minb = maxr = maxg = maxb = 0;
  blendMode = Renderer::ADDITIVE;
}
void Emitter::SetRate(double minrate, double maxrate)
{
  this->minrate = (maxrate == minrate) ? 0 : abs(minrate);
  this->maxrate = abs(maxrate); 
}
void Emitter::SetVelocityX(double minvelx, double maxvelx)
{ 
  this->minvelx = (maxvelx == minvelx) ? 0 : minvelx; 
  this->maxvelx = maxvelx;
}
void Emitter::SetVelocityY(double minvely, double maxvely)
{
  this->minvely = (maxvely == minvely) ? 0 : minvely;
  this->maxvely = maxvely;
 }
void Emitter::SetAngularVelocity(double minangvel, double maxangvel) 
{ 
  this->minangvel = (maxangvel == minangvel) ? 0 : minangvel;
  this->maxangvel = maxangvel; 
}
void Emitter::SetLifetime(double minlifetime, double maxlifetime)
{ 
  this->minlifetime = (maxlifetime == minlifetime) ? 0 : minlifetime; 
  this->maxlifetime = maxlifetime;
}

void Emitter::SetMinColor(uint8 r, uint8 g, uint8 b)
{
  minr = r; ming = g; minb = b;
}
void Emitter::SetMaxColor(uint8 r, uint8 g, uint8 b)
{
  maxr = r; maxg = g; maxb = b;
}
void Emitter::Update(double elapsed)
{
  if (emitting)
  {
    double rate = (minrate == 0 && maxrate == 0) ? 0 : (WrapValue(rand(), maxrate - minrate) + minrate) * elapsed;
    for (int n = 0; n < INT(rate); n++){
      double velPx = (minvelx == 0 && maxvelx == 0) ? 0: WrapValue(rand(), maxvelx - minvelx) + minvelx;
      double velPy = (minvely == 0 && maxvely == 0) ? 0 : WrapValue(rand(), maxvelx - minvelx) + minvely;
      double velPangle = (minangvel == 0 && maxangvel == 0) ? 0 : WrapValue(rand(), maxangvel - minangvel) + minangvel;
      double timeP = (minlifetime == 0 && maxlifetime == 0) ? 0 : WrapValue(rand(), maxlifetime - minlifetime) + minlifetime;
      Particle *nueva = new Particle(image, velPx, velPy, velPangle, timeP, autofade);

      uint8 rP;
      if (maxr == 0 && minr == 0) rP = 0;
      else rP = (maxr == minr) ? maxr : rand() % (maxr - minr) + minr;

      uint8 gP;
      if (maxg == 0 && ming == 0) gP = 0;
      else gP = (maxg == ming) ? maxg : rand() % (maxg - ming) + ming;

      uint8 bP;
      if (maxb == 0 && minb == 0) bP = 0;
      else bP = (maxb == minb) ? maxb : rand() % (maxb - minb) + minb;
      
      nueva->SetColor(rP, gP, bP);
      nueva->SetBlendMode(blendMode);
      nueva->SetPosition(this->GetX(), this->GetY());
      particles.Add(nueva);
    }
  }
  for (uint32 i = 0; i < afectores.Size(); i++)
    for (uint32 j = 0; j < particles.Size(); j++)
      if (!particles[j]->isAfected())
        afectores[i]->Afectar(particles[j]);

  for (uint32 i = 0; i < particles.Size(); i++)
  {
    particles[i]->Update(elapsed);
    if (particles[i]->GetLifetime() <= 0){
      delete particles[i];
      particles.RemoveAt(i--);
    }
  }
}
void Emitter::Render() const
{
  for (uint32 i = 0; i < particles.Size(); i++)
    particles[i]->Render();
}

void Emitter::addAffector(Affector *afectador)
{
  afectores.Add(afectador); 
}