#include "../include/emitter.h"
#include "../include/particle.h"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/affector.h"
#include <math.h>
Emitter::Emitter(Image *image, bool autofade)
{
  this->m_image = image;
  this->m_autofade = autofade;
  m_x = m_y = m_minrate = m_maxrate = m_minvelx = m_maxvelx = m_minvely = m_maxvely = m_minangvel = m_maxangvel = m_minlifetime, m_maxlifetime = 0.0;
  m_emitting = false;
  m_minr = m_ming = m_minb = m_maxr = m_maxg = m_maxb = 0;
  m_blendMode = Renderer::ADDITIVE;
}
void Emitter::SetRate(double minrate, double maxrate)
{
  this->m_minrate = (maxrate == minrate) ? 0 : abs(minrate);
  this->m_maxrate = abs(maxrate); 
}
void Emitter::SetVelocityX(double minvelx, double maxvelx)
{ 
  this->m_minvelx = (maxvelx == minvelx) ? 0 : minvelx; 
  this->m_maxvelx = maxvelx;
}
void Emitter::SetVelocityY(double minvely, double maxvely)
{
  this->m_minvely = (maxvely == minvely) ? 0 : minvely;
  this->m_maxvely = maxvely;
 }
void Emitter::SetAngularVelocity(double minangvel, double maxangvel) 
{ 
  this->m_minangvel = (maxangvel == minangvel) ? 0 : minangvel;
  this->m_maxangvel = maxangvel; 
}
void Emitter::SetLifetime(double minlifetime, double maxlifetime)
{ 
  this->m_minlifetime = (maxlifetime == minlifetime) ? 0 : minlifetime; 
  this->m_maxlifetime = maxlifetime;
}

void Emitter::SetMinColor(uint8 r, uint8 g, uint8 b)
{
  m_minr = r; m_ming = g; m_minb = b;
}
void Emitter::SetMaxColor(uint8 r, uint8 g, uint8 b)
{
  m_maxr = r; m_maxg = g; m_maxb = b;
}
void Emitter::Update(double elapsed)
{
  if (m_emitting)
  {
    double rate = (m_minrate == 0 && m_maxrate == 0) ? 0 : (WrapValue(rand(), m_maxrate - m_minrate) + m_minrate) * elapsed;
    for (int n = 0; n < INT(rate); n++){
      double velPx = (m_minvelx == 0 && m_maxvelx == 0) ? 0: WrapValue(rand(), m_maxvelx - m_minvelx) + m_minvelx;
      double velPy = (m_minvely == 0 && m_maxvely == 0) ? 0 : WrapValue(rand(), m_maxvelx - m_minvelx) + m_minvely;
      double velPangle = (m_minangvel == 0 && m_maxangvel == 0) ? 0 : WrapValue(rand(), m_maxangvel - m_minangvel) + m_minangvel;
      double timeP = (m_minlifetime == 0 && m_maxlifetime == 0) ? 0 : WrapValue(rand(), m_maxlifetime - m_minlifetime) + m_minlifetime;
      Particle *nueva = new Particle(m_image, velPx, velPy, velPangle, timeP, m_autofade);

      uint8 rP;
      if (m_maxr == 0 && m_minr == 0) rP = 0;
      else rP = (m_maxr == m_minr) ? m_maxr : rand() % (m_maxr - m_minr) + m_minr;

      uint8 gP;
      if (m_maxg == 0 && m_ming == 0) gP = 0;
      else gP = (m_maxg == m_ming) ? m_maxg : rand() % (m_maxg - m_ming) + m_ming;

      uint8 bP;
      if (m_maxb == 0 && m_minb == 0) bP = 0;
      else bP = (m_maxb == m_minb) ? m_maxb : rand() % (m_maxb - m_minb) + m_minb;
      
      nueva->SetColor(rP, gP, bP);
      nueva->SetBlendMode(m_blendMode);
      nueva->SetPosition(this->GetX(), this->GetY());
      m_particles.Add(nueva);
    }
  }
  for (uint32 i = 0; i < m_afectores.Size(); i++)
    for (uint32 j = 0; j < m_particles.Size(); j++)
      if (!m_particles[j]->isAfected())
        m_afectores[i]->Afectar(m_particles[j]);

  for (uint32 i = 0; i < m_particles.Size(); i++)
  {
    m_particles[i]->Update(elapsed);
    if (m_particles[i]->GetLifetime() <= 0){
      delete m_particles[i];
      m_particles.RemoveAt(i--);
    }
  }
}
void Emitter::Render() const
{
  for (uint32 i = 0; i < m_particles.Size(); i++)
    m_particles[i]->Render();
}

void Emitter::addAffector(Affector *afectador)
{
  m_afectores.Add(afectador); 
}