#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTex;
layout (location = 1) in vec3 aNormal;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 matrix;
uniform mat4 translation;

out vec3 Normal;
out vec3 CurrentPosition;
out vec2 texCoord;

void main()
{
	CurrentPosition = vec3(matrix*vec4(aPos,1.0f));

    gl_Position = projection*view*translation*matrix*vec4(CurrentPosition,1.0f);
	Normal = aNormal;
	texCoord = aTex;
}

