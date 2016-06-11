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

void DocumentEditorView::saveTab(){

   if(ui->tabWidget->currentIndex() < 0)
       return;

   QString fileName =  QFileDialog::getSaveFileName(this);

   std::list<DocumentView*>::iterator it = documentlist.begin();
   std::advance(it, ui->tabWidget->currentIndex());
   QStandardItemModel *model = (*it)->getModel();
   QStringList header = (*it)->getColumnNames();

   QDomDocument doc;

   QDomElement el = doc.createElement("document");
   el.appendChild(doc.createTextNode((*it)->getName()));
   doc.appendChild(el);

   QStandardItem *root = model->invisibleRootItem();

   for(int i = 0; i < root->rowCount(); i++){  

       QDomElement subel = doc.createElement("row");
       el.appendChild(subel);

       for(int j = 0; j < root->columnCount(); j++){
            QStandardItem *item = root->child(i, j);
            QDomElement subsub =  doc.createElement(header.at(j));
            if(item)
                subsub.appendChild(doc.createTextNode(item->text()));
            subel.appendChild(subsub);
       }

       QStandardItem *item = root->child(i);


       for(int j = 0; j < item->rowCount(); j++){

           QDomElement subsubel = doc.createElement("subrow");
           subel.appendChild(subsubel);

           for(int k = 0; k < root->columnCount(); k++){

                QStandardItem *subitem = item->child(j, k);
                QDomElement subsub =  doc.createElement(header.at(k));
                if(subitem)
                    subsub.appendChild(doc.createTextNode(subitem->text()));
                subsubel.appendChild(subsub);
           }
      }
   }


   QFile file(fileName);
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

    file.write(doc.toByteArray());
    file.close();
   //readXml(fileName);
}

void DocumentEditorView::loadTab(){

   QString fileName =  QFileDialog::getOpenFileName(this);
   qDebug() << fileName;

   QDomDocument doc;
   QFile file(fileName); //filename
   if (!file.open(QIODevice::ReadOnly | QFile::Text)){
       std::cerr<< "ERROR: file openning"<< std::endl;
       return;
   }

   QString str;
   int line;
   if (!doc.setContent(&file, &str, &line)) {
       std::cerr << "ERROR: dom document open: " << str.toStdString() << " " << line << std::endl;
       file.close();
       return;
   }

   file.close();

   QDomElement docEl = doc.documentElement();

//   if (docEl.tagName() != "tree") {
//           std::cerr << "Error: Not a bookindex file" << std::endl;
//           return ;
//   }

   QString name = docEl.tagName();
   DocumentView *newdoc = new DocumentView(name, this);
   ui->tabWidget->addTab(newdoc, name);
   documentlist.push_back(newdoc);

   QStandardItem *root = newdoc->getModel()->invisibleRootItem();

   QDomNode child = docEl.firstChild();
   int index = 0;

   while (!child.isNull())
   {
       QStandardItem *rowitem = new QStandardItem(child.toElement().tagName().remove(0,1));
       root->appendRow(rowitem);
       QDomNode childNode = child.toElement().firstChild();

       while(!childNode.isNull())
       {
           rowitem->appendRow(new QStandardItem(childNode.toElement().tagName().remove(0,1)));

           while(!childNode.isNull())


           childNode = childNode.nextSibling();
       }
       child = child.nextSibling();
       index++;
   }


   docAdded(newdoc);

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
        std::list<DocumentView*>::iterator it = documentlist.begin();
        std::advance(it, ui->tabWidget->currentIndex());
        documentlist.erase(it);
        removeDocument(ui->tabWidget->currentIndex());        
        //ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    }
}
