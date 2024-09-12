#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 texCoord;
uniform float ZOffset;
uniform vec3 position;
uniform mat4 scale;

void main()
{
    gl_Position = scale * vec4(aPos.x,aPos.y,0.0f,1.0f) + vec4(position,ZOffset);
    texCoord = aTexCoord;
}