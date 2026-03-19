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



#include "Loader.h"
#include "ObjLoader.h"


Loader::Loader() {}

void Loader::LoadScene(std::vector<Renderable>& scene)
{
	// Loading mesh for airplane
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	loadOBJ("airplane.txt", vertices, indices);
	Mesh* planeMesh = new Mesh(vertices, indices, indices.size());

	// Load grid
	std::vector<float> gridVertices;
	std::vector<unsigned int> gridIndices;
	loadOBJ("grid.txt", gridVertices, gridIndices);
	Mesh* gridMesh = new Mesh(gridVertices, gridIndices, gridIndices.size());


	// Creating Renderable objects
	Renderable plane1 = Renderable(planeMesh, GL_TRIANGLES, 0.0f, 0.0f, 0.9f);
	Renderable plane2 = Renderable(planeMesh, GL_TRIANGLES, 0.0f, 0.0f, 0.0f);
	Renderable grid = Renderable(gridMesh, GL_LINES, 0.0f, 0.0f, 0.0f);


	// Adding objects to our scene
	//scene.push_back(plane1);
	scene.push_back(plane2);

	// TODO: CREATE PROPER GRID
	//scene.push_back(grid);
}