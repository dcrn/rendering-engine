#include "ShaderLoader.h"

#include <fstream>
#include <glbinding/gl/enum.h>
#include <iostream>
#include <vector>

#include <glbinding/gl41/functions.h>

using namespace gl;

GLuint ShaderLoader::CompileProgram(const std::vector<GLuint>& shaderIds)
{
	GLuint programId = glCreateProgram();

	for (const GLuint& shaderId : shaderIds)
	{
		glAttachShader(programId, shaderId);
	}

	glLinkProgram(programId);

	GLint linkResult, linkLogBytes;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkResult);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &linkLogBytes);
	if (linkLogBytes > 0)
	{
		std::vector<char> msg(static_cast<size_t>(linkLogBytes) + 1);
		glGetProgramInfoLog(programId, linkLogBytes, nullptr, msg.data());

		if (linkResult != static_cast<GLint>(GL_TRUE))
		{
			throw std::runtime_error("Error while linking program: " + std::string(msg.data()));
		}
		std::cout << "Program linker output: " << msg.data() << std::endl;
	}

	return programId;
}

GLuint ShaderLoader::LoadShader(const std::string& filename, GLenum shaderType)
{
	const GLuint shaderId = glCreateShader(shaderType);
	if (shaderId == 0)
	{
		return 0;
	}

	std::vector<int8_t> shaderSource = LoadFile(filename);

	GLchar* srcString = reinterpret_cast<GLchar*>(shaderSource.data());
	GLint srcLength = static_cast<GLint>(shaderSource.size());
	glShaderSource(shaderId, 1, &srcString, &srcLength);
	glCompileShader(shaderId);

	GLint compileResult, compileLogBytes;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &compileLogBytes);
	if (compileLogBytes > 0)
	{
		std::vector<char> msg(static_cast<size_t>(compileLogBytes) + 1);
		glGetShaderInfoLog(shaderId, compileLogBytes, nullptr, msg.data());

		if (compileResult != static_cast<GLint>(GL_TRUE))
		{
			throw std::runtime_error("Error while compiling shader '" + filename + "': " + msg.data());
		}
		std::cout << "Shader compiler output: " << msg.data() << std::endl;
	}

	return shaderId;
}

std::vector<int8_t> ShaderLoader::LoadFile(const std::string& filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	size_t end = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	std::vector<int8_t> fileData(end - ifs.tellg());

	if (fileData.size() == 0)
	{
		return fileData;
	}

	if (!ifs.read(reinterpret_cast<char*>(fileData.data()), fileData.size()))
	{
		throw std::runtime_error("Cannot load file '" + filename + "', error: " + std::to_string(errno));
	}

	return fileData;
}
