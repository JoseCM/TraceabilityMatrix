#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    editor = new DocumentEditorView(this);
    editor->hide();
    QString *str = new QString("Requirements Document");
    requirements = new DocumentView(*str, this);
    requirements->hide();
    traceability = new TraceabilityView(requirements, this);
    ui->centralWidget->layout()->addWidget(traceability);

    QObject::connect(ui->showReq, SIGNAL(pressed()), this, SLOT(showRequirements()));
    QObject::connect(ui->showEdit, SIGNAL(pressed()), this, SLOT(showEditor()));
    QObject::connect(ui->showTrace, SIGNAL(pressed()), this, SLOT(showTraceability()));
    QObject::connect(editor, SIGNAL(docAdded(DocumentView*)), traceability, SLOT(addModels(DocumentView*)));

}

void MainWindow::showEditor(){
    ui->centralWidget->layout()->removeWidget(traceability);
    traceability->hide();
    ui->centralWidget->layout()->removeWidget(requirements);
    requirements->hide();
    ui->centralWidget->layout()->addWidget(editor);
    editor->show();
}

void MainWindow::showTraceability(){

    ui->centralWidget->layout()->removeWidget(editor);
    editor->hide();
    ui->centralWidget->layout()->removeWidget(requirements);
    requirements->hide();
    ui->centralWidget->layout()->addWidget(traceability);
    traceability->show();
}

void MainWindow::showRequirements(){
    ui->centralWidget->layout()->removeWidget(traceability);
    traceability->hide();
    ui->centralWidget->layout()->removeWidget(editor);
    editor->hide();
    ui->centralWidget->layout()->addWidget(requirements);
    requirements->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        msgBox = new QMessageBox();
        msgBox->setWindowTitle("Hello");
        msgBox->setText("You Clicked Right Mouse Button");
        msgBox->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
