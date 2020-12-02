#pragma once

#include "glew.h"
#include <string>

using std::string;

class Shader
{

public:

	Shader();

	bool	Load(const string& vertName, const string& fragName);

	void	SetActive();

	~Shader();

private:

	bool	CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader);

	bool	IsCompiled(GLuint shader);

	bool	IsValidProgram();

	bool	CheckIsValid(GLenum checkParam, bool isProgram, GLuint* entity, string errorMsg);

	GLuint	mVertexShader;
	GLuint	mFragShader;
	GLuint	mShaderProgram;

};