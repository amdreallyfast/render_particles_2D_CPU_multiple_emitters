#pragma once

#include "glm/vec2.hpp"
#include "Particle.h"
#include <vector>

// TODO: header
class IParticleRegion
{
public:
    virtual ~IParticleRegion() {}

    // these methods set a particle's "is active" flag to false if it goes out of bounds

    virtual bool OutOfBounds(const Particle &p) const = 0;
    virtual void DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection) const = 0;
};

