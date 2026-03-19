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


#include "Renderable.h"

#include <glm/gtc/matrix_transform.hpp>



Renderable::Renderable(Mesh* m, GLenum mode, float d_x, float d_y, float d_z)
{
	mesh = m;

	dx = d_x;
	dy = d_y;
	dz = d_z;

	x = 0;
	y = 0;
	z = 0;

	drawingMode = mode;
}

// This function will update coordinates with dt, (not t)
void Renderable::Update(float dt)
{
	x += dx * dt;
	y += dy * dt;
	z += dz * dt;
}

glm::mat4 Renderable::ModelWorld()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	// add scale if needed
	return model;
}
