#include "graphicswidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      eyePos(0.0f, 12.0f, 18.0f),
      lightInitialPos(0.0f, 5.0f, 3.0f),
      time(0.0f)
{
}

void GraphicsWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Resources
    initShaders();
    constructScene();

    // Update timer
    timer.start(UPDATE_INTERVAL, this);
}

void GraphicsWidget::initShaders()
{
    initProgram(objProgram, ":/shaders/obj_vertex.vsh", ":/shaders/obj_fragment.fsh");
    initProgram(spriteProgram, ":/shaders/sprite_vertex.vsh", ":/shaders/sprite_fragment.fsh");
}

void GraphicsWidget::initProgram(QOpenGLShaderProgram &program, QString vertName, QString fragName)
{
    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertName))
    {
        throw "Vertex shader compilation error!";
    }

    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragName))
    {
        throw "Fragment shader compilation error!";
    }

    if(!program.link())
    {
        throw "Shader link error!";
    }
}

void GraphicsWidget::constructScene()
{
    cube = new CubeGeometry();
    cube->setPosition(QVector3D(0.0f, 0.0f, 0.0f));

    testSprite = new Sprite(":/img/test_pic.jpg");
}

void GraphicsWidget::resizeGL(int w, int h)
{
    const qreal zNear = 2.0, zFar = 30.0, fov = 45.0;
    qreal size = 100.0f;

    qreal ratio = (qreal)w / (qreal)h;
    projection.setToIdentity();
    projection.perspective(fov, ratio, zNear, zFar);

    qreal vSize = size;
    qreal hSize = vSize * ratio;
    orthoProjection.setToIdentity();
    orthoProjection.ortho(-hSize, hSize, -vSize, vSize, -2.0, 2.0);
}

void GraphicsWidget::timerEvent(QTimerEvent *event)
{
    const float SPRITE_R = 50.0f;

    Q_UNUSED(event);

    cube->updateRotation();
    update();

    float sX = cos(time) * SPRITE_R;
    float sY = sin(time) * SPRITE_R;
    testSprite->setPosition(sX, sY);

    time += 0.1f;
}

void GraphicsWidget::paintGL()
{
    renderScene();
}

void GraphicsWidget::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera view
    QMatrix4x4 viewMatrix;
    viewMatrix.lookAt(eyePos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    QMatrix4x4 viewProjMatrix = projection * viewMatrix;

    renderSceneObject(viewProjMatrix);
    renderSprite(orthoProjection);
}

// Render rotating cube
void GraphicsWidget::renderSceneObject(QMatrix4x4 &viewProjMatrix)
{
    objProgram.bind();

    QMatrix4x4 cubeRotationMatrix;
    cubeRotationMatrix.rotate(cube->rotation(), 1.0f, 0.75f, 0.5f);

    QMatrix4x4 cubeMatrix;
    cubeMatrix.scale(2.0f);
    cubeMatrix.translate(cube->position());
    cubeMatrix = cubeMatrix * cubeRotationMatrix;
    objProgram.setUniformValue("u_mvp", viewProjMatrix * cubeMatrix);

    // Light for cube
    QMatrix4x4 invCubeRotation = cubeRotationMatrix.inverted();
    objProgram.setUniformValue("u_light", invCubeRotation * lightInitialPos);

    cube->render(&objProgram);
}

// Render 2D sprite
void GraphicsWidget::renderSprite(QMatrix4x4 &projMatrix)
{
    spriteProgram.bind();
    testSprite->render(spriteProgram, projMatrix);
}
