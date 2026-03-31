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



#include "simulator/graphics/VAO.h"


VAO::VAO() {
	glGenVertexArrays(1, &vao);
}


void VAO::Bind()
{
	glBindVertexArray(vao);
}
void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::LoadAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &vao);
}