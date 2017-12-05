#version 420 core
in layout(location=0) vec3 Position;
in layout(location=1) vec4 Color;
uniform mat4 rot;     //view matrix
out vec4 outcolor;
void main()
{    
    outcolor = Color;
    gl_Position = rot * vec4(Position.x, Position.y, Position.z, 1);
};
