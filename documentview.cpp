#include "documentview.h"
#include "ui_documentview.h"

DocumentView::DocumentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentView)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 0, this);
    model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("ID"));
    model->setHorizontalHeaderItem(model->columnCount(), new QStandardItem("Name"));
    ui->tableView->setModel(model);

    QObject::connect(ui->addRowButton, SIGNAL(pressed()), this, SLOT(addRow()));
    QObject::connect(ui->addColumnButton, SIGNAL(pressed()), this, SLOT(addColumn()));
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
    model->setVerticalHeaderItem(model->rowCount(), new QStandardItem(""));
}
