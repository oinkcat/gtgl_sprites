#ifndef TEXT_H
#define TEXT_H

#include <QVector>
#include <QImage>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

struct TextVertexData
{
    QVector2D pos;
    QVector2D texcoord;
};

class Text : protected QOpenGLFunctions
{
public:

    enum LetterSpacing {
        Narrow,
        Normal,
        Wide
    };

    Text(QString text);

    QString text() const { return textString; }
    void setText(QString newText);

    void render(QOpenGLShaderProgram &program, QMatrix4x4 &proj);

private:
    const int NUM_ROWS = 16;
    const int NUM_COLS = 16;
    const int NUM_VERTICES_PER_QUAD = 6;

    const float ROW_STEP = 1.0f / (float)NUM_ROWS;
    const float COL_STEP = 1.0f / (float)NUM_COLS;
    const float CHAR_SIZE = 8.0f;

    const char *fontFileName = ":/imgs/test_font.png";

    QString textString;
    LetterSpacing spacing;

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLTexture texture;

    int numIndices;

    QVector2D topLeft;

    void reCreateTextVertices();
    void addCharVertices(QChar qc, QVector<TextVertexData> &vertices);

    float getLetterWidth();
};

#endif // TEXT_H
