#pragma once

#include "Particle.h"

class IParticleEmitter
{
public:
    virtual ~IParticleEmitter() {}
    virtual void ResetParticle(Particle *resetThis) const = 0;
};

