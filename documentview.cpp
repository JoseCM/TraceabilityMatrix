#include "documentview.h"
#include "ui_documentview.h"

DocumentView::DocumentView(QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentView), name(name)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 0, this);
    model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("ID"));
    model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("Name"));
    ui->tableView->setModel(model);

    QObject::connect(ui->addRowButton, SIGNAL(pressed()), this, SLOT(addRow()));
    QObject::connect(ui->addColumnButton, SIGNAL(pressed()), this, SLOT(addColumn()));
    QObject::connect(ui->delRowButtom, SIGNAL(pressed()), this, SLOT(deleteRow()));
    QObject::connect(ui->delColButtom, SIGNAL(pressed()), this, SLOT(deleteColumn()));
}

DocumentView::~DocumentView()
{
    delete ui;
}

void DocumentView::addColumn(){
    bool ok;
    QString name = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem(name));
}

void DocumentView::addRow(){
    bool ok;
    // model->insertRow(model->rowCount(), new QStandardItem(""));
    QString name = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    model->setVerticalHeaderItem(model->rowCount(), new QStandardItem(name));
}

void DocumentView::deleteRow(){
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    while (!indexes.isEmpty())
    {
        model->removeRows(indexes.last().row(), 1);
        indexes.removeLast();
    }
}

void DocumentView::deleteColumn(){
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedColumns();
    while (!indexes.isEmpty())
    {
        model->removeColumns(indexes.last().column(), 1);
        indexes.removeLast();
    }
}

void DocumentView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        msgBox = new QMessageBox();
        msgBox->setWindowTitle("Hello");
        msgBox->setText("You Clicked Right Mouse Button");
        msgBox->show();
    }
}
