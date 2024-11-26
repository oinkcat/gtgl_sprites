#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include "graphicswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const int WIDTH = 800;
    const int HEIGHT = 600;

    GraphicsWidget *glWidget;

    void SetupWindow();
};
#endif // MAINWINDOW_H
