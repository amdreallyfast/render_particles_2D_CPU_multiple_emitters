#include "ParticleRegionPolygon.h"

#include "glm/detail/func_geometric.hpp"    // for dot and normalize

/*-----------------------------------------------------------------------------------------------
Description:
    Encapsulates the rotating of a 2D vector by -90 degrees (+90 degrees not used in this demo).
Parameters:
    v   A const 2D vector.
Returns:    
    A 2D vector rotated -90 degrees from the provided one.
Exception:  Safe
Creator:    John Cox (7-2-2016)
-----------------------------------------------------------------------------------------------*/
static glm::vec2 RotateNeg90(const glm::vec2 &v)
{
    return glm::vec2(v.y, -(v.x));
}

/*-----------------------------------------------------------------------------------------------
Description:
    Ensures that the object starts object with initialized values.
Parameters:
    corners     A counterclockwise collection of 2D points in window space (XY on range[-1,+1]).
Returns:    None
Exception:  Safe
Creator:    John Cox (7-2-2016)
-----------------------------------------------------------------------------------------------*/
ParticleRegionPolygon::ParticleRegionPolygon(const std::vector<glm::vec2> corners)
{
    // calculating the face centers does not depend on clockwise-ness
    for (size_t cornerIndex = 0; cornerIndex < corners.size(); cornerIndex++)
    {
        glm::vec2 corner1 = corners[cornerIndex];
        glm::vec2 corner2;
        if (cornerIndex + 1 == corners.size())
        {
            // wrap around
            corner2 = corners[0];
        }
        else
        {
            corner2 = corners[cornerIndex + 1];
        }

        // the center if halfway between these two points
        glm::vec2 faceCenterPoint = (corner1 + corner2) * 0.5f;
        _faceCenterPoints.push_back(faceCenterPoint);
    }

    // the normals should point outwards
    // Note: This means that, if the corners are provided clockwise, then each corner->corner
    // vector needs to rotate +90 degrees, but if the corners are provided counterclockwise, 
    // then each corner->corner vector needs to rotate -90 degrees.  Try drawing it out or 
    // working it out with yoru fingers (I did the latter).
    for (size_t cornerIndex = 0; cornerIndex < corners.size(); cornerIndex++)
    {
        glm::vec2 corner1 = corners[cornerIndex];
        glm::vec2 corner2;
        if (cornerIndex + 1 == corners.size())
        {
            // wrap around
            corner2 = corners[0];
        }
        else
        {
            corner2 = corners[cornerIndex + 1];
        }

        glm::vec2 rotatedFace = RotateNeg90(corner2 - corner1);
        _faceNormals.push_back(rotatedFace);
    }
}

/*-----------------------------------------------------------------------------------------------
Description:
    Checks if the provided particle has gone outside of the polygonal boundaries.
Parameters:
    p   A const reference to a particle object.
Returns:
    True if the particle has outside of the region's boundaries, otherwise false.
Exception:  Safe
Creator:    John Cox (7-2-2016)
-----------------------------------------------------------------------------------------------*/
bool ParticleRegionPolygon::OutOfBounds(const Particle &p) const
{
    // TODO: find a way to speed this up; it is dramatically slower than the circle's region check; ?perhaps use an enum to specify how many edges there are, and then use that to unroll the loop??

    // the number of face center pointers == number of face normals, so eithers' size works
    for (size_t faceCounter = 0; faceCounter < _faceCenterPoints.size(); faceCounter++)
    {
        const glm::vec2 &faceCenter = _faceCenterPoints[faceCounter];
        const glm::vec2 &faceNormal = _faceNormals[faceCounter];
        if (glm::dot(p._position - faceCenter, faceNormal) > 0)
        {
            return true;
        }
    }

    // not out of bounds 
    return false;
}
