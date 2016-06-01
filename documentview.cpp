#include "documentview.h"
#include "ui_documentview.h"
#include <QDebug>

DocumentView::DocumentView(QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentView), QStandardItem(name), name(name)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 0, this);
    labels << "ID" << "Name";
    model->setHorizontalHeaderLabels(labels);
    //model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("ID"));
    //model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("Name"));
    ui->tableView->setModel(model);

    QObject::connect(ui->addRowButton, SIGNAL(pressed()), this, SLOT(addRow()));
    QObject::connect(ui->addColumnButton, SIGNAL(pressed()), this, SLOT(addColumn()));
    QObject::connect(ui->delRowButtom, SIGNAL(pressed()), this, SLOT(deleteRow()));
    QObject::connect(ui->delColButtom, SIGNAL(pressed()), this, SLOT(deleteColumn()));
    QObject::connect(ui->subButton, SIGNAL(pressed()), this, SLOT(addSubRow()));

    QObject::connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(dataChanged(QModelIndex,QModelIndex,QVector<int>)));
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
    if(item->rowCount() > 0){
        for(int i = 0 ; i < item->rowCount(); i++)
         item->child(i)->insertColumns(item->child(i)->columnCount(), 1);
        list << new QStandardItem("");
        item->appendColumn(list);
    }
    labels << name;
    model->setHorizontalHeaderLabels(labels);
}

void DocumentView::addRow(){
    bool ok;
    QString name = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);

    QStandardItem *item = model->invisibleRootItem();
    QList<QStandardItem*> list;
    list << new QStandardItem(QString::number(item->rowCount() + 1));
    list << new QStandardItem(name);
    item->appendRow(list);
    item->sortChildren(0);
    addRowToDocument(this);
}

void DocumentView::addSubRow(){    

    if(ui->tableView->selectionModel()->selectedRows().isEmpty())
        return;

    int row = ui->tableView->selectionModel()->selectedRows().first().row();

    QStandardItem *item = model->invisibleRootItem()->child(row,0);
    qDebug() << (item->text());
    QList<QStandardItem*> list;

    list << new QStandardItem(item->text() + "." + QString::number(item->rowCount( ) +1 ) );
    for(int i = 1; i < model->columnCount(); i++)
        list << new QStandardItem("");

    item->appendRow(list);
    item->sortChildren(0);
    addRowToDocument(this);
    ui->tableView->expandAll();
}

void DocumentView::deleteRow(){
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    int row = indexes.last().row();
    while (!indexes.isEmpty())
    {
        model->removeRows(row, 1);
        indexes.removeLast();
    }
    deleteRowOfDocument(this, row);
}

void DocumentView::deleteColumn(){
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedColumns();
    while (!indexes.isEmpty())
    {
        model->removeColumns(indexes.last().column(), 1);
        indexes.removeLast();
    }
}

//ISTO LEAKA
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

QStringList DocumentView::getHeader(){
    QStringList list;
    QStandardItem *base = model->invisibleRootItem();

    for(int i = 0; i< base->rowCount();i++){
        list << base->child(i)->text() + " - " +  base->child(i,1)->text();
        for(int j = 0; j< base->child(i)->rowCount();j++)
            list << "\t\t\t" + base->child(i)->child(j)->text() + " - " +  base->child(i)->child(j,1)->text();
    }
    return list;
}

void DocumentView::dataChanged(QModelIndex,QModelIndex,QVector<int>){
     addRowToDocument(this);
}
