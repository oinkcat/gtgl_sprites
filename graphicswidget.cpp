#include "graphicswidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      time(0.0f),
      eyePos(0.0f, 12.0f, 18.0f),
      lightPos(5.0f, 5.0f, 5.0f)
{
}

void GraphicsWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    testSprite = new Sprite(":/imgs/test_alpha.png");

    testText = new Text("Hello World!");
}

void GraphicsWidget::resizeGL(int w, int h)
{
    const qreal zNear = 2.0, zFar = 30.0, fov = 45.0;

    qreal ratio = (qreal)w / (qreal)h;
    projection.setToIdentity();
    projection.perspective(fov, ratio, zNear, zFar);

    qreal vSize = IMG_VIEW_WIDTH;
    qreal hSize = vSize * ratio;
    imgViewSize = QVector2D(hSize, vSize);

    orthoProjection.setToIdentity();
    orthoProjection.ortho(0, hSize, vSize, 0, -2.0, 2.0);
}

void GraphicsWidget::timerEvent(QTimerEvent *event)
{
    const float SPRITE_R = 50.0f;

    Q_UNUSED(event);

    cube->updateRotation();

    float sX = cos(time) * SPRITE_R + imgViewSize.x() / 2;
    float sY = sin(time) * SPRITE_R + imgViewSize.y() / 2;
    testSprite->setPosition(sX, sY);
    testSprite->setRotation(time * 15.0f);

    testText->setText(QString("Rotation: %1").arg(cube->rotation()));

    time += 0.1f;

    update();
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


    glEnable(GL_DEPTH_TEST);
    renderSceneObject(viewProjMatrix);

    glDisable(GL_DEPTH_TEST);
    renderSprite(orthoProjection);
    renderText(orthoProjection);
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
    QMatrix4x4 invCubeTransform = cubeMatrix.inverted();
    objProgram.setUniformValue("u_light", invCubeTransform * lightPos);

    cube->render(&objProgram);
}

// Render 2D sprite
void GraphicsWidget::renderSprite(QMatrix4x4 &projMatrix)
{
    spriteProgram.bind();
    testSprite->render(spriteProgram, projMatrix);
}

// Render 2D text
void GraphicsWidget::renderText(QMatrix4x4 &projMatrix)
{
    spriteProgram.bind();
    testText->render(spriteProgram, projMatrix);
}
