#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new GraphicsWidget(this);
    setCentralWidget(glWidget);

    SetupWindow();
}

MainWindow::~MainWindow()
{
}

void MainWindow::SetupWindow()
{
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("Test OpenGL Sprites");

    auto app = qobject_cast<QApplication*>(QApplication::instance());
    QSize desktopSize = app->desktop()->size();
    move((desktopSize.width() - WIDTH) / 2, (desktopSize.height() - HEIGHT) / 2);
}
