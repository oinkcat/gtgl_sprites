#include "text.h"

Text::Text(QString text)
    : textString(text),
      spacing(LetterSpacing::Narrow),
      indexBuffer(QOpenGLBuffer::Type::IndexBuffer),
      texture(QOpenGLTexture::Target::Target2D)
{
    const QOpenGLTexture::Filter FILTER = QOpenGLTexture::Filter::Nearest;

    initializeOpenGLFunctions();

    vertexBuffer.create();
    indexBuffer.create();

    texture.setData(QImage(fontFileName));
    texture.setMinMagFilters(FILTER, FILTER);

    reCreateTextVertices();
}

void Text::reCreateTextVertices()
{
    QVector<TextVertexData> vertices;
    QVector<GLushort> indices;

    // float cw = getLetterWidth();
    topLeft = QVector2D(0.0f, 0.0f); // QVector2D(-textString.length() / 2 * cw, CHAR_SIZE / 2.0f);

    for(QChar c : textString) {
        int n = vertices.size();

        addCharVertices(c, vertices);

        indices << n << n + 1 << n + 2;
        indices << n + 1 << n + 3 << n + 2;
    }

    numIndices = indices.size();

    vertexBuffer.bind();
    vertexBuffer.allocate(vertices.data(), sizeof(TextVertexData) * vertices.size());

    indexBuffer.bind();
    indexBuffer.allocate(indices.data(), sizeof(GLushort) * indices.size());
}

void Text::addCharVertices(QChar qc, QVector<TextVertexData> &vertices)
{
    int charIdx = vertices.size() / 4;
    char c = qc.toLatin1();

    float cw = getLetterWidth();
    float ncw = cw / CHAR_SIZE;

    float vX = charIdx * cw + topLeft.x();
    float vY = topLeft.y();

    int rowIdx = c / NUM_COLS;
    int colIdx = c % NUM_COLS;

    float tX = colIdx * COL_STEP;
    float tY = rowIdx * COL_STEP;

    vertices << TextVertexData { {vX, vY}, {tX, tY} }
             << TextVertexData { {vX + cw, vY}, {tX + COL_STEP * ncw, tY} }
             << TextVertexData { {vX, vY + CHAR_SIZE}, {tX, tY + ROW_STEP} }
             << TextVertexData { {vX + cw, vY + CHAR_SIZE}, {tX + COL_STEP * ncw, tY + ROW_STEP} };
}

float Text::getLetterWidth()
{
    switch(spacing)
    {
    case LetterSpacing::Narrow:
        return CHAR_SIZE * 0.65f;
    case LetterSpacing::Normal:
        return CHAR_SIZE * 0.85f;
    default:
        return CHAR_SIZE;
    }
}

void Text::setText(QString newText)
{
    if(textString.compare(newText) != 0) {
        textString = newText;

        vertexBuffer.release();
        indexBuffer.release();
        reCreateTextVertices();
    }
}

void Text::render(QOpenGLShaderProgram &program, QMatrix4x4 &proj)
{
    // Transforms
    QMatrix4x4 transforms;
    transforms.setToIdentity();
    //transforms.rotate(rot, 0.0f, 0.0f, 1.0f);
    //transforms.translate(pos.x(), pos.y(), 0.0f);
    program.setUniformValue("u_mvp", proj * transforms);

    // Texture
    texture.bind();
    program.setUniformValue("u_texture", 0);
    program.setUniformValue("u_keyed", true);

    // Geometry
    vertexBuffer.bind();
    indexBuffer.bind();

    int offset = 0;

    // Vertex position
    int vertexLocation = program.attributeLocation("a_pos"); // !
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 2, sizeof(TextVertexData));

    offset += sizeof(QVector2D);

    // Texture coordinate
    int texcoordLocation = program.attributeLocation("a_texcoord"); // !
    program.enableAttributeArray(texcoordLocation);
    program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(TextVertexData));

    // Draw
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}
