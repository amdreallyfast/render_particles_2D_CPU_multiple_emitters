#pragma once

#include "Particle.h"
#include "IParticleEmitter.h"
#include "IParticleRegion.h"
#include <vector>

// TODO: header
// contains a region and an emitter
class ParticleUpdater
{
public:
    ParticleUpdater();
    
    void SetRegion(const IParticleRegion *pRegion);

    // TODO: multiple emitters
    void SetEmitter(const IParticleEmitter *pEmitter, const int maxParticlesEmittedPerFrame);

    void Update(std::vector<Particle> &particleCollection, const float deltaTimeSec) const;

private:
    // the form "const something *" means that it is a pointer to a const something, so the 
    // pointer can be changed for a new region or emitter, but the region or emitter itself 
    // can't be altered

    const IParticleRegion *_pRegion;
    const IParticleEmitter *_pEmitter;
    
    // TODO: when using multiple emitters, associate one of these with each emitter
    int _maxParticlesEmittedPerFrame;
};
