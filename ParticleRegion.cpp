#include "ParticleRegion.h"
#include "glm/detail/func_geometric.hpp"    // for dot and normalize


static glm::vec2 RotatePlus90(const glm::vec2 &v)
{
    return glm::vec2(-(v.y), v.x);
}

static glm::vec2 RotateNeg90(const glm::vec2 &v)
{
    return glm::vec2(v.y, -(v.x));
}

ParticleRegionSphere::ParticleRegionSphere() :
    // the glm::vec2 initializes itself to 0
    _radiusSqr(0.0f)
{
}

void ParticleRegionSphere::Init(const glm::vec2 &center, const float radius)
{
    _center = center;
    _radiusSqr = radius * radius;
}

void ParticleRegionSphere::DeactivateIfOutOfBounds(Particle &p)
{
    glm::vec2 centerToParticle = p._position - _center;
    float distSqr = glm::dot(centerToParticle, centerToParticle);
    if (distSqr > _radiusSqr)
    {
        p._isActive = false;
    }
}

void ParticleRegionSphere::DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection)
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


ParticleRegionPolygon::ParticleRegionPolygon()
{
    // the glm::vec2 objects have initializers to 0, so don't bother initializing them
}

void ParticleRegionPolygon::Init(const bool isClockwise, const glm::vec2 &corner1, const glm::vec2 &corner2,
    const glm::vec2 &corner3, const glm::vec2 &corner4)
{
    // the normals should point outwards
    // Note: This means that, if the corners are provided clockwise, then each corner->corner
    // vector needs to rotate +90 degrees, but if the corners are provided counterclockwise, 
    // then each corner->corner vector needs to rotate -90 degrees.  Try drawing it out or 
    // working it out with yoru fingers (I did the latter).
    _face1CenterPoint = (corner1 + corner2) * 0.5f;
    _face2CenterPoint = (corner2 + corner3) * 0.5f;
    _face3CenterPoint = (corner3 + corner4) * 0.5f;
    _face4CenterPoint = (corner4 + corner1) * 0.5f;

    if (isClockwise)
    {
        _face1Normal = glm::normalize(RotatePlus90(corner2 - corner1));
        _face2Normal = glm::normalize(RotatePlus90(corner3 - corner2));
        _face3Normal = glm::normalize(RotatePlus90(corner4 - corner3));
        _face4Normal = glm::normalize(RotatePlus90(corner1 - corner4));
    }
    else
    {
        _face1Normal = glm::normalize(RotateNeg90(corner2 - corner1));
        _face2Normal = glm::normalize(RotateNeg90(corner3 - corner2));
        _face3Normal = glm::normalize(RotateNeg90(corner4 - corner3));
        _face4Normal = glm::normalize(RotateNeg90(corner1 - corner4));
    }
}

void ParticleRegionPolygon::DeactivateIfOutOfBounds(Particle *p)
{
    glm::vec2 toParticle = p->_position - _face1CenterPoint;
    if (glm::dot(toParticle, _face1Normal) > 0)
    {
        p->_isActive = 0;
        return;
    }

    toParticle = p->_position - _face2CenterPoint;
    if (glm::dot(toParticle, _face2Normal) > 0)
    {
        p->_isActive = 0;
        return;
    }

    toParticle = p->_position - _face3CenterPoint;
    if (glm::dot(toParticle, _face3Normal) > 0)
    {
        p->_isActive = 0;
        return;
    }

    toParticle = p->_position - _face4CenterPoint;
    if (glm::dot(toParticle, _face4Normal) > 0)
    {
        p->_isActive = 0;
        return;
    }
}

void ParticleRegionPolygon::DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection)
{
    for (size_t particleIndex = 0; particleIndex < particleCollection.size(); particleIndex++)
    {
        glm::vec2 particlePosition = particleCollection[particleIndex]._position;

        // assume within bounds until proven otherwise
        bool activeStatus = true;

        // these could be condensed even more, but I spelled them out for the sake of 
        // (1) demonstration and (2) debugging
        if (glm::dot(particlePosition - _face1CenterPoint, _face1Normal) > 0)
        {
            activeStatus = false;
        }
        else if (glm::dot(particlePosition - _face2CenterPoint, _face2Normal) > 0)
        {
            activeStatus = false;
        }
        else if (glm::dot(particlePosition - _face3CenterPoint, _face3Normal) > 0)
        {
            activeStatus = false;
        }
        else if (glm::dot(particlePosition - _face4CenterPoint, _face4Normal) > 0)
        {
            activeStatus = false;
        }

        particleCollection[particleIndex]._isActive = activeStatus;
    }
}

