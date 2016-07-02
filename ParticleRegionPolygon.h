#pragma once

#include "IParticleRegion.h"
#include "glm/vec2.hpp"
#include "Particle.h"
#include <vector>

// TODO: header
class ParticleRegionPolygon : IParticleRegion
{
public:
    ParticleRegionPolygon();
    void Init(const bool isClockwise, const glm::vec2 &corner1, const glm::vec2 &corner2,
        const glm::vec2 &corner3, const glm::vec2 &corner4);

    virtual bool OutOfBounds(const Particle &p) const;
    virtual void DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection) const;

private:
    glm::vec2 _face1Normal;
    glm::vec2 _face2Normal;
    glm::vec2 _face3Normal;
    glm::vec2 _face4Normal;

    // these centers are used as reference points to make a vector out of the particle's current 
    // position that stems from the same base as the face normal
    // Note: I actually could have used any point along the face, but the center point is 
    // conceptually easy to imagine as the "source" of the surface normal since that is where it 
    // is usually drawn in diagrams.
    glm::vec2 _face1CenterPoint;
    glm::vec2 _face2CenterPoint;
    glm::vec2 _face3CenterPoint;
    glm::vec2 _face4CenterPoint;
};