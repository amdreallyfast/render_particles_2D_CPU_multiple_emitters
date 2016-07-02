#pragma once

#include <map>
#include <string>

class ShaderStorage
{
public:
    ShaderStorage();
    void AddShader(const std::string &key, const unsigned int programId);
private:
};