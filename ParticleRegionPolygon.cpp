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
    _numCorners = corners.size();

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

    _cp1 = _faceCenterPoints[0];
    _cp2 = _faceCenterPoints[1];
    _cp3 = _faceCenterPoints[2];
    _cp4 = _faceCenterPoints[3];
    _n1 = _faceNormals[0];
    _n2 = _faceNormals[1];
    _n3 = _faceNormals[2];
    _n4 = _faceNormals[3];
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

    Particle pCopy = p;
    switch (_numCorners)
    {
    case 3:
    {
        bool outsideFace1 = glm::dot(pCopy._position - _faceCenterPoints[0], _faceNormals[0]) > 0;
        bool outsideFace2 = glm::dot(pCopy._position - _faceCenterPoints[1], _faceNormals[1]) > 0;
        bool outsideFace3 = glm::dot(pCopy._position - _faceCenterPoints[2], _faceNormals[2]) > 0;
        return outsideFace1 || outsideFace2 || outsideFace3;
    }
    break;
    case 4:
    {
        //bool outsideFace1 = glm::dot(pCopy._position - _faceCenterPoints[0], _faceNormals[0]) > 0;
        //bool outsideFace2 = glm::dot(pCopy._position - _faceCenterPoints[1], _faceNormals[1]) > 0;
        //bool outsideFace3 = glm::dot(pCopy._position - _faceCenterPoints[2], _faceNormals[2]) > 0;
        //bool outsideFace4 = glm::dot(pCopy._position - _faceCenterPoints[3], _faceNormals[3]) > 0;
        //return outsideFace1 || outsideFace2 || outsideFace3 || outsideFace4;
        bool outsideFace1 = glm::dot(pCopy._position - _cp1, _n1) > 0;
        bool outsideFace2 = glm::dot(pCopy._position - _cp2, _n2) > 0;
        bool outsideFace3 = glm::dot(pCopy._position - _cp3, _n3) > 0;
        bool outsideFace4 = glm::dot(pCopy._position - _cp4, _n4) > 0;
        return outsideFace1 || outsideFace2 || outsideFace3 || outsideFace4;
    }
    break;
    case 5:
    {
        bool outsideFace1 = glm::dot(pCopy._position - _faceCenterPoints[0], _faceNormals[0]) > 0;
        bool outsideFace2 = glm::dot(pCopy._position - _faceCenterPoints[1], _faceNormals[1]) > 0;
        bool outsideFace3 = glm::dot(pCopy._position - _faceCenterPoints[2], _faceNormals[2]) > 0;
        bool outsideFace4 = glm::dot(pCopy._position - _faceCenterPoints[3], _faceNormals[3]) > 0;
        bool outsideFace5 = glm::dot(pCopy._position - _faceCenterPoints[4], _faceNormals[4]) > 0;
        return outsideFace1 || outsideFace2 || outsideFace3 || outsideFace4;
    }
    break;
    case 6:
    {
        bool outsideFace1 = glm::dot(pCopy._position - _faceCenterPoints[0], _faceNormals[0]) > 0;
        bool outsideFace2 = glm::dot(pCopy._position - _faceCenterPoints[1], _faceNormals[1]) > 0;
        bool outsideFace3 = glm::dot(pCopy._position - _faceCenterPoints[2], _faceNormals[2]) > 0;
        bool outsideFace4 = glm::dot(pCopy._position - _faceCenterPoints[3], _faceNormals[3]) > 0;
        bool outsideFace5 = glm::dot(pCopy._position - _faceCenterPoints[4], _faceNormals[4]) > 0;
        bool outsideFace6 = glm::dot(pCopy._position - _faceCenterPoints[5], _faceNormals[5]) > 0;
        return outsideFace1 || outsideFace2 || outsideFace3 || outsideFace4 || outsideFace5 || outsideFace6;
    }
    break;
    default:
        return false;
        break;
    }

    //bool outOfBounds = false;
    //// the number of face center pointers == number of face normals, so eithers' size works
    //for (size_t faceCounter = 0; faceCounter < _faceCenterPoints.size(); faceCounter++)
    //{
    //    const glm::vec2 &faceCenter = _faceCenterPoints[faceCounter];
    //    const glm::vec2 &faceNormal = _faceNormals[faceCounter];
    //    if (glm::dot(p._position - faceCenter, faceNormal) > 0)
    //    {
    //        //return true;
    //        outOfBounds = true;
    //    }
    //}

    //// not out of bounds 
    ////return false;
    //return outOfBounds;
}
