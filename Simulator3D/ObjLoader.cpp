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


#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "ObjLoader.h"
 /*
bool loadOBJ(
    const std::string& path,
    std::vector<float>& outVertices,
    std::vector<unsigned int>& outIndices)
{
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line))
    {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        char type;
        ss >> type;

        if (type == 'v')
        {
            float x, y, z, r, g, b, a;
            ss >> x >> y >> z >> r >> g >> b >> a;
            outVertices.push_back(x);
            outVertices.push_back(y);
            outVertices.push_back(z);
            outVertices.push_back(r);
            outVertices.push_back(g);
            outVertices.push_back(b);
            outVertices.push_back(a);
        }
        else if (type == 'f')
        {
            unsigned int a, b, c;
            ss >> a >> b >> c;
            outIndices.push_back(a);
            outIndices.push_back(b);
            outIndices.push_back(c);
        }
    }
    return true;
}

*/


bool loadOBJ(
    const std::string& path,
    std::vector<float>& outVertices,
    std::vector<unsigned int>& outIndices)
{
    std::ifstream file(path);
    if (!file.is_open()) return false;

    std::vector<float> tempPositions;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;

            // Add position
            tempPositions.push_back(x);
            tempPositions.push_back(y);
            tempPositions.push_back(z);

            // Add DEFAULT color (white)
            tempPositions.push_back(1.0f);
            tempPositions.push_back(1.0f);
            tempPositions.push_back(1.0f);
            tempPositions.push_back(1.0f);
        }
        else if (type == "f")
        {
            unsigned int a, b, c;
            ss >> a >> b >> c;

            outIndices.push_back(a - 1);
            outIndices.push_back(b - 1);
            outIndices.push_back(c - 1);
        }
    }

    outVertices = tempPositions;
    return true;
}