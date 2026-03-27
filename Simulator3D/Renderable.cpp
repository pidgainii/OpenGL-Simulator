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



Renderable::Renderable(Mesh* m, GLenum mode)
{
	mesh = m;

	x = 0;
	y = 0;
	z = 0;
	theta = 0;

	drawingMode = mode;
}

void Renderable::SetCoords(float x, float y, float z, float theta)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->theta = theta;  // store theta for rotation
}

glm::mat4 Renderable::ModelWorld()
{
	glm::mat4 model = glm::mat4(1.0f);

	// Translate first
	model = glm::translate(model, glm::vec3(x, y, z));

	// Rotate around vertical axis (y-axis in this example)
	model = glm::rotate(model, theta, glm::vec3(0.0f, 1.0f, 0.0f));

	// Add scaling here if needed
	return model;
}