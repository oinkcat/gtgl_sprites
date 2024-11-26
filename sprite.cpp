#include "sprite.h"

Sprite::Sprite(QString path)
    : texturePath(path),
      indexBuffer(QOpenGLBuffer::Type::IndexBuffer),
      texture(QOpenGLTexture::Target::Target2D)
{
    initializeOpenGLFunctions();

    vertexBuffer.create();
    indexBuffer.create();

    constructGeometry();
}

Sprite::~Sprite()
{
    texture.destroy();
    vertexBuffer.destroy();
    indexBuffer.destroy();
}

void Sprite::constructGeometry()
{
    QImage textureImage = QImage(texturePath).mirrored();
    float halfWidth = textureImage.width() / SIZE_DIVISOR / 2;
    float halfHeight = textureImage.height() / SIZE_DIVISOR / 2;

    texture.setData(textureImage);

    SpriteVertedData vertices[] = {
        {{-halfWidth, -halfHeight}, {0.0f, 0.0f}},
        {{halfWidth, -halfHeight}, {1.0f, 0.0f}},
        {{-halfWidth, halfHeight}, {0.0f, 1.0f}},
        {{halfWidth, halfHeight}, {1.0f, 1.0f}}
    };

    GLushort indices[] = {0, 1, 2, 1, 3, 2};

    vertexBuffer.bind();
    vertexBuffer.allocate(vertices, sizeof(vertices));

    indexBuffer.bind();
    indexBuffer.allocate(indices, sizeof(indices));
}

void Sprite::render(QOpenGLShaderProgram &program, QMatrix4x4 &proj)
{
    // Transforms
    QMatrix4x4 transforms;
    transforms.setToIdentity();
    transforms.translate(pos.x(), pos.y(), 0.0f);
    program.setUniformValue("u_mvp", proj * transforms);

    // Texture
    texture.bind();
    program.setUniformValue("u_texture", 0);

    // Geometry
    vertexBuffer.bind();
    indexBuffer.bind();

    int offset = 0;

    // Vertex position
    int vertexLocation = program.attributeLocation("a_pos"); // !
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 2, sizeof(SpriteVertedData));

    offset += sizeof(QVector2D);

    // Texture coordinate
    int texcoordLocation = program.attributeLocation("a_texcoord"); // !
    program.enableAttributeArray(texcoordLocation);
    program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(SpriteVertedData));

    // Draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
