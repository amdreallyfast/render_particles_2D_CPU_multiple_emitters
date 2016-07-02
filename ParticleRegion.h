#pragma once

#include "glm/vec2.hpp"
#include "Particle.h"
#include <vector>

// contains boundaries and the logic to determine when a particle goes outside of spherical boundaries
class ParticleRegionSphere
{
public:
    ParticleRegionSphere();
    void Init(const glm::vec2 &center, const float radius);

    // these methods set a particle's "is active" flag to false if it goes out of bounds

    // may never get used, but here for single particle checks
    void DeactivateIfOutOfBounds(Particle &p);

    // this may be a slightly more efficient way to check large numbers of particles
    void DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection);

private:
    glm::vec2 _center;
    float _radiusSqr;   // because radius is never used
};

class ParticleRegionPolygon
{
public:
    // be aware that these calculations assume that corner1->corner2->corner3->corner4 is 
    // counterclockwise like OpenGL
    ParticleRegionPolygon();

    void Init(const bool isClockwise, const glm::vec2 &corner1, const glm::vec2 &corner2, 
        const glm::vec2 &corner3, const glm::vec2 &corner4);

    // these methods set a particle's "is active" flag to false if it goes out of bounds

    void DeactivateIfOutOfBounds(Particle *p);
    void DeactivateIfOutOfBounds(std::vector<Particle> &particleCollection);

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
