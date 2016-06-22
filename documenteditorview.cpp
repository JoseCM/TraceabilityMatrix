#include "documenteditorview.h"
#include "ui_documenteditorview.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>
#include <xmlhandler.h>
#include <QXmlStreamWriter>
#include <iostream>
#include <QDomDocument>

DocumentEditorView::DocumentEditorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentEditorView)
{
    ui->setupUi(this);
    QObject::connect(ui->addDocButton, SIGNAL(pressed()), this, SLOT(addNewTab()));
    QObject::connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(deleteTab()));
    QObject::connect(ui->loadDocButton, SIGNAL(pressed()), this, SLOT(loadTab()));
    QObject::connect(ui->saveButton, SIGNAL(pressed()), this, SLOT(saveTab()));
}

DocumentEditorView::~DocumentEditorView()
{
    delete ui;
}

void DocumentEditorView::addLoadedTab(DocumentView *doc){

    doc->setParent(this);
    ui->tabWidget->addTab(doc, doc->getName());
    documentlist.push_back(doc);
    docAdded(doc);
}

void DocumentEditorView::saveTab(){

   if(ui->tabWidget->currentIndex() < 0)
       return;

   QString fileName =  QFileDialog::getSaveFileName(this);

   std::list<DocumentView*>::iterator it = documentlist.begin();
   std::advance(it, ui->tabWidget->currentIndex());
   (*it)->saveDocument(fileName);

}

void DocumentEditorView::loadTab(){

    QString filename = QFileDialog::getOpenFileName(this);

    DocumentView *newdoc = DocumentView::loadDocument(filename);
    newdoc->setParent(this);
    ui->tabWidget->addTab(newdoc, newdoc->getName());
    documentlist.push_back(newdoc);
    docAdded(newdoc);


}

void DocumentEditorView::addNewTab(){

    bool ok;
    QString text = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Trace Document", &ok);

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
        std::list<DocumentView*>::iterator it = documentlist.begin();
        std::advance(it, ui->tabWidget->currentIndex());
        documentlist.erase(it);
        removeDocument(ui->tabWidget->currentIndex());        
        //ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    }
}



