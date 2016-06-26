#include "traceabilityview.h"
#include "ui_traceabilityview.h"
#include <QDebug>
#include <QHeaderView>
#include <QDomDocument>
#include <QDir>

TraceabilityView::TraceabilityView(DocumentView* requirements,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TraceabilityView)
{
    ui->setupUi(this);
    this->requirements = requirements;
    QObject::connect(requirements, SIGNAL(addRowToDocument(DocumentView*, int)), this, SLOT(addRowToDocument(DocumentView*, int)));
    QObject::connect(requirements, SIGNAL(deleteRowOfDocument(DocumentView*,int,int)), this, SLOT(deleteRowOfDocument(DocumentView*,int,int)));
    model = nullptr;

    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->verticalHeader()->setFixedWidth(100);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::);

    del = new CheckBoxDelegate(this);
    ui->tableView->setItemDelegate(del);


    ui->noteEdit->setReadOnly(true);

    ui->tableView->horizontalHeader()->setVisible(true);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView->verticalHeader()->setSectionsClickable(false);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //ui->tableView->selectAll();

    ui->comboBox->setModel(&otherDocsModel);
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedDocumentChanged(int)));

    ui->reqList->setModel(&reqListModel);
    ui->preReq->setModel(&preReqModel);
    ui->postReq->setModel(&postReqModel);

    QObject::connect(ui->reqList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateTrace(QModelIndex)));
    QObject::connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    QObject::connect(ui->tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(itemSelected(QModelIndex)));
    previous = nullptr;

}

 QStandardItemModel* TraceabilityView::loadMatrix(QString name){

    QFile file(name);

    QStandardItemModel* model = new QStandardItemModel();

    if (file.open(QIODevice::ReadOnly))
    {
       QDataStream stream(&file);
        qint32 n, m;
        stream >> n >> m;
        model->setRowCount(n);
        model->setColumnCount(m);

        for (int i = 0; i < n ; ++i) {
               for (int j = 0; j < m; j++) {
                   QStandardItem *item = new QStandardItem;
                   item->read(stream);
                   model->setItem(i, j, item);
               }
           }

     file.close();
    }

    //ui->tableView->setModel(model);
    return model;
     qDebug() << "Matrix loaded: " << name;
}

const void TraceabilityView::saveMatrix(QString name, QStandardItemModel *model){

    QFile file(name);

     if (file.open(QIODevice::WriteOnly))
     {
         QDataStream stream(&file);
         qint32 n = model->rowCount();
         qint32 m = model->columnCount();
         stream << n << m;

         for (int i=0; i<n; ++i)
         {
          for (int j=0; j<m; j++)
            {
              if(model->item(i,j))
                model->item(i,j)->write(stream);
              else
                (new QStandardItem())->write(stream);
            }
          }
        file.close();
      }

    qDebug() << "Matrix saved: " << name;
}

void TraceabilityView::itemSelected(const QModelIndex &current){
    qDebug() << "Select: " << current.row() << " " << current.column();

    if(previous != nullptr){
        previous->setAccessibleText(ui->noteEdit->toPlainText());
    }

    previous = model->itemFromIndex(current);

    ui->noteEdit->setReadOnly(false);
    ui->noteEdit->clear();
    ui->noteEdit->setPlainText(model->itemFromIndex(current)->accessibleText());


}


void TraceabilityView::tabChanged(int i){

    if(i == 1)
        updateTrace(QModelIndex());

    ui->noteEdit->setReadOnly(true);
}

void TraceabilityView::updateTrace(QModelIndex index){

    int row = ui->reqList->currentIndex().row();
    qDebug() << "update trace row: " << row;
    if(row < 0)
        return;

    QList<QStandardItemModel*> list = traceModelList.values();
    preReqModel.clear();
    postReqModel.clear();

    for(int i = 0; i < list.size(); i++){

            QStringList listheader = traceModelList.keys().at(i)->getHeader();
            int column = list[i]->columnCount();
            for(int j = 0; j < column; j++){
                QStandardItem* item = list.at(i)->item(row, j);
                if(!item)
                    continue;
                if(item->data(Qt::EditRole).toInt() == 1){
                   QStandardItem *subitem = new QStandardItem(traceModelList.keys().at(i)->text() + " - " + traceModelList.keys().at(i)->getHeader().at(j).trimmed());
                   subitem->setToolTip(item->accessibleText());
                   preReqModel.insertRow(preReqModel.rowCount(), subitem);
                }
                else if(item->data(Qt::EditRole).toInt() == 2){
                   QStandardItem *subitem = new QStandardItem(traceModelList.keys().at(i)->text() + " - " + traceModelList.keys().at(i)->getHeader().at(j).trimmed()) ;
                   subitem->setToolTip(item->accessibleText());
                   postReqModel.insertRow(postReqModel.rowCount(), subitem);
                }
            }
    }

}

void TraceabilityView::addModels(DocumentView *item, QStandardItemModel *model){

    otherDocsModel.setItem(otherDocsModel.rowCount(), item);
    if(model == nullptr)
        model = new QStandardItemModel();
    model->setVerticalHeaderLabels(requirements->getHeader());
    traceModelList.insert(item, model);
    //noteModel.append(new QStandardItemModel());
    QObject::connect(item, SIGNAL(addRowToDocument(DocumentView*, int)), this, SLOT(addRowToDocument(DocumentView*, int)));
    QObject::connect(item, SIGNAL(deleteRowOfDocument(DocumentView*,int, int)), this, SLOT(deleteRowOfDocument(DocumentView*,int, int)));
    if(this->model == nullptr){
        this->model = model;
        ui->tableView->setModel(model);
        ui->comboBox->setCurrentIndex(0);

    }
}

void TraceabilityView::addRowToDocument(DocumentView *item, int row){

    if(item == requirements){
        QList<QStandardItemModel*> list = traceModelList.values();
        for(int i = 0; i < list.size(); i++){
                if(row >= 0){
                    list[i]->insertRow(row);
                    //noteModel[i]->insertRow(row, new QStandardItem());
                }
                list[i]->setVerticalHeaderLabels(requirements->getHeader());
        }
          reqListModel.clear();
          for(QString str : requirements->getHeader()){
              QStandardItem *tempitem = new QStandardItem(str.trimmed());
              tempitem->setEditable(false);
              reqListModel.insertRow(reqListModel.rowCount(), tempitem);
          }
        return;
    }

    QStandardItemModel *model = traceModelList.value(item);
    if(row >= 0){
        model->insertColumn(row);
     //   noteModel.insertRow(noteModel.rowCount(), new QStandardItem());
    }
    model->setHorizontalHeaderLabels(item->getHeader());
}

void TraceabilityView::updateReqListModel(){
    reqListModel.clear();
    for(QString str : requirements->getHeader()){
        QStandardItem *tempitem = new QStandardItem(str.trimmed());
        tempitem->setEditable(false);
        reqListModel.insertRow(reqListModel.rowCount(), tempitem);
    }
}

void TraceabilityView::deleteRowOfDocument(DocumentView *item, int row, int count){

    if(item == requirements){
        QList<QStandardItemModel*> list = traceModelList.values();
        for(int i = 0; i < list.size(); i++)
                list[i]->removeRows(row, count);
        reqListModel.removeRows(row, count);
        return;
    }

    QStandardItemModel *model = traceModelList.value(item);
    model->removeColumns(row, count);

}

void TraceabilityView::selectedDocumentChanged(int index){

    DocumentView *item = static_cast<DocumentView*> (otherDocsModel.item(index));
    QStandardItemModel *model = traceModelList.value(item);

    this->model = model;
    ui->tableView->setModel(model);
}

void TraceabilityView::removeDocument(int index){

    QStandardItem *item = otherDocsModel.item(index);
    otherDocsModel.removeRow(index);

    traceModelList.remove(static_cast<DocumentView*>(item));
}

void TraceabilityView::setMatrixModel(QStandardItemModel *model){
    this->model = model;
    ui->tableView->setModel(model);
}

TraceabilityView::~TraceabilityView()
{
    delete ui;
}
