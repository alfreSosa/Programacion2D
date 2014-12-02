#include "../include/emitter.h"
#include "../include/particle.h"
#include "../include/image.h"

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
  if (IsEmitting)
  {
    //generar particulas
    //cast en rand?
    int velPx = rand() % INT(maxvelx - minvelx) + minvelx;
    int velPy = rand() % INT(maxvely - minvely) + minvely;
    int velPangle = rand() % INT(maxangvel - minangvel) + minangvel;
    int timeP = rand() % INT(maxlifetime - minlifetime) + minlifetime;
    if (autofade) 
    {
      uint8 rP = rand() % (maxr - minr) + minr;
      uint8 gP = rand() % (maxg - ming) + ming;
      uint8 bP = rand() % (maxb - minb) + minb;
    }
  }
}
void Emitter::Render() const
{

}