#pragma once

#include "IParticleRegion.h"
#include "glm/vec2.hpp"
#include "Particle.h"
#include <vector>

/*-----------------------------------------------------------------------------------------------
Description:
    This object defines a polygonal region within which particles are considered active and the
    logic to determine when a particle goes outside of its boundaries.
Creator:    John Cox (7-2-2016)
-----------------------------------------------------------------------------------------------*/
class ParticleRegionPolygon : public IParticleRegion
{
public:
    ParticleRegionPolygon(const std::vector<glm::vec2> corners);
    virtual bool OutOfBounds(const Particle &p) const;

private:
    std::vector<glm::vec2> _faceNormals;

    // these centers are used as reference points to make a vector out of the particle's current 
    // position that stems from the same base as the face normal
    // Note: I actually could have used any point along the face, but the center point is 
    // conceptually easy to imagine as the "source" of the surface normal since that is where it 
    // is usually drawn in diagrams.
    std::vector<glm::vec2> _faceCenterPoints;
};