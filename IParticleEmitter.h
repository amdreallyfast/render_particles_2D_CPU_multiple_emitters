#pragma once

#include "Particle.h"
#include "glm/mat4x4.hpp"

/*-----------------------------------------------------------------------------------------------
Description:
    The "particle updater" must be able to easily use multiple particle emitters without much 
    trouble, so use an interface that defines the basic functionality of each particle emitter.
Creator:    John Cox (7-2-2016)
-----------------------------------------------------------------------------------------------*/
class IParticleEmitter
{
public:
    virtual ~IParticleEmitter() {}
    virtual void ResetParticle(Particle *resetThis) const = 0;
    virtual void SetTransform(const glm::mat4 &m) = 0;
};

