#pragma once

#include <glbinding/gl/types.h>

#include <string>
#include <vector>

class ShaderLoader
{
public:
	gl::GLuint CompileProgram(const std::vector<gl::GLuint>& shaderIds);
	static gl::GLuint LoadShader(const std::string& filename, gl::GLenum shaderType);

private:
	static std::vector<int8_t> LoadFile(const std::string& filename);
};

