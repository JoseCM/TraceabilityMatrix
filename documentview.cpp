#include "documentview.h"
#include "ui_documentview.h"
#include <QDebug>
#include <QDialogButtonBox>

DocumentView::DocumentView(QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentView), QStandardItem(name), name(name)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 0, this);
    labels << "ID" << "Name";
    model->setHorizontalHeaderLabels(labels);
    ui->tableView->setModel(model);
    ui->tableView->header()->setSectionsClickable(true);
    ui->tableView->expandAll();


    QObject::connect(ui->addRowButton, SIGNAL(pressed()), this, SLOT(addRow()));
    QObject::connect(ui->addColumnButton, SIGNAL(pressed()), this, SLOT(addColumn()));
    QObject::connect(ui->delRowButtom, SIGNAL(pressed()), this, SLOT(deleteRow()));
    QObject::connect(ui->delColButtom, SIGNAL(pressed()), this, SLOT(deleteColumn()));
    QObject::connect(ui->subButton, SIGNAL(pressed()), this, SLOT(addSubRowPressed()));

    QObject::connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(dataChanged(QModelIndex,QModelIndex,QVector<int>)));
}

DocumentView::~DocumentView()
{
    delete ui;
}

QTreeView* DocumentView::getTreeView() { return ui->tableView; }

void DocumentView::addEmptyColumn(){

    QStandardItem *item = model->invisibleRootItem();
    QList<QStandardItem*> list;

    if(item->rowCount() > 0){
        for(int i = 0 ; i < item->rowCount(); i++){
         item->child(i)->insertColumns(item->child(i)->columnCount(), 1);
        }
        list << new QStandardItem("");
        item->appendColumn(list);
    }

}

void DocumentView::addColumn(){

    bool ok;
    QString name = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    QStandardItem *item = model->invisibleRootItem();
    QList<QStandardItem*> list;

    if(item->rowCount() > 0){
        for(int i = 0 ; i < item->rowCount(); i++){
            item->child(i)->insertColumns(item->child(i)->columnCount(), 1);
        }
        list << new QStandardItem("");
        item->appendColumn(list);
    }

    labels << name;
    model->setHorizontalHeaderLabels(labels);

}

void DocumentView::addRow(){
    bool ok;

    QStandardItem *item = model->invisibleRootItem();
    QList<QStandardItem*> list;
    list << new QStandardItem(QString::number(item->rowCount() + 1));
    list << new QStandardItem("");
    for(int i = 2; i < model->columnCount(); i++)
        list << new QStandardItem("");
    list.at(0)->setEditable(false);
    item->appendRow(list);
    item->sortChildren(0);
    addRowToDocument(this, item->rowCount() - 1);
    ui->tableView->selectionModel()->selectedColumns(0);
}

void DocumentView::addSubRowPressed(){

    if(ui->tableView->selectionModel()->selectedRows().isEmpty())
        return;

    if(ui->tableView->selectionModel()->currentIndex().parent() != QModelIndex())
            return;

    int row = ui->tableView->selectionModel()->selectedRows().first().row();

    addSubRow(row);
}

void DocumentView::addSubRow(int row){

    QStandardItem *item = model->invisibleRootItem()->child(row,0);
    QList<QStandardItem*> list;

    list << new QStandardItem(item->text() + "." + QString::number(item->rowCount( ) +1 ) );
    for(int i = 1; i < model->columnCount(); i++)
        list << new QStandardItem("");

    list.at(0)->setEditable(false);
    item->appendRow(list);
    item->sortChildren(0);
    QModelIndex temp = item->index();
    addRowToDocument(this, getIndexGlobalRow(temp) + item->rowCount());
    ui->tableView->expandAll();
}


void DocumentView::expand(){
    ui->tableView->expandAll();
}

void DocumentView::deleteRow(){

    QModelIndex index = ui->tableView->selectionModel()->currentIndex();

    if(index == QModelIndex())
        return;

    int row = getIndexGlobalRow(index);
    int count = (index.parent() == QModelIndex() ? model->invisibleRootItem()->child(index.row())->rowCount() : 0);

    model->removeRow(index.row(), index.parent());
    deleteRowOfDocument(this, row, count + 1);
}

int DocumentView::getIndexGlobalRow(QModelIndex &index){

    int count = 0;

   QStandardItem *item = model->itemFromIndex(index);

   qDebug() << "ROOT: " <<  model->invisibleRootItem()->rowCount() << " " << model->invisibleRootItem()->columnCount();
   if(index.parent() == QModelIndex()){
      qDebug() << "top";
       for(int i = 0; i < index.row(); i++){
           count = count + 1 + model->invisibleRootItem()->child(i)->rowCount();
       }
   } else {
       qDebug() << "sub";
       for(int i = 0; i < index.parent().row(); i++)
           count = count + 1  + model->invisibleRootItem()->child(i)->rowCount();
       count =  count + 1 + index.row();
   }

   return count;
}

void DocumentView::deleteColumn(){
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();

    if(index == QModelIndex())
        return;

    model->removeColumn(index.column());
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

QStringList DocumentView::getHeader(){
    QStringList list;
    QStandardItem *base = model->invisibleRootItem();

    for(int i = 0; i< base->rowCount();i++){
        list << base->child(i)->text() + ". " +  base->child(i,1)->text();
        for(int j = 0; j< base->child(i)->rowCount();j++)
            list << "\t\t\t" + base->child(i)->child(j)->text() + ". " +  base->child(i)->child(j,1)->text();
    }
    return list;
}

void DocumentView::dataChanged(QModelIndex,QModelIndex,QVector<int>){
     addRowToDocument(this, -1);
}

QStringList DocumentView::getColumnNames(){

    QStringList columns;
    QAbstractItemModel *model = ui->tableView->model();

    for(int i = 0; i < model->columnCount(); i++)
        columns << model->headerData(i,Qt::Orientation::Horizontal).toString();

    return columns;

}




