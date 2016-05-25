#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    editor = new DocumentEditorView(this);
    editor->hide();
    traceability = new TraceabilityView(this);
    ui->horizontalLayout->addWidget(traceability, 10, Qt::AlignRight);

}


MainWindow::~MainWindow()
{
    delete ui;
}
