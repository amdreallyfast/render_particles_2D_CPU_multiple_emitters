#pragma once

#include "Particle.h"
#include <vector>

// TODO: header
// the purpose of this structure is to associate an OpenGL buffer and any necessary vertex attributes with a particle collection
// this is a struct because I can't think of a good reason to make it private; the OpenGL data should definitely be restricted, but the GeometryData gets away with it just fine, and the particle collection needs to be accessible by the ParticleUpdater class, so I could jump through some hoops to make it accessible through a friend interface or something, or I could just be responsible and not mess them up; 
struct ParticleStorage
{
public:
    ParticleStorage();
    void Init(unsigned int programId, unsigned int numParticles);

    // save on the large header inclusion of OpenGL and write out these primitive types instead 
    // of using the OpenGL typedefs
    // Note: IDs are GLuint (unsigned int), draw style is GLenum (unsigned int), GLushort is 
    // unsigned short.
    unsigned int _vaoId;
    unsigned int _arrayBufferId;
    unsigned int _drawStyle;    // GL_TRIANGLES, GL_LINES, etc.
    unsigned int _sizeBytes;    // useful for glBufferSubData(...)
    std::vector<Particle> _allParticles;
};

