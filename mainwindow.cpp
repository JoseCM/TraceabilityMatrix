#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0, 0, this);

//    QStandardItem *item = new QStandardItem();
//    item->setCheckable(true);
//    item->setEditable(false);
//    model->setItemPrototype(item);
//    model->setColumnCount(2);
//    model->setRowCount(2);
    
//    QModelIndex index = model()->index(0, 0, QModelIndex());
//    QAbstractItemView::setIndexWidget(index, widget);

    ui->tableView->setModel(model);
    QItemDelegate* del = new CheckBoxDelegate(this);
    ui->tableView->setItemDelegate(del);



    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Coluna 1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Coluna 2")));
    model->setVerticalHeaderItem(0, new QStandardItem(QString("Linha 1")));
    model->setVerticalHeaderItem(1, new QStandardItem(QString("Linha 2")));



//    QWidget *par = new QWidget();
//    QWidget *wi =  new QCheckBox();
//    QHBoxLayout * layout = new QHBoxLayout(par);
//    layout->addWidget(wi);
//    layout->setAlignment(Qt::AlignCenter);
//    layout->setMargin(0);
//    par->setLayout(layout);
//    ui->tableView->setIndexWidget(model->index(0, 0), par);

}


MainWindow::~MainWindow()
{
    delete ui;
}
