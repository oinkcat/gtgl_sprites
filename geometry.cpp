#include "geometry.h"

Geometry::Geometry() : indicesBuf(QOpenGLBuffer::Type::IndexBuffer)
{
    initializeOpenGLFunctions();

    attrsBuf.create();
    indicesBuf.create();
}

Geometry::~Geometry()
{
    attrsBuf.destroy();
    indicesBuf.destroy();
}

void Geometry::setPosition(QVector3D newPos)
{
    pos = newPos;
}

QVector3D Geometry::position() const
{
    return pos;
}

void Geometry::updateRotation()
{
    rotationAngle += 1.0f;
}

void Geometry::createBuffers(QVector<VertexData> &vertices, QVector<GLushort> &indices)
{
    attrsBuf.bind();
    attrsBuf.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

    indicesBuf.bind();
    indicesBuf.allocate(indices.data(), indices.size() * sizeof(GLushort));

    numIndices = indices.size();
}

void Geometry::render(QOpenGLShaderProgram *program)
{
    attrsBuf.bind();
    indicesBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Vertex positions
    int vertexLocation = program->attributeLocation("a_pos"); // !
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    // Texture coordinates
    int texcoordLocation = program->attributeLocation("a_normal"); // !
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    // Vertex colors
    int colorLocation = program->attributeLocation("a_color"); // !
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}
