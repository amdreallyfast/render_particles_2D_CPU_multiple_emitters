#pragma once

#include "glm/vec2.hpp"

// TODO: header
class MinMaxVelocity
{
public:
    MinMaxVelocity();

    // need setters because this thing will be utilized in a class that doesn't have all the 
    // information to use this upon creation, and the point particle emitter will need a random 
    // direction, which will need to be handled

    void SetMinMaxVelocity(const float min, const float max);
    void SetDir(const glm::vec2 &dir);
    void UseRandomDir();

    glm::vec2 GetNew() const;
private:
    // why store the max if I'm going to be calculating the delta all the time?
    float _velocityDelta;
    float _min;
    bool _useRandomDir;
    glm::vec2 _dir;
};