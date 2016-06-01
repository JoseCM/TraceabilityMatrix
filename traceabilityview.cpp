#include "traceabilityview.h"
#include "ui_traceabilityview.h"
#include <QDebug>

TraceabilityView::TraceabilityView(DocumentView* requirements,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TraceabilityView)
{
    ui->setupUi(this);
    this->requirements = requirements;
    QObject::connect(requirements, SIGNAL(addRowToDocument(DocumentView*)), this, SLOT(addRowToDocument(DocumentView*)));
    QObject::connect(requirements, SIGNAL(deleteRowOfDocument(DocumentView*,int)), this, SLOT(deleteRowOfDocument(DocumentView*,int)));
    model = nullptr;

    ui->tableView->setModel(model);

    QItemDelegate* del = new CheckBoxDelegate(this);
    ui->tableView->setItemDelegate(del);
    ui->tableView->horizontalHeader()->setVisible(true);

//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Coluna 1")));
//    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Coluna 2")));
//    model->setVerticalHeaderItem(0, new QStandardItem(QString("Linha 1")));
//    model->setVerticalHeaderItem(1, new QStandardItem(QString("Linha 2")));

    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->comboBox->setModel(&otherDocsModel);

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedDocumentChanged(int)));
}

void TraceabilityView::addModels(DocumentView *item){

    otherDocsModel.setItem(otherDocsModel.rowCount(), item);
    QStandardItemModel *model = new QStandardItemModel();
    model->setVerticalHeaderLabels(requirements->getHeader());
    traceModelList.insert(item, model);
    QObject::connect(item, SIGNAL(addRowToDocument(DocumentView*)), this, SLOT(addRowToDocument(DocumentView*)));
    QObject::connect(item, SIGNAL(deleteRowOfDocument(DocumentView*,int)), this, SLOT(deleteRowOfDocument(DocumentView*,int)));
    if(this->model == nullptr){
        this->model = model;
        ui->tableView->setModel(model);
        ui->comboBox->setCurrentIndex(0);

    }
}

void TraceabilityView::addRowToDocument(DocumentView *item){

    QList<QStandardItemModel*> list = traceModelList.values();
    for(int i = 0; i < list.size(); i++)
            list[i]->setVerticalHeaderLabels(requirements->getHeader());

    if(item == requirements)
        return;

    QStandardItemModel *model = traceModelList.value(item);
    model->setHorizontalHeaderLabels(item->getHeader());
}

void TraceabilityView::deleteRowOfDocument(DocumentView *item, int row){

    if(item == requirements){
        QList<QStandardItemModel*> list = traceModelList.values();
        for(int i = 0; i < list.size(); i++)
                list[i]->removeRow(row);
        return;
    }

    QStandardItemModel *model = traceModelList.value(item);
    model->removeColumn(row);

}

void TraceabilityView::selectedDocumentChanged(int index){

    DocumentView *item = static_cast<DocumentView*> (otherDocsModel.item(index));
    QStandardItemModel *model = traceModelList.value(item);

    this->model = model;
    ui->tableView->setModel(model);
}

TraceabilityView::~TraceabilityView()
{
    delete ui;
}
