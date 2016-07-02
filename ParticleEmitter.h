#pragma once

#include "glm/vec2.hpp"
#include "Particle.h"
#include "MinMaxVelocity.h"

// each particle emitter will know how to reset particles that it is given

class ParticleEmitterPoint
{
public:
    // emits randomly from the origin point
    ParticleEmitterPoint(const glm::vec2 &emitterPos, const float radius, const float minVel, 
        const float maxVel);
    void ResetParticle(Particle *resetThis);
private:
    glm::vec2 _position;
    float _radius;
    MinMaxVelocity _velocityCalculator;
};

class ParticleEmitterBar
{
public:
    // emits +90 degrees from the p1->p2 vector
    ParticleEmitterBar(const glm::vec2 &p1, const glm::vec2 &p2, const float minVel,
        const float maxVel);
    void ResetParticle(Particle *resetThis);
private:
    // why store the start and the end when what I need is the start + the start-end vector?
    glm::vec2 _barStart;
    glm::vec2 _barStartToEnd;
    glm::vec2 _emitDirection;
    MinMaxVelocity _velocityCalculator;
};
