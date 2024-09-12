//----------------Lighting.cpp------------------//
//  Author: Excilious
//  Date: 12/06/24
//  Abstraction: Lighting system for world.
//
//----------------------------------------------//

#include "Lighting.h"

GLfloat LightVertices[] =
{
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint LightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

Lighting::Lighting()
{};

void Lighting::CreateLightBlock(glm::vec3 Scale, glm::vec3 Position, glm::vec4 Colour)
{
	std::cout << Scale.x << Scale.y << Scale.z << "\n";
	std::cout << Position.x << Position.y << Position.z << "\n";
	std::cout << Colour.x << Colour.y << Colour.z << Colour.w << "\n";
	LightPosition = Position;
	LightScale = Scale;
	LightColour = Colour;

	NewLightShader.CreateNewShader("../../Shaders/Lighting.vert","../../Shaders/Lighting.frag");

	glGenVertexArrays(1,&LightVertexArray);
	glGenBuffers(1,&LightVertexBuffer);
	glGenBuffers(1,&LightElementBuffer);

	glBindVertexArray(LightVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER,LightVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(LightVertices),LightVertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,LightElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(LightIndices),LightIndices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
	glEnableVertexAttribArray(0);
}

void Lighting::RenderLightBlockWorld(Camera& NewCamera)
{
	glm::mat4 LightModel = glm::mat4(1.0f);
	glm::mat4 LightTranslation = glm::mat4(1.0f);
	LightModel = glm::translate(LightModel,LightScale);
	LightTranslation = glm::translate(LightTranslation,LightPosition);
	NewLightShader.ActivateShader();

	glUniformMatrix4fv(glGetUniformLocation(NewLightShader.Program,"matrix"),1,GL_FALSE,glm::value_ptr(LightModel));
    glUniformMatrix4fv(glGetUniformLocation(NewLightShader.Program,"projection"),1,GL_FALSE,glm::value_ptr(NewCamera.ProjectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(NewLightShader.Program,"view"),1,GL_FALSE,glm::value_ptr(NewCamera.ViewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(NewLightShader.Program,"translation"),1,GL_FALSE,glm::value_ptr(LightTranslation));

	glUniform4f(glGetUniformLocation(NewLightShader.Program,"lightColor"),LightColour.x,LightColour.y,LightColour.z,LightColour.w);

	glBindVertexArray(LightVertexArray);
	glDrawElements(GL_TRIANGLES,sizeof(LightIndices)/sizeof(GLuint),GL_UNSIGNED_INT,0);
}

void Lighting::RenderLightBlockModel(Model& NewModel,Shader& NewModelShader,Camera& NewCamera)
{
	glUniform4f(glGetUniformLocation(NewLightShader.Program,"lightColor"),LightColour.x,LightColour.y,LightColour.z,LightColour.w);
	glUniform4f(glGetUniformLocation(NewModelShader.Program,"lightColor"),LightColour.x,LightColour.y,LightColour.z,LightColour.w);
	glUniform3f(glGetUniformLocation(NewModelShader.Program,"lightPos"),LightPosition.x,LightPosition.y,LightPosition.z);
	glUniform3f(glGetUniformLocation(NewModelShader.Program,"camPos"),NewCamera.Position.x,NewCamera.Position.y,NewCamera.Position.z);
}