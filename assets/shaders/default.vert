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




// shaders are functions that will run on GPU, written in glsl language.

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 color;

void main()
{
	// Coordinates are actually 4d. It's complex
	// For now we'll just add 1.0
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	color = aColor;
}