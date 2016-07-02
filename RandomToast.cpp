#include "RandomToast.h"
#include <climits>


// Marsaglia's xorshf generator
// According to http://stackoverflow.com/questions/1640258/need-a-fast-random-generator-for-c, 
// unless I'm doing cryptography, this generator rocks.

static unsigned long x = 123456789, y = 362436069, z = 521288629;
//unsigned long xorshf96(void) {          //period 2^96-1

// TODO: header
// the algorithm is positive if stuck into an unsigned long but positive and negative if stuck into a signed long
static unsigned long FastRand(void) {          //period 2^96-1
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

static const float INVERSE_UNSIGNED_LONG = 1.0f / ULONG_MAX;


// TODO: header
float RandomOnRange0to1()
{
    return ((float)FastRand() * INVERSE_UNSIGNED_LONG);
}

// TODO: header
unsigned long Random()
{
    return FastRand();
}

// TODO: header
long RandomPosAndNeg()
{
    return (long)(FastRand());
}

/*-----------------------------------------------------------------------------------------------
Description:
    Generates three random floats on the range 0.0f - 1.0f and stores them in a glm::vec3 for
    use in RGB or other red-green-blue color combinations (texture format and internal format can
    be RGB, GBR, GRB, etc.).
Parameters: None
Returns:
    A glm::vec3 with three random floats stuffed inside on the range 0.0f - 1.0f;
Exception:  Safe
Creator:    John Cox (6-12-2016)
-----------------------------------------------------------------------------------------------*/
glm::vec3 RandomColor()
{
    glm::vec3 ret;
    ret.x = RandomOnRange0to1();
    ret.y = RandomOnRange0to1();
    ret.z = RandomOnRange0to1();
    return ret;
}
