#pragma once

// there doesn't seem to be any way out of including all of FreeType without some shady forward 
// declarations of FreeType internal structures
// Note: FreeType has a single header for everything.  This is evil.
#include <ft2build.h>
#include FT_FREETYPE_H  // also defined relative to "freetype-2.6.1/include/"

#include "FreeTypeAtlas.h"

#include <string>
#include <memory>   // for the shared pointer
#include <map>      // for storing the atlas pointers

// this encapsulation was built to associate the FreeType atlas with a particular shader and the 
// uniforms that it contains, plus contain the necessar FT_Library and FT_Face classes
// Note: It is entirely possible to use the FreeType atlas manually, but since rendering text 
// requires a particular shader program, it seemed appropriate to wrap up the shader 
// dependencies in their own class.
class FreeTypeEncapsulated
{
public:
    FreeTypeEncapsulated();
    ~FreeTypeEncapsulated();

    // takes: file path relative to solution directory
    // returns: true if all went well, false if there was trouble
    bool Init(const std::string &trueTypeFontFilePath, const unsigned int programId);

    // the shared pointer will encapsulate the atlas' pointer and clean up after it is 
    // unecessary, and it is const so that the user can't even try to re-initialize it
    // Note: Changing the font size will change the size of the bitmaps of each character, so 
    // each font size must be associated with its own atlas.
    const std::shared_ptr<FreeTypeAtlas> GetAtlas(const int fontSize);

private:
    bool _haveInitialized;

    FT_Library _ftLib;  // move to a "FreeTypeContainment" class
    FT_Face _ftFace;    // move to a "FreeTypeContainment" class

    typedef std::map<int, std::shared_ptr<FreeTypeAtlas>> _ATLAS_MAP;
    _ATLAS_MAP _atlasMap;

    // drawing these textures requires their own shader
    // Note: These are actually GLuint and GLint values, but I didn't want to include all of 
    // OpenGL just for the typedefs, which is unfortunately necessary since the only readily 
    // available header files for OpenGL include everything.
    unsigned int _programId;
    int _uniformTextSamplerLoc;   // uniform location within program
    int _uniformTextColorLoc;     // uniform location within program
};