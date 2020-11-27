
#include "Modules/RenderModule/Shader.h"

#include <fstream>
#include <sstream>
#include "SDL.h"

using std::ifstream;

Shader::Shader()
{

}

bool Shader::Load(const string& vertName, const string& fragName)
{
	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader)
		|| !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);
	
	return IsValidProgram();
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

Shader::~Shader()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

bool Shader::CompileShader(const string& fileName, GLenum shaderType, GLuint& outShader)
{
	ifstream shaderFile(fileName);

	if (shaderFile.is_open())
	{
		std::stringstream sstream;

		sstream << shaderFile.rdbuf();
		
		const char* contentsChar = sstream.str().c_str();

		outShader = glCreateShader(shaderType);

		glShaderSource(outShader, 1, &contentsChar, nullptr);

		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader: %s\n", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s\n", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[128];
		memset(buffer, 0, 128);
		glGetShaderInfoLog(shader, 127, nullptr, buffer);
		SDL_Log("GLSL compile failed: %s\n", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;

	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[128];
		memset(buffer, 0, 128);
		glGetProgramInfoLog(mShaderProgram, 127, nullptr, buffer);
		SDL_Log("GLSL compile failed: %s\n", buffer);
		return false;
	}
	return true;
}

