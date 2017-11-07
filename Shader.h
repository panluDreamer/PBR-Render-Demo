#ifndef SHADER_H
#define SHADER_H
#include <QObject>
#include <QtGui/QOpenGLFunctions_4_1_Core>
#include <QtOpenGLExtensions/QOpenGLExtensions>
#include<glm\gtc\type_ptr.hpp>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;
class Shader : public QObject, protected QOpenGLFunctions_4_1_Core
{
	Q_OBJECT
private:
	GLuint program;
public:
	Shader() {}
	~Shader() {
		glDeleteProgram(program);
	}
	//init shader using two types of shader files
	void init(const char * vetex_shader_path, const char * frag_shader_path) {
		initializeOpenGLFunctions();
		program = LoadShaders(vetex_shader_path, frag_shader_path);
	}
	GLuint getProgram() {
		return program;
	}
	void use()
	{
		glUseProgram(program);
	}

	void bind_mat4(const char* name, glm::mat4 const & mat)
	{
		GLint loc = get_uniform_loc(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
	}

	void bind_bool(const char* name, const bool b)
	{
		bind_int(name, b);
	}

	void bind_int(const char* name, const int i)
	{
		GLint loc = get_uniform_loc(name);
		glUniform1i(loc, i);
	}

	void bind_float(const char* name, const float f)
	{
		GLint loc = get_uniform_loc(name);
		glUniform1f(loc, f);
	}

	void bind_vec2(const char* name, glm::vec2 const & vec)
	{
		GLint loc = get_uniform_loc(name);
		glUniform2fv(loc, 1, &vec[0]);
	}

	void bind_vec3(const char* name, glm::vec3 const & vec)
	{
		GLint loc = get_uniform_loc(name);
		glUniform3fv(loc, 1, &vec[0]);
	}

	void bind_vec4_array(const char* name, std::vector<glm::vec4> vec)
	{
		GLint loc = get_uniform_loc(name);
		glUniform4fv(loc, (GLsizei)vec.size(), glm::value_ptr(vec[0]));
	}

	void bind_texture(const char* name, GLuint texture, GLuint id, GLenum texture_type = GL_TEXTURE_2D)
	{
		glActiveTexture(GLenum(GL_TEXTURE0 + id));
		glBindTexture(texture_type, texture);
		GLuint loc = glGetUniformLocation(program, name);
		glUniform1i(loc, id);
	}
private:
	GLuint LoadShaders(const char * vertex_shader_path, const char * frag_shader_path) {
		string vertexCode;
		string fragCode;
		ifstream vertexFile, fragFile;
		vertexFile.exceptions(ifstream::failbit | ifstream::badbit);
		fragFile.exceptions(ifstream::failbit | ifstream::badbit);
		try
		{
			vertexFile.open(vertex_shader_path);
			fragFile.open(frag_shader_path);
			stringstream vertexStream, fragStream;
			vertexStream << vertexFile.rdbuf();
			fragStream << fragFile.rdbuf();
			vertexFile.close();
			fragFile.close();
			vertexCode = vertexStream.str();
			fragCode = fragStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		GLuint vertexShaderID, fragShaderID;
		const char *vetexTemp = vertexCode.c_str();
		const char *fragTemp = fragCode.c_str();
		//vertex shader
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vetexTemp, NULL);
		glCompileShader(vertexShaderID);
		checkCompileErrors(vertexShaderID, "VERTEX");

		fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShaderID, 1, &fragTemp, NULL);
		glCompileShader(fragShaderID);
		checkCompileErrors(fragShaderID, "FRAGMENT");

		program = glCreateProgram();
		glAttachShader(program, vertexShaderID);
		glAttachShader(program, fragShaderID);
		glLinkProgram(program);
		checkCompileErrors(program, "PROGRAM");
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragShaderID);
		return program;
	}
	GLint get_uniform_loc(const char * name)
	{
		GLint loc = glGetUniformLocation(program, name);
		if (loc == -1) {
			cerr << name << " Uniform not found!" << endl;
		}
		return loc;
	}
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

#endif
