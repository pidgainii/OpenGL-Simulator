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

#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShaderProgram {
	public: 
		GLuint program;

		ShaderProgram();

		ShaderProgram(const char* vertexPath, const char* fragmentPath);

		void ActivateProgram();

		void DeleteProgram();

		void setM(glm::mat4 modelWorld);
		void setV(glm::mat4 worldView);
		void setP(glm::mat4 viewProj);
};