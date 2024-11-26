#include "cubegeometry.h"

CubeGeometry::CubeGeometry() : Geometry()
{
    construct();
}

void CubeGeometry::construct()
{
    // Geometry data
    QVector3D colors[] = {
        QVector3D(1.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 1.0f, 0.0f),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector3D(1.0f, 1.0f, 0.0f),
        QVector3D(1.0f, 0.0f, 1.0f),
        QVector3D(0.0f, 1.0f, 1.0f)
    };

    QVector<VertexData> vertices = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f, 0.0f, 1.0f), colors[0]}, // v0
        {QVector3D(1.0f, -1.0f,  1.0f), QVector3D(0.0f, 0.0f, 1.0f), colors[0]}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f, 0.0f, 1.0f), colors[0]}, // v2
        {QVector3D(1.0f,  1.0f,  1.0f), QVector3D(0.0f, 0.0f, 1.0f), colors[0]}, // v3

        // Vertex data for face 1
        {QVector3D(1.0f, -1.0f,  1.0f), QVector3D(1.0f, 0.0f, 0.0f), colors[1]}, // v4
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f), colors[1]}, // v5
        {QVector3D(1.0f,  1.0f,  1.0f), QVector3D(1.0f, 0.0f, 0.0f), colors[1]},  // v6
        {QVector3D(1.0f,  1.0f, -1.0f), QVector3D(1.0f, 0.0f, 0.0f), colors[1]}, // v7

        // Vertex data for face 2
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), colors[2]}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), colors[2]},  // v9
        {QVector3D(1.0f,  1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), colors[2]}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f, 0.0f, -1.0f), colors[2]},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(-1.0f, 0.0f, 0.0f), colors[3]}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(-1.0f, 0.0f, 0.0f), colors[3]},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(-1.0f, 0.0f, 0.0f), colors[3]}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(-1.0f, 0.0f, 0.0f), colors[3]},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f), colors[4]}, // v16
        {QVector3D(1.0f, -1.0f, -1.0f), QVector3D(0.0f, -1.0f, 0.0f), colors[4]}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f, -1.0f, 0.0f), colors[4]}, // v18
        {QVector3D(1.0f, -1.0f,  1.0f), QVector3D(0.0f, -1.0f, 0.0f), colors[4]}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f, 1.0f, 0.0f), colors[5]}, // v20
        {QVector3D(1.0f,  1.0f,  1.0f), QVector3D(0.0f, 1.0f, 0.0f), colors[5]}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f), colors[5]}, // v22
        {QVector3D(1.0f,  1.0f, -1.0f), QVector3D(0.0f, 1.0f, 0.0f), colors[5]}  // v23
    };

    QVector<GLushort> indices = {
        0, 1, 2, 1, 3, 2,       // Face 0 - triangles ( v0,  v1,  v2,  v3)
        4, 5, 6, 5, 7, 6,       // Face 1 - triangles ( v4,  v5,  v6,  v7)
        8, 9, 10, 9, 11, 10,    // Face 2 - triangles ( v8,  v9, v10, v11)
        12, 13, 14, 13, 15, 14, // Face 3 - triangles (v12, v13, v14, v15)
        16, 17, 18, 17, 19, 18, // Face 4 - triangles (v16, v17, v18, v19)
        20, 21, 22, 21, 23, 22  // Face 5 - triangles (v20, v21, v22, v23)
    };

    createBuffers(vertices, indices);
}

