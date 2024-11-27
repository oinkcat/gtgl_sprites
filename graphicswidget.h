#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QBasicTimer>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <math.h>

#include "cubegeometry.h"
#include "sprite.h"
#include "text.h"

class GraphicsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GraphicsWidget(QWidget *parent);

    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;

private:
    const int UPDATE_INTERVAL = 20;
    const float IMG_VIEW_WIDTH = 200.0f;

    QBasicTimer timer;

    QVector2D imgViewSize;

    float time;

    QVector3D eyePos;
    QVector3D lightPos;

    QMatrix4x4 projection;
    QMatrix4x4 orthoProjection;

    QOpenGLShaderProgram objProgram;
    QOpenGLShaderProgram spriteProgram;

    Geometry *cube;
    Sprite *testSprite;
    Text *testText;

    void initShaders();
    void initProgram(QOpenGLShaderProgram &program, QString vertName, QString fragName);
    void constructScene();

    void renderScene();
    void renderSceneObject(QMatrix4x4 &viewProjMatrix);
    void renderSprite(QMatrix4x4 &projMatrix);
    void renderText(QMatrix4x4 &projMatrix);
};

#endif // GRAPHICSWIDGET_H
