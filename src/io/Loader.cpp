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


#include "simulator/io/Loader.h"
#include "simulator/io/ObjLoader.h"

Loader::Loader() {}

void Loader::LoadScene(std::vector<Renderable>& scene)
{
    // -------- AIRPLANE --------
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Use proper .obj file
    loadOBJ("assets/models/airplane.obj", vertices, indices);

    Mesh* planeMesh = new Mesh(vertices, indices, indices.size());

    // -------- RENDERABLES --------
    Renderable plane = Renderable(planeMesh, GL_TRIANGLES);
    Renderable plane2 = Renderable(planeMesh, GL_TRIANGLES);

    // -------- SCENE --------
    scene.push_back(plane);



    // -------- GRID ---------
    float gridSize = 1.0f;      // distance between grid lines
    int gridCount = 200;         // number of lines in each direction

    std::vector<float> verticesGrid;
    std::vector<unsigned int> indicesGrid;

    for (int i = 0; i <= gridCount; ++i) {
        for (int j = 0; j <= gridCount; ++j) {
            float x = (i - gridCount / 2) * gridSize;
            float z = (j - gridCount / 2) * gridSize;
            float y = -15.0f; // **grid at Y = 0**
            // position (x, y, z) + color RGBA blue
            verticesGrid.push_back(x);
            verticesGrid.push_back(y);
            verticesGrid.push_back(z);
            verticesGrid.push_back(0.05f);
            verticesGrid.push_back(0.05f);
            verticesGrid.push_back(0.1f);
            verticesGrid.push_back(1.0f);
        }
    }

    // now create indices for triangles
    for (int i = 0; i < gridCount; ++i) {
        for (int j = 0; j < gridCount; ++j) {
            int row1 = i * (gridCount + 1);
            int row2 = (i + 1) * (gridCount + 1);

            indicesGrid.push_back(row1 + j);
            indicesGrid.push_back(row2 + j);
            indicesGrid.push_back(row2 + j + 1);

            indicesGrid.push_back(row1 + j);
            indicesGrid.push_back(row2 + j + 1);
            indicesGrid.push_back(row1 + j + 1);
        }
    }

    Mesh* gridMesh = new Mesh(verticesGrid, indicesGrid, indicesGrid.size());
    Renderable grid = Renderable(gridMesh, GL_TRIANGLES);
    grid.SetCoords(0.0f, 0.0f, 0.0f, 0.0f); // **at origin**
    scene.push_back(grid);
}