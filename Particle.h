#pragma once

#include "glm/vec2.hpp"

// a simple structure that says where a particle is, where it is going, and whether the emitter 
// has sent it out yet
struct Particle
{
    glm::vec2 _position;
    glm::vec2 _velocity;

    // in order to prevent the emitter from sending out all particles at once, the particle 
    // needs to be able to turn "off" once it is reset until the emitter can get to it
    bool _isActive;
};