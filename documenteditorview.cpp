#include "documenteditorview.h"
#include "ui_documenteditorview.h"
#include <QDebug>

DocumentEditorView::DocumentEditorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentEditorView)
{
    ui->setupUi(this);
    QObject::connect(ui->addDocButton, SIGNAL(pressed()), this, SLOT(addNewTab()));
    QObject::connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(deleteTab()));
}

DocumentEditorView::~DocumentEditorView()
{
    delete ui;
}

void DocumentEditorView::addNewTab(){

    bool ok;
    QString text = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    if (ok && !text.isEmpty()){
        DocumentView *newdoc = new DocumentView(text, this);
        ui->tabWidget->addTab(newdoc, text);
        documentlist.push_back(newdoc);
        docAdded(newdoc);
   }
}

void DocumentEditorView::deleteTab(){
    if(ui->tabWidget->currentIndex() < 0)
        return;

    if(QMessageBox::question(this, "Delete Document", "Are you sure you want to delete this document?",  QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        qDebug() << ui->tabWidget->currentIndex();
        removeDocument(ui->tabWidget->currentIndex());
        //ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    }
}
