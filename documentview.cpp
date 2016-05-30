#include "documentview.h"
#include "ui_documentview.h"

DocumentView::DocumentView(QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentView), QStandardItem(name), name(name)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 0, this);
    labels << "ID";
    model->setHorizontalHeaderLabels(labels);
    //model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("ID"));
    //model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("Name"));
    ui->tableView->setModel(model);

    QObject::connect(ui->addRowButton, SIGNAL(pressed()), this, SLOT(addRow()));
    QObject::connect(ui->addColumnButton, SIGNAL(pressed()), this, SLOT(addColumn()));
    QObject::connect(ui->delRowButtom, SIGNAL(pressed()), this, SLOT(deleteRow()));
    QObject::connect(ui->delColButtom, SIGNAL(pressed()), this, SLOT(deleteColumn()));
    QObject::connect(ui->subButton, SIGNAL(pressed()), this, SLOT(addSubRow()));
}

DocumentView::~DocumentView()
{
    delete ui;
}

void DocumentView::addColumn(){
    bool ok;
    QString name = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    QStandardItem *item = model->invisibleRootItem();
    QList<QStandardItem*> list;
    for(int i = 0 ; i < item->rowCount(); i++)
        item->child(i)->insertColumns(item->child(i)->columnCount(), 1);
    list << new QStandardItem("name");
    item->appendColumn(list);
    labels << name;
    model->setHorizontalHeaderLabels(labels);
}

void DocumentView::addRow(){
    bool ok;
    QStandardItem *item = model->invisibleRootItem();
    QList<QStandardItem*> list;
    list << new QStandardItem("main");
    item->appendRow(list);
}

void DocumentView::addSubRow(){
    QStandardItem *item = model->invisibleRootItem()->child(0,0);
    QList<QStandardItem*> list;
    list << new QStandardItem("sub");
    for(int i = 1; i < model->columnCount(); i++)
        list << new QStandardItem("");
    item->appendRow(list);
    ui->tableView->expandAll();
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
