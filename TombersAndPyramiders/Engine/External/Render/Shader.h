#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLHeaders.h"
#include "HelperFunctions.h"
#include <map>

using namespace std;

#define SHADER_DEFAULT 0
#define SHADER_PIXEL 1
#define SHADER_TILE 2
#define SHADER_SPRITESHEET 3

#define SHADER_PP_DEFAULT 10
#define SHADER_PP_EXTRACTLIGHT 11
#define SHADER_PP_EXTRACTLIGHTDIRECTIONAL 12
#define SHADER_PP_BLOOMCOMBINE 13
#define SHADER_PP_HORIZONTALBLUR 14
#define SHADER_PP_VERTICALBLUR 15
#define SHADER_PP_AMBIENTCOLOR 16
#define SHADER_PP_FOGOFWAR 17
#define SHADER_PP_GRAYSCALE 18

#define SHADER_SHADOW_DEFAULT 20
#define SHADER_SHADOW_SPRITESHEET 21

class Shader
{
private:
	int m_shaderID;
	static std::map<int, Shader*> m_createdShaders;

public:
	GLuint program;
	void use();
	int getID();
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath, int id);
	static Shader* getShader(int shaderID = SHADER_DEFAULT);
};
