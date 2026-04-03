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



#include "simulator/scene/Mesh.h"



// The mesh class will actually store indices and vertices in GPU once
// and then we have the access to vao vbo and ebo in order to be able
// to draw the mesh



Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, GLsizei i)
{
	indexCount = i;

	vao = VAO::VAO();
	vbo = VBO::VBO();
	ebo = EBO::EBO();

	// store vertices and indices in GPU
	vao.Bind();

	// TODO: Use variables, no hardcode numbers
	vbo.Bind();
	vbo.LoadData(vertices.data(), vertices.size() * sizeof(float));
	// TODO: same
	ebo.Bind();
	ebo.LoadData(indices.data(), indices.size() * sizeof(GLuint));

	// TODO: correct this and see how we can get info about this
	vao.LoadAttributes(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	vao.LoadAttributes(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	vbo.Unbind();
	vao.Unbind();
}


Mesh::Mesh()
{
	indexCount = 0;
	
	vao = VAO::VAO();
	vbo = VBO::VBO();
	ebo = EBO::EBO();
}

