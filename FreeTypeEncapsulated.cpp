#include "FreeTypeEncapsulated.h"

// the OpenGL version include also includes all previous versions
// Build note: Do NOT mistakenly include _int_gl_4_4.h.  That one doesn't define OpenGL stuff 
// first.
#include "glload/include/glload/gl_4_4.h"

// for make the shaders
#include "ShaderStorage.h"


FreeTypeEncapsulated::FreeTypeEncapsulated()
    :
    _haveInitialized(0),
    _programId(0),
    _uniformTextSamplerLoc(0),
    _uniformTextColorLoc(0)
{
}

FreeTypeEncapsulated::~FreeTypeEncapsulated()
{
    // cleanup
    glDeleteProgram(_programId);
}

std::string FreeTypeEncapsulated::Init(const std::string &trueTypeFontFilePath,
    const std::string &vertShaderPath, const std::string &fragShaderPath)
{
    // FreeType needs to load itself into particular variables
    // Note: FT_Init_FreeType(...) returns something called an FT_Error, which VS can't find.
    // Based on the useage, it is assumed that 0 is returned if something went wrong, otherwise
    // non-zero is returned.  That is the only explanation for this kind of condition.
    if (FT_Init_FreeType(&_ftLib))
    {
        fprintf(stderr, "Could not init freetype library\n");
        return false;
    }

    // Note: FT_New_Face(...) also returns an FT_Error.
    if (FT_New_Face(_ftLib, trueTypeFontFilePath.c_str(), 0, &_ftFace))
    {
        fprintf(stderr, "Could not open font '%s'\n", trueTypeFontFilePath.c_str());
        return false;
    }

    ShaderStorage &shaderStorageRef = ShaderStorage::GetInstance();
    std::string shaderKey = "freetype";
    shaderStorageRef.NewShader(shaderKey);
    shaderStorageRef.AddShaderFile(shaderKey, vertShaderPath, GL_VERTEX_SHADER);
    shaderStorageRef.AddShaderFile(shaderKey, fragShaderPath, GL_FRAGMENT_SHADER);
    shaderStorageRef.LinkShader(shaderKey);
    _programId = shaderStorageRef.GetShaderProgram(shaderKey);
    if (_programId == 0)
    {
        fprintf(stderr, "Freetype shader program is 0.  This is invalid.\n");
        return false;
    }

    // pick out the attributes and uniforms used in the FreeType GPU program

    char textTextureName[] = "textureSamplerId";
    _uniformTextSamplerLoc = glGetUniformLocation(_programId, textTextureName);
    if (_uniformTextSamplerLoc == -1)
    {
        fprintf(stderr, "Could not bind uniform '%s'\n", textTextureName);
        return false;
    }

    //char textColorName[] = "color";
    char textColorName[] = "textureColor";
    _uniformTextColorLoc = glGetUniformLocation(_programId, textColorName);
    if (_uniformTextColorLoc == -1)
    {
        fprintf(stderr, "Could not bind uniform '%s'\n", textColorName);
        return false;
    }

    _haveInitialized = true;
    return shaderKey;
}

//const std::shared_ptr<FreeTypeAtlas> FreeTypeEncapsulated::GenerateAtlas(const int fontSize)
//{
//    if (!_haveInitialized)
//    {
//        fprintf(stderr, "FreeTypeEncapsulated object has not been initialized with font file and shader file paths.\n");
//        return false;
//    }
//
//    std::shared_ptr<FreeTypeAtlas> newAtlasPtr = std::make_shared<FreeTypeAtlas>(
//        _uniformTextSamplerLoc, _uniformTextColorLoc);
//    newAtlasPtr->Init(_ftFace, fontSize);
//
//    return newAtlasPtr;
//}

const std::shared_ptr<FreeTypeAtlas> FreeTypeEncapsulated::GetAtlas(const int fontSize)
{
    if (!_haveInitialized)
    {
        fprintf(stderr, "FreeTypeEncapsulated object has not been initialized with font file and shader file paths.\n");
        return false;
    }

    _ATLAS_MAP::iterator itr = _atlasMap.find(fontSize);
    if (itr != _atlasMap.end())
    {
        // found it
        return itr->second;
    }
    else
    {
        // make a new one
        std::shared_ptr<FreeTypeAtlas> newAtlasPtr = std::make_shared<FreeTypeAtlas>(
            _uniformTextSamplerLoc, _uniformTextColorLoc);
        newAtlasPtr->Init(_ftFace, fontSize);
        _atlasMap[fontSize] = newAtlasPtr;
        return newAtlasPtr;
    }
}

