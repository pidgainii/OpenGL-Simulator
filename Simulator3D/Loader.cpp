#include "Loader.h"
#include "ObjLoader.h"

Loader::Loader() {}

void Loader::LoadScene(std::vector<Renderable>& scene)
{
    // -------- AIRPLANE --------
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // Use proper .obj file
    loadOBJ("airplane.obj", vertices, indices);

    Mesh* planeMesh = new Mesh(vertices, indices, indices.size());

    // -------- RENDERABLES --------
    Renderable plane = Renderable(planeMesh, GL_TRIANGLES, 0.0f, 0.0f, 0.1f);
    Renderable plane2 = Renderable(planeMesh, GL_TRIANGLES, 0.0f, 0.0f, 0.15f);

    // -------- SCENE --------
    scene.push_back(plane);
    scene.push_back(plane2);
}