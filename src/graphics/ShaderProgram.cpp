/*
 * Licensed under the Apache License, Version 2.0.
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "simulator/graphics/ShaderProgram.h"
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>



ShaderProgram::ShaderProgram() {}


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;


	// We ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: SHADER NOT SUCCESFULLY READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* vFragmentCode = fragmentCode.c_str();
	
	





	program = glCreateProgram();
	GLuint vertexShader, fragmentShader;


	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	// error checking code
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		std::cout << "ERROR: VERTEX SHADER COMPILATION FAILED" << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &vFragmentCode, NULL);
	glCompileShader(fragmentShader);

	// error checking code
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED" << std::endl;
	}


	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::ActivateProgram()
{
	glUseProgram(program);
}

void ShaderProgram::DeleteProgram()
{
	glDeleteProgram(program);
}

void ShaderProgram::setM(glm::mat4 modelWorld)
{
	int modelWorldLoc = glGetUniformLocation(program, "model");
	
	glUniformMatrix4fv(modelWorldLoc, 1, GL_FALSE, glm::value_ptr(modelWorld));
}

void ShaderProgram::setV(glm::mat4 worldView)
{
	int worldViewLoc = glGetUniformLocation(program, "view");
	
	glUniformMatrix4fv(worldViewLoc, 1, GL_FALSE, glm::value_ptr(worldView));
}

void ShaderProgram::setP(glm::mat4 viewProj)
{
	int viewProjLoc = glGetUniformLocation(program, "proj");

	glUniformMatrix4fv(viewProjLoc, 1, GL_FALSE, glm::value_ptr(viewProj));
}