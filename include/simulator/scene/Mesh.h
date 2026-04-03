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

#include "simulator/graphics/VAO.h"
#include "simulator/graphics/VBO.h"
#include "simulator/graphics/EBO.h"

#include <vector>


class Mesh
{
	public:

		Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, GLsizei i);
		Mesh();

		// Prevent copying
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		
		VAO vao;
		VBO vbo;
		EBO ebo;

		GLsizei indexCount;
};