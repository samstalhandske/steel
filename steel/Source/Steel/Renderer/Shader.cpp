#include "pch.h"
#include "Shader.hpp"

#include <glad/glad.h>

namespace Steel
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//https://www.khronos.org/opengl/wiki/Shader_Compilation

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);


		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);
		STEEL_ENGINE_INFO("Vertex Shader, \"{0}\", compiling...", vertexSrc);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			STEEL_ENGINE_ERROR("Failed compiling shader: {0}", infoLog.data());
			
			return;
		}



		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);
		STEEL_ENGINE_INFO("Fragment Shader, \"{0}\", compiling...", fragmentSrc);
		
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			STEEL_ENGINE_ERROR("Failed compiling fragment shader: {0}", infoLog.data());

			return;
		}



		myRendererID = glCreateProgram();
		GLuint program = myRendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		STEEL_ENGINE_INFO("Vertex and Fragment Shader, attaching...");

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			STEEL_ENGINE_ERROR("Failed attaching vertex and fragment shader to program: {0}", infoLog.data());

			return;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(myRendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(myRendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}
