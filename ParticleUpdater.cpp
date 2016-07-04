#include "ParticleUpdater.h"

//class ParticleUpdater

// TODO: header
ParticleUpdater::ParticleUpdater() :
    _pRegion(0),
    _pEmitter(0)
{
}

// TODO: header
void ParticleUpdater::SetRegion(const IParticleRegion *pRegion)
{
    _pRegion = pRegion;
}

// TODO: header
void ParticleUpdater::SetEmitter(const IParticleEmitter *pEmitter, const int maxParticlesEmittedPerFrame)
{
    _pEmitter = pEmitter;
    _maxParticlesEmittedPerFrame = maxParticlesEmittedPerFrame;
}

// TODO: header
void ParticleUpdater::Update(std::vector<Particle> &particleCollection, 
    const float deltaTimeSec) const
{
    // TODO: ??some kind of std::remove_if(...) algorithm? for each item, if not good, then swap with last item and reduce final index by 1??

    // for all particles:
    // - if it has gone out of bounds, reset it and deactivate it
    // - if it is inactive and the emitter hasn't used up its quota for emitted particles this frame, reactivate it
    // - if it is active, update its position with its velocity
    // Note: If if() statements are used for each situation, then a particle has a chance to go 
    // out of bounds and get reset, get reactivated, and emit again in the same frame.  If 
    // else-if() statements are used, then only one of those situations will be run per frame.  
    // I did the former, but it doesn't really matter which approach is chosen.

    int emitCounter = 0;
    for (size_t particleIndex = 0; particleIndex < particleCollection.size(); particleIndex++)
    {
        Particle &particleRef = particleCollection[particleIndex];
        if (_pRegion->OutOfBounds(particleRef))
        {
            particleRef._isActive = false;
            _pEmitter->ResetParticle(&(particleCollection[particleIndex]));
        }

        // if vs else-if()? eh
        if (!particleRef._isActive && emitCounter < _maxParticlesEmittedPerFrame)
        {
            particleRef._isActive = true;
        }

        if (particleRef._isActive)
        {
            particleRef._position = particleRef._position + 
                (particleRef._velocity * deltaTimeSec);
        }
    }
}

