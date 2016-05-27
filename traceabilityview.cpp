#include "traceabilityview.h"
#include "ui_traceabilityview.h"

TraceabilityView::TraceabilityView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TraceabilityView)
{
    ui->setupUi(this);

//    model = new QStandardItemModel(0, 0, this);

//    ui->tableView->setModel(model);
//    QItemDelegate* del = new CheckBoxDelegate(this);
//    ui->tableView->setItemDelegate(del);

//    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Coluna 1")));
//    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Coluna 2")));
//    model->setVerticalHeaderItem(0, new QStandardItem(QString("Linha 1")));
//    model->setVerticalHeaderItem(1, new QStandardItem(QString("Linha 2")));

//     ui->comboBox->setModel(ui);
}

TraceabilityView::~TraceabilityView()
{
    delete ui;
}
