#pragma once

#include "IParticleRegion.h"
#include "glm/vec2.hpp"
#include "Particle.h"
#include <vector>

// TODO: header
// contains boundaries and the logic to determine when a particle goes outside of spherical boundaries
class ParticleRegionSphere : IParticleRegion
{
public:
    ParticleRegionSphere();
    void Init(const glm::vec2 &center, const float radius);

    virtual bool OutOfBounds(const Particle &p) const;
    virtual void DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection) const;

private:
    glm::vec2 _center;
    float _radiusSqr;   // because radius is never used
};
