#pragma once

#include <map>
#include <string>

/*-----------------------------------------------------------------------------------------------
Description:
    Handles the assembly, storage, and retrieval of different shader programs.  The term 
    "storage" does not imply assembly, but the main functionality of this class after startup 
    will be storage and retrieval of shader program ID, so "storage" seemed to be an appropriate 
    description.
Creator:    John Cox (7-4-2016)
-----------------------------------------------------------------------------------------------*/
class ShaderStorage
{
public:
    ShaderStorage();
    void AddShader(const std::string &key, const unsigned int programId);
private:
};