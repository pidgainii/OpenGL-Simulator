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


#include "simulator/graphics/Renderer.h"

#include <iostream>




// TODO: This method will take a list of renderable objects
// and load them to gpu i guess
// For now it will just take our cube

// Update -> Meshes are loaded to GPU when being created,
// no need to do that here
void Renderer::Init()
{
	// Now we will activate OpenGL functions with GLAD loader
	gladLoadGL();

	// TODO: make variables for width and height
	glViewport(0, 0, 1400, 900);

	// TODO: specify shaders in some other way
	shaderProgram = ShaderProgram(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);


	EnableDepthTest();
}



void Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void ActivateShaders(ShaderProgram shaderProgram)
{
	shaderProgram.ActivateProgram();
}

void setCameraMatrix(ShaderProgram shaderProgram, glm::mat4 worldView, glm::mat4 viewProj)
{
	shaderProgram.setV(worldView);
	shaderProgram.setP(viewProj);
}

void DrawElements(ShaderProgram shaderProgram, std::vector<Renderable> scene)
{
	// for each element, the renderer should draw the mesh using the
	// mesh vao, vbo and ebo i guess
	// also it should say to the shader programme to set the model matrix
	for (Renderable r : scene)
	{
		shaderProgram.setM(r.ModelWorld());
		r.mesh->vao.Bind();

		// the index count is how many indices to draw, mesh should know that
		// also it should know the draw mode
		glDrawElements(r.drawingMode, r.mesh->indexCount, GL_UNSIGNED_INT, 0);

		// TODO: put this in another place
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

// TEMPORARY ARGUMENTS: worldView, viewProj
void Renderer::Render(std::vector<Renderable> scene, glm::mat4 worldView, glm::mat4 viewProj)
{
	Clear();
	ActivateShaders(shaderProgram);
	setCameraMatrix(shaderProgram, worldView, viewProj);
	DrawElements(shaderProgram, scene);
}



void Renderer::Clean()
{
	shaderProgram.DeleteProgram();
}