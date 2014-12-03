#include "../include/emitter.h"
#include "../include/particle.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/affector.h"
Emitter::Emitter(Image *image, bool autofade)
{
  this->image = image;
  this->autofade = autofade;
  x = y = minrate = maxrate = minvelx = maxvelx = minvely = maxvely = minangvel = maxangvel = minlifetime, maxlifetime = 0.0;
  emitting = false;
  minr = ming = minb = maxr = maxg = maxb = 0;
  blendMode = Renderer::ADDITIVE;
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
    double rate = (WrapValue(rand(), maxrate - minrate) + minrate) * elapsed;
    for (int n = 0; n < INT(rate); n++){
      double velPx = WrapValue(rand(), maxvelx - minvelx) + minvelx;
      double velPy = WrapValue(rand(), maxvelx - minvelx) + minvely;
      double velPangle = WrapValue(rand(), maxangvel - minangvel) + minangvel;
      double timeP = WrapValue(rand(), maxlifetime - minlifetime) + minlifetime;
      Particle nueva(image, velPx, velPy, velPangle, timeP, autofade);
      uint8 rP = rand() % (maxr - minr) + minr;
      uint8 gP = rand() % (maxg - ming) + ming;
      uint8 bP = rand() % (maxb - minb) + minb;
      nueva.SetColor(rP, gP, bP);
      nueva.SetBlendMode(blendMode);
      nueva.SetPosition(this->GetX(), this->GetY());
      particles.Add(nueva);
    }
  }
  //aqui en el update hacer lo de afector
  for (uint32 i = 0; i < particles.Size(); i++)
  {
    particles[i].Update(elapsed);
    if (particles[i].GetLifetime() <= 0)
      particles.RemoveAt(i--);
  }
}
void Emitter::Render() const
{
  for (uint32 i = 0; i < particles.Size(); i++)
    particles[i].Render();
}

void Emitter::addAffector(Affector afectador)
{
  afectores.Add(afectador); 
}