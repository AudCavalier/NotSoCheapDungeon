#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexFile, const char* fragmentFile) {
		std::ifstream vertexHandle, fragmentHandle;
		std::string vString, fString;
		//MAKE SURE ifstreams CAN THROW EXCEPTIONS
		//vertexHandle.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		//fragmentHandle.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vertexHandle.open(vertexFile);
			fragmentHandle.open(fragmentFile);
			std::stringstream vertexCode, fragmentCode;
			vertexCode << vertexHandle.rdbuf();
			fragmentCode << fragmentHandle.rdbuf();
			vertexHandle.close();
			fragmentHandle.close();
			vString = vertexCode.str();
			fString = fragmentCode.str();
		}
		catch (std::exception e) {
			std::cout << "EXCEPTION: " << e.what() << "\n";
		}
		const char* vShaderCode = vString.c_str();
		const char* fShaderCode = fString.c_str();
		
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckSuccess(vertex, "Vertex Shader");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckSuccess(fragment, "Fragment Shader");
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckSuccess(ID, "Program");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void use() {
		glUseProgram(ID);
	}
	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setVec2(const std::string &name, glm::vec2 value) const {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &name, int x, int y) const {
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void setVec3(const std::string &name, glm::vec2 value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &name, int x, int y, int z) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void setVec4(const std::string &name, glm::vec2 value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &name, int x, int y, int z, int w) const {
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	void setMat2(const std::string &name, glm::mat2 mat) const {
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat3(const std::string &name, glm::mat3 mat) const {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setMat4(const std::string &name, glm::mat4 mat) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	void CheckSuccess(int prog, std::string type) {
		int success;
		char infoLog[512];
		if (type != "Program") {
			glGetShaderiv(prog, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(prog, 512, NULL, infoLog);
				std::cout << "ERROR: " << type << "\n" << infoLog << "\n";
			}
		}
		else {
			glGetProgramiv(prog, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(prog, 512, NULL, infoLog);
				std::cout << "ERROR: " << type << "\n" << infoLog << "\n";
			}
		}
	}
};

#endif // !SHADER_H
