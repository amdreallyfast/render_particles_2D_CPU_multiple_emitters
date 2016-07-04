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
    // used to unroll a loop in the "out of bounds" check, which became necessary when the frame
    // rate dropped like a rock when going from 1000->10000 particles (the circle particle 
    // region was fine and trucks along at a high frame rate)
    unsigned int _numCorners;

    glm::vec2 _cp1;
    glm::vec2 _cp2;
    glm::vec2 _cp3;
    glm::vec2 _cp4;
    glm::vec2 _n1;
    glm::vec2 _n2;
    glm::vec2 _n3;
    glm::vec2 _n4;

    std::vector<glm::vec2> _faceNormals;

    // these centers are used as reference points to make a vector out of the particle's current 
    // position that stems from the same base as the face normal
    // Note: I actually could have used any point along the face, but the center point is 
    // conceptually easy to imagine as the "source" of the surface normal since that is where it 
    // is usually drawn in diagrams.
    std::vector<glm::vec2> _faceCenterPoints;
};