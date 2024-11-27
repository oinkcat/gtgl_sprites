#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

struct VertexData
{
    QVector3D pos;
    QVector3D normal;
    QVector3D color;
};

class Geometry : protected QOpenGLFunctions
{
public:
    Geometry();
    ~Geometry();

    virtual void construct() = 0;

    void setPosition(QVector3D newPos);
    QVector3D position() const { return pos; }

    float rotation() const { return rotationAngle; }

    void updateRotation();
    void render(QOpenGLShaderProgram *program);

protected:
    void createBuffers(QVector<VertexData>& vertices, QVector<GLushort>& indices);

    int numIndices;

    QOpenGLBuffer attrsBuf;
    QOpenGLBuffer indicesBuf;

    QVector3D pos;
    float rotationAngle;
};

#endif // GEOMETRY_H
