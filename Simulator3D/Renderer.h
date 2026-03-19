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

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"
#include "Renderable.h"

#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>




class Renderer
{
	public:

		ShaderProgram shaderProgram;

		void Init();

		void EnableDepthTest();

		// TEMPORARY ARGUMENTS: worldView, viewProj
		void Render(std::vector<Renderable> scene, glm::mat4 worldView, glm::mat4 viewProj);

		// delete buffers and shader program
		void Clean();
};