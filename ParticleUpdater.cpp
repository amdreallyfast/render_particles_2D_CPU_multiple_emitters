#include "ParticleUpdater.h"

//class ParticleUpdater

ParticleUpdater::ParticleUpdater() :
    _regionSphere(0),
    _regionPolygon(0),
    _emitterPoint(0),
    _emitterBar(0)
{
}

void ParticleUpdater::SetRegion(const ParticleRegionSphere *region)
{
}

void ParticleUpdater::SetRegion(const ParticleRegionPolygon *region)
{
}

void ParticleUpdater::SetEmitter(const ParticleEmitterPoint *emitter, const int maxParticlesEmittedPerFrame)
{
}

void ParticleUpdater::SetEmitter(const ParticleEmitterBar *emitter, const int maxParticlesEmittedPerFrame)
{
}

void ParticleUpdater::Update(std::vector<Particle> &particleCollection)
{
}

