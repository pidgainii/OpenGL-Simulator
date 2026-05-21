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

#include "simulator/scene/Scene.h"
#include "simulator/scene/Renderable.h"

Loader::Loader() {}


Renderable Loader::LoadTrajectoryLine(int trajectoryType) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    int segments = 200; // How smooth the line is
    float pi = 3.14159265359f;

    for (int i = 0; i <= segments; i++) {
        float t = (2.0f * pi * i) / segments;
        float x = 0.0f, z = 0.0f;

        if (trajectoryType == 0) {
            // Circle Parametric (Swapped for correct 3D orientation)
            float r = 20.0f;
            z = r * cos(t);  // Was x
            x = r * sin(t);  // Was z
        }
        else if (trajectoryType == 1) {
            // Lemniscate Parametric (Swapped for correct 3D orientation)
            float a = 35.0f;
            float scale = a * sqrt(2.0f);
            float denom = sin(t) * sin(t) + 1.0f;

            z = (scale * cos(t)) / denom;           // Was x
            x = (scale * cos(t) * sin(t)) / denom;  // Was z
        }

        // Push Position (x, y, z)
        vertices.push_back(x);
        vertices.push_back(0.1f);
        vertices.push_back(z);


        vertices.push_back(1.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);

        indices.push_back(i);
    }

    Mesh* trajMesh = new Mesh(vertices, indices, indices.size());

    return Renderable(trajMesh, GL_LINE_STRIP);
}

Scene Loader::LoadScene(int nAgents, const std::string& objPath, int selectedTraj)
{
    std::vector<Renderable> scene;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    loadOBJ(objPath.c_str(), vertices, indices);

    Mesh* objMesh = new Mesh(vertices, indices, indices.size());
    Renderable mainObj = Renderable(objMesh, GL_TRIANGLES);

    for (int i = 0; i < nAgents; i++) {
        scene.push_back(mainObj);
    }
    

    // -------- GRID ---------
    float gridSize = 1.0f;      // distance between grid lines
    int gridCount = 200;         // number of lines in each direction

    std::vector<float> verticesGrid;
    std::vector<unsigned int> indicesGrid;

    for (int i = 0; i <= gridCount; ++i) {
        for (int j = 0; j <= gridCount; ++j) {
            float x = (i - gridCount / 2) * gridSize;
            float z = (j - gridCount / 2) * gridSize;
            float y = -0.3f; // **grid at Y = 0**
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


    // Load and add the trajectory line
    Renderable trajectoryLine = LoadTrajectoryLine(selectedTraj);
    scene.push_back(trajectoryLine);


    Scene myScene(scene);

    return myScene;
}

