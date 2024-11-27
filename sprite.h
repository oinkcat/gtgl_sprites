#ifndef SPRITE_H
#define SPRITE_H

#include <QVector2D>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QImage>
#include <QOpenGLTexture>

struct SpriteVertexData
{
    QVector2D pos;
    QVector2D texcoord;
};

class Sprite : protected QOpenGLFunctions
{
public:
    Sprite(QString path);
    ~Sprite();

    QVector2D position() const { return pos; }
    void setPosition(float x, float y) { pos = QVector2D(x, y); }

    float rotation() const { return rot; }
    void setRotation(float angle) { rot = angle; }

    void render(QOpenGLShaderProgram &program, QMatrix4x4 &proj);

private:
    const int NUM_VERTICES = 6;
    const float SIZE_DIVISOR = 5.0f;

    QString texturePath;

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLTexture texture;

    QVector2D pos;
    float rot;

    void constructGeometry();
};

#endif // SPRITE_H
