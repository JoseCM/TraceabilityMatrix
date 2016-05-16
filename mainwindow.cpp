#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(2, 2, this);
    ui->tableView->setModel(model);

    QObject::connect(ui->addDocButton, SIGNAL(pressed()), this, SLOT(addNewTab()));

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Coluna 1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Coluna 2")));
    model->setVerticalHeaderItem(0, new QStandardItem(QString("Linha 1")));
    model->setVerticalHeaderItem(1, new QStandardItem(QString("Linha 2")));
}

void MainWindow::addNewTab(){

    bool ok;
    QString text = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    if (ok && !text.isEmpty())
        ui->tabWidget->addTab(new DocumentView(this), text);
}

MainWindow::~MainWindow()
{
    delete ui;
}
