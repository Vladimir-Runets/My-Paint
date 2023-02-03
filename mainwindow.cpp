#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget.h"
#include <QColorDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainwidget= new widget();

    setCentralWidget(mainwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    QColor color = QColorDialog::getColor(Qt::gray, this);
    mainwidget->setColor(color);
}

void MainWindow::on_action_2_triggered()
{
    bool ok;
    int thickness = QInputDialog::getInt(this, tr("QInputDialog::getInt()"), tr("Введите толщину линии:"), 3, 1, 100, 1, &ok);
    if (ok && 1<=thickness) {mainwidget->setThickness(thickness);}
}
