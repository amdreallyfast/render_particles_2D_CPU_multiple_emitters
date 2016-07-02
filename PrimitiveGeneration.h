#pragma once

#include "GeometryData.h"
#include "glm/vec2.hpp"
#include <vector>

void GenerateTriangle(GeometryData *putDataHere);
void GenerateBox(GeometryData *putDataHere);
void GenerateCircle(GeometryData *putDataHere);
void GeneratePolygonWireframe(GeometryData *putDataHere, const std::vector<glm::vec2> &corners, 
    bool isClockwise);
void InitializeGeometry(unsigned int programId, GeometryData *initThis);