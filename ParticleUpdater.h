#pragma once

#include "Particle.h"
#include "ParticleEmitter.h"
#include "ParticleRegion.h"
#include <vector>

class ParticleUpdater
{
public:
    ParticleUpdater();
    
    // these will be reduced to interfaces soon
    void SetRegion(const ParticleRegionSphere *region);
    void SetRegion(const ParticleRegionPolygon *region);
    
    // these will be reduced to interfaces soon
    void SetEmitter(const ParticleEmitterPoint *emitter, const int maxParticlesEmittedPerFrame);
    void SetEmitter(const ParticleEmitterBar *emitter, const int maxParticlesEmittedPerFrame);

    void Update(std::vector<Particle> &particleCollection);

private:
    ParticleRegionSphere *_regionSphere;
    ParticleRegionPolygon *_regionPolygon;
    ParticleEmitterPoint *_emitterPoint;
    ParticleEmitterPoint *_emitterBar;
};
