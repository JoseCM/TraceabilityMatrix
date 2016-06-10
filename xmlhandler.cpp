#include "xmlhandler.h"
#include "ui_xmlhandler.h"

XmlHandler::XmlHandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XmlHandler)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 0, this);
    tree_model = new QStandardItemModel(0,0,this);
    ui->tableView->setModel(model);
    ui->treeView->setModel(tree_model);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Coluna1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Coluna2")));
    model->setVerticalHeaderItem(0, new QStandardItem(QString("Linha1")));
    model->setVerticalHeaderItem(1, new QStandardItem(QString("Linha2")));
    model->setVerticalHeaderItem(2, new QStandardItem(QString("Linha3")));

    model->setItem(0,0, new QStandardItem(QString("ola11")));
    model->setItem(0,1, new QStandardItem(QString("ola12")));
    model->setItem(1,0, new QStandardItem(QString("ola21")));
    model->setItem(1,1, new QStandardItem(QString("ola22")));
    model->setItem(2,0, new QStandardItem(QString("ola31")));
    model->setItem(2,1, new QStandardItem(QString("ola32")));

    tree_model->setVerticalHeaderItem(0,new QStandardItem(QString("Ola1")));
    tree_model->setItem(0,new QStandardItem(QString("Ol")));
    tree_model->setItem(1,new QStandardItem(QString("Ola")));
    tree_model->setVerticalHeaderItem(1,new QStandardItem(QString("Ola2")));
    tree_model->setItem(0,new QStandardItem(QString("Ol2")));
    tree_model->setItem(1,new QStandardItem(QString("Ola")));
}

XmlHandler::~XmlHandler()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////////////
void XmlHandler::startTree(){

    readXmlToTree();
}

void XmlHandler::readXmlToTree()
{
    /*
     * Example file
     *
     * <?xml version="1.0" encoding="UTF-8"?>
        <tree>
            <Sexo>
                <Fem></Fem>
                <Masc></Masc>
            </Sexo>
            <Idade>
                <21></21>
            </Idade>
        </tree>

     *
     *
     * */
    QDomDocument doc;
    QFile file("C:/Users/Almeida/Desktop/tree.xml"); //filename
    if (!file.open(QIODevice::ReadOnly | QFile::Text)){
        std::cerr<< "ERROR: file openning"<< std::endl;
        return;
    }

    if (!doc.setContent(&file)) {
        std::cerr << "ERROR: dom document open" << std::endl;
        file.close();
        return;
    }

    file.close();

    QDomElement docEl = doc.documentElement();
    if (docEl.tagName() != "tree") {
            std::cerr << "Error: Not a bookindex file" << std::endl;
            return ;
    }

    QDomNode child = docEl.firstChild();
    int index = 0;

    while (!child.isNull())
    {
        qDebug(child.toElement().tagName().toLatin1());
        QDomNode childNode = child.toElement().firstChild();

        while(!childNode.isNull())
        {
            qDebug(" "+childNode.toElement().tagName().toLatin1());
            childNode = childNode.nextSibling();
        }
        child = child.nextSibling();
        index++;
    }
}

void XmlHandler::writeXmlToTree(QStandardItemModel &model)
{
    QStandardItem root = model.invisibleRootItem();
    QStandardItem item = root.child();

    qDebug(item.text().toLatin1());

    /* ... */
}

void XmlHandler::insertFather(QString name){
    item = new QStandardItem(name);
    item->setEditable(false);
}

void XmlHandler::insertChildren(QString name){
    QStandardItem *subItem = new QStandardItem( name );
    subItem->setEditable(false);
    item->appendRow(subItem);
}

void XmlHandler::setItem(int nRow,QStandardItemModel *model){
    model->setItem(nRow, item);
    nRow++;
}

///////////////////////////////////////////////////////////////////////////////////////
bool XmlHandler::writeXml(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("table");

    for (int i = 0; i < model->rowCount(); i++)
    {
        xmlWriter.writeStartElement(model->verticalHeaderItem(i)->text());
        for(int j=0; j < model->columnCount(); j++)
        {
            xmlWriter.writeTextElement(model->horizontalHeaderItem(j)->text(),model->item(i,j)->text());
        }
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    if (file.error()) {
        std::cerr << "Error: O nico"
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    readXml(fileName);
    return true;
}

bool XmlHandler::readXml(const QString &fileName)
{
    QFile file2(fileName);

    QStandardItemModel *model2 = new QStandardItemModel(0,0,this);
    ui->tableView_2->setModel(model2);

    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this,"Load XML File Problem",
            "Couldn't open xmlfile.xml to load settings for download",
            QMessageBox::Ok);
            return false;
    }

    QXmlStreamReader *xmlReader = new QXmlStreamReader(&file2);

     int indexVert=0, indexHor=0, i = 0;
     bool aux = false;

     //Parse the XML until we reach end of it
     while(!xmlReader->atEnd() && !xmlReader->hasError()) {

            if(xmlReader->isStartDocument()) {
                xmlReader->readNext();
                xmlReader->readNext();

                continue;
            }

            if(xmlReader->isStartElement())
            {
                model2->setVerticalHeaderItem(indexVert,new QStandardItem(QString(xmlReader->name().toString())));
                xmlReader->readNextStartElement();

                while(!xmlReader->isEndElement())
                {
                    if(!aux)
                        model2->setHorizontalHeaderItem(indexHor,new QStandardItem(QString(xmlReader->name().toString())));

                    model2->setItem(i,indexHor,new QStandardItem(QString(xmlReader->readElementText())));
                    xmlReader->readNextStartElement();
                    indexHor++;
                }
                indexVert++;
                aux=true;
                indexHor = 0;
                i++;
           }

           xmlReader->readNext();
    }


    if(xmlReader->hasError()) {
            QMessageBox::critical(this,
            "xmlFile.xml Parse Error",xmlReader->errorString(),
            QMessageBox::Ok);
            return false;
    }

    //close reader and flush file
    xmlReader->clear();
    file2.close();

    return true;
}

void XmlHandler::on_saveFileButton_clicked()
{
    QString fileName = ui->lineEdit->text();
    writeXml(fileName);
}
