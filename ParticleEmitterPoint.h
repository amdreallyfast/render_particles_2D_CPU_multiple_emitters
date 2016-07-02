#pragma once

#include "IParticleEmitter.h"
#include "Particle.h"
#include "MinMaxVelocity.h"
#include "glm/vec2.hpp"

// TODO: header
// knows how to reset particles that it is given
class ParticleEmitterPoint : IParticleEmitter
{
public:
    // emits randomly from the origin point
    ParticleEmitterPoint(const glm::vec2 &emitterPos, const float minVel, const float maxVel);
    void ResetParticle(Particle *resetThis) const;
private:
    glm::vec2 _position;
    float _radius;
    MinMaxVelocity _velocityCalculator;
};
