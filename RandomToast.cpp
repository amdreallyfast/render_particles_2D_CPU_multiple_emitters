#include "RandomToast.h"
#include <climits>


// Marsaglia's xorshf generator
// According to http://stackoverflow.com/questions/1640258/need-a-fast-random-generator-for-c, 
// unless I'm doing cryptography, this generator rocks.

static unsigned long x = 123456789, y = 362436069, z = 521288629;
//unsigned long xorshf96(void) {          //period 2^96-1
static unsigned long FastRandPosOnly(void) {          //period 2^96-1
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
float RandomOnRange0to1()
{
    return ((float)FastRandPosOnly() * INVERSE_UNSIGNED_LONG);
}

unsigned long Random()
{
    return FastRandPosOnly();
}

long RandomPosAndNeg()
{
    return (long)(FastRandPosOnly());
}
