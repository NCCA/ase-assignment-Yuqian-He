#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_gl = new NGLScene();
    ui->mainWindowGridLayout->addWidget(m_gl,0,1,2,2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
    m_gl->keyPressEvent(_event);
}
