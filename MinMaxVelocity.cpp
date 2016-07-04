#include "MinMaxVelocity.h"

#include "glm/detail/func_geometric.hpp" // for normalizing glm vectors
#include "RandomToast.h"


// TODO: header
MinMaxVelocity::MinMaxVelocity() :
    _min(-1.0f),
    _velocityDelta(-1.0f),
    _useRandomDir(true) // until a direction is set, assume random
{
}

// TODO: header
void MinMaxVelocity::SetMinMaxVelocity(const float min, const float max)
{
    _min = min;
    _velocityDelta = max - min;
}

// TODO: header
void MinMaxVelocity::SetDir(const glm::vec2 &dir)
{
    _dir = dir;
    _useRandomDir = false;
}

// TODO: header
void MinMaxVelocity::UseRandomDir()
{
    _dir = glm::vec2();
    _useRandomDir = true;
}

// TODO: header
glm::vec2 MinMaxVelocity::GetNew() const
{
    //float velocityVariation = ((float)rand() * INVERSE_RAND_MAX) * _velocityDelta;
    float velocityVariation = RandomOnRange0to1() * _velocityDelta;
    float velocityMagnitude = _min + velocityVariation;
    
    if (_useRandomDir)
    {
        // create a normalized random vector, then multiple all items by the magnitude
        // Note: The hard-coded mod100 is just to prevent the random axis magnitudes from 
        // getting too crazy different from each other.
        float newX = (float)(RandomPosAndNeg() % 100);
        float newY = (float)(RandomPosAndNeg() % 100);
        glm::vec2 randomVelocityVector = glm::normalize(glm::vec2(newX, newY));
        return (randomVelocityVector * velocityMagnitude);
    }
    else  // read, "don't use random direction"
    {
        return (_dir * velocityMagnitude);
    }
}

