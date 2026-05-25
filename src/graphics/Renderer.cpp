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



void Renderer::Init()
{
	// Now we will activate OpenGL functions with GLAD loader
	gladLoadGL();

	glViewport(0, 0, 1400, 900);

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
	for (Renderable r : scene)
	{
		shaderProgram.setM(r.ModelWorld());
		r.mesh->vao.Bind();

		glDrawElements(r.drawingMode, r.mesh->indexCount, GL_UNSIGNED_INT, 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

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