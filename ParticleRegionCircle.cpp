#include "ParticleRegionCircle.h"

#include "glm/detail/func_geometric.hpp"    // glm::dot

// TODO: header
ParticleRegionCircle::ParticleRegionCircle(const glm::vec2 &center, const float radius)
{
    _center = center;
    _radiusSqr = radius * radius;
}

// TODO: header
bool ParticleRegionCircle::OutOfBounds(const Particle &p) const
{
    glm::vec2 centerToParticle = p._position - _center;
    float distSqr = glm::dot(centerToParticle, centerToParticle);
    if (distSqr > _radiusSqr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// TODO: header
void ParticleRegionCircle::DeactivateIfOutOfBounds(
    std::vector<Particle> &particleCollection) const
{
    for (size_t particleIndex = 0; particleIndex < particleCollection.size(); particleIndex++)
    {
        glm::vec2 centerToParticle = particleCollection[particleIndex]._position - _center;
        float distSqr = glm::dot(centerToParticle, centerToParticle);
        if (distSqr > _radiusSqr)
        {
            particleCollection[particleIndex]._isActive = false;
        }
    }
}