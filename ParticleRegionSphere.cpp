#include "ParticleRegionSphere.h"

#include "glm/detail/func_geometric.hpp"    // glm::dot

// TODO: header
ParticleRegionSphere::ParticleRegionSphere() :
    // the glm::vec2 initializes itself to 0
    _radiusSqr(0.0f)
{
}

// TODO: header
void ParticleRegionSphere::Init(const glm::vec2 &center, const float radius)
{
    _center = center;
    _radiusSqr = radius * radius;
}

// TODO: header
bool ParticleRegionSphere::OutOfBounds(const Particle &p) const
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
void ParticleRegionSphere::DeactivateIfOutOfBounds(
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