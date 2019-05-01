#include "MeshFactory.h"

Mesh MeshFactory::BuildPlaneMesh()
{
    // position of the vertices
    std::vector<GLfloat> vertices = {
            -0.5f, 0.5f, 0.0f, // Top-left
            0.5f, 0.5f, 0.0f, // Top-right
            0.5f, -0.5f, 0.0f, // Bottom-right
            -0.5f, -0.5f, 0.0f // Bottom-left
    };

    // drawing indices/order of the vertices
    std::vector<GLint> indices = {
            0, 1, 2,
            2, 3, 0
    };

    return Mesh(vertices, indices);
}

Mesh MeshFactory::BuildCubeMesh()
{
    // position of the vertices
    std::vector<GLfloat> vertices = {
            // front
            -1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0
    };

    // drawing indices/order of the vertices
    std::vector<GLint> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    return Mesh(vertices, indices);
}
