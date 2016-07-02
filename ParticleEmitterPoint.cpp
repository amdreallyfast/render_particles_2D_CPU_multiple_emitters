#include "ParticleEmitterPoint.h"

#include "RandomToast.h"

// TODO: header
ParticleEmitterPoint::ParticleEmitterPoint(const glm::vec2 &emitterPos, const float minVel, 
    const float maxVel)
{
    _position = emitterPos;
    _velocityCalculator.SetMinMaxVelocity(minVel, maxVel);
    _velocityCalculator.UseRandomDir();
}

// TODO: header
void ParticleEmitterPoint::ResetParticle(Particle *resetThis) const
{
    //??when to turn it on??
    //resetThis->_isActive = true;

    // give it some flavor by making the particles be reset to within a range near the emitter's 
    // position, making it look like a particle hotspot
    // TODO: the random thing
    resetThis->_position = _position;


    resetThis->_velocity = _velocityCalculator.GetNew();
}
