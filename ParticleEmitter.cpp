#include "ParticleEmitter.h"
#include "RandomToast.h"

ParticleEmitterPoint::ParticleEmitterPoint(const glm::vec2 &emitterPos, const float radius, 
    const float minVel, const float maxVel)
{
    _position = emitterPos;
    _velocityCalculator.SetMinMaxVelocity(minVel, maxVel);
    _velocityCalculator.UseRandomDir();
}

void ParticleEmitterPoint::ResetParticle(Particle *resetThis)
{
    resetThis->_isActive = true;
    resetThis->_position = _position;
    resetThis->_velocity = _velocityCalculator.GetNew();
}

ParticleEmitterBar::ParticleEmitterBar(const glm::vec2 &p1, const glm::vec2 &p2, 
    const float minVel, const float maxVel)
{
    _barStart = p1;
    _barStartToEnd = p2 - p1;

    // rotate a 2D vector (x,y) by +90 degrees => (-y,x)
    glm::vec2 plus90Degrees((-1.0f) * _barStartToEnd.y, _barStartToEnd.x);

    _velocityCalculator.SetMinMaxVelocity(minVel, maxVel);
    _velocityCalculator.SetDir(plus90Degrees);
}

void ParticleEmitterBar::ResetParticle(Particle *resetThis)
{
    resetThis->_isActive = true;
    resetThis->_position = _barStart + (RandomOnRange0to1() * _barStartToEnd);
    resetThis->_velocity = _velocityCalculator.GetNew();
}

