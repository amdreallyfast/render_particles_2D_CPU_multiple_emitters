#pragma once

#include "IParticleEmitter.h"
#include "Particle.h"
#include "MinMaxVelocity.h"
#include "glm/vec2.hpp"

// TODO: header
// knows how to reset particles that it is given
class ParticleEmitterBar : public IParticleEmitter
{
public:
    // emits +90 degrees from the p1->p2 vector
    ParticleEmitterBar(const glm::vec2 &p1, const glm::vec2 &p2, const float minVel,
        const float maxVel);
    virtual void ResetParticle(Particle *resetThis) const;
private:
    // why store the start and the end when what I need is the start + the start-end vector?
    glm::vec2 _barStart;
    glm::vec2 _barStartToEnd;
    glm::vec2 _emitDirection;
    MinMaxVelocity _velocityCalculator;
};

