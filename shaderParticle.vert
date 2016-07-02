#version 440

layout (location = 0) in vec2 pos;  // position in window space

// must have the same name as its corresponding "in" item in the frag shader
smooth out vec3 particleColor;

void main()
{
    // just hard code a white particle color for now and shove the position out the door
    particleColor = vec3(0.5f, 0.5f, 0.5f);
	gl_Position = vec4(pos, -1.0f, 1.0f);
}

