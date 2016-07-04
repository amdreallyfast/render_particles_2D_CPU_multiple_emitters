#version 440

// position in window space (both X and Y on the range [-1,+1])
layout (location = 0) in vec2 pos;  

// velocity also in window space (ex: an X speed of 1.0 would cross the window horizontally in 2 
// seconds)
layout (location = 1) in vec2 vel;  

// must have the same name as its corresponding "in" item in the frag shader
smooth out vec4 particleColor;

void main()
{
    // hard code a white particle color, but let faster colors be brighter
    // Note: There is an implicit assumption that the magnitude of the particle's velocity will 
    // be between 0.0 and 1.0.  That is acceptable for this demo program.
    // Also Note: Don't multiple the full vec4 by the vector length or else the alpha channel will
    // get modified as well.
    float fastness = length(vel);
    vec3 whiteBrightness = vec3(1.0f, 1.0f, 1.0f) * fastness;
    particleColor = vec4(whiteBrightness, 1.0f);

	gl_Position = vec4(pos, -1.0f, 1.0f);
}

