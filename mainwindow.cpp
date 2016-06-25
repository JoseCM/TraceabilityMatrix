#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBrush>
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    project_open = false;
    ui->setupUi(this);
    ui->frame->hide();
}
void MainWindow::showEditor(){
    ui->centralWidget->layout()->removeWidget(traceability);
    traceability->hide();
    ui->centralWidget->layout()->removeWidget(requirements);
    requirements->hide();
    ui->centralWidget->layout()->addWidget(editor);
    editor->show();
    ui->showTrace->setChecked(false);
    ui->showReq->setChecked(false);
}

void MainWindow::showTraceability(){

    ui->centralWidget->layout()->removeWidget(editor);
    editor->hide();
    ui->centralWidget->layout()->removeWidget(requirements);
    requirements->hide();
    ui->centralWidget->layout()->addWidget(traceability);
    traceability->show();
    traceability->updateTrace(QModelIndex());
    ui->showEdit->setChecked(false);
    ui->showReq->setChecked(false);
}

void MainWindow::showRequirements(){
    ui->centralWidget->layout()->removeWidget(traceability);
    traceability->hide();
    ui->centralWidget->layout()->removeWidget(editor);
    editor->hide();
    ui->centralWidget->layout()->addWidget(requirements);
    requirements->show();
    ui->showEdit->setChecked(false);
    ui->showTrace->setChecked(false);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        msgBox = new QMessageBox();
        msgBox->setWindowTitle("Hello");
        msgBox->setText("You Clicked Right Mouse Button");
        msgBox->show();
    }
}

void MainWindow::closeEvent ( QCloseEvent * event ){
    if(project_open){
       QMessageBox::StandardButton button =  QMessageBox::question(this, "Quit", "Save befor quitting?",
                                                       QMessageBox::Yes |  QMessageBox::No |  QMessageBox::Cancel );
       if(button == QMessageBox::Yes){
           on_actionSave_Project_triggered();
           event->accept();
       } else if (button == QMessageBox::No){
           event->accept();
       } else {
           event->ignore();
       }
    } else {
        QMessageBox::StandardButton button =  QMessageBox::question(this, "Quit", "Are you sure you want to quit?", QMessageBox::Yes |  QMessageBox::No);
        if (button == QMessageBox::Yes){
            event->accept();
        } else {
            event->ignore();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Project_triggered()
{
    if(project_open)
        on_actionClose_Project_triggered();

    if(project_open)
        return;


    QString tempdir = QFileDialog::getExistingDirectory(this, QString("Choose Project Directory"));
    if(tempdir.isEmpty())
        return;
    current_project_directory =  QDir(tempdir);
    current_project_name = current_project_directory.dirName();

    editor = new DocumentEditorView(this);
    editor->hide();
    QString temp = current_project_name;
    requirements = new DocumentView(QString(current_project_name + "_requirements.xml"), this);
    requirements->hide();
    traceability = new TraceabilityView(requirements, this);
    ui->centralWidget->layout()->addWidget(traceability);

    QObject::connect(ui->showReq, SIGNAL(pressed()), this, SLOT(showRequirements()));
    QObject::connect(ui->showEdit, SIGNAL(pressed()), this, SLOT(showEditor()));
    QObject::connect(ui->showTrace, SIGNAL(pressed()), this, SLOT(showTraceability()));
    QObject::connect(editor, SIGNAL(docAdded(DocumentView*)), traceability, SLOT(addModels(DocumentView*)));
    QObject::connect(editor, SIGNAL(removeDocument(int)), traceability, SLOT(removeDocument(int)));

    project_open = true;
    saveProject();
    ui->frame_2->hide();
    ui->frame->show();
}

void MainWindow::saveProject(){

    if(!project_open){
        return;
    }

    const QString pathName =  current_project_directory.dirName();
    QString fileName = current_project_directory.filePath(current_project_name + ".trx");

    QDomDocument doc;

    QDomElement el = doc.createElement("trproject");
    el.appendChild(doc.createTextNode(current_project_name));
    doc.appendChild(el);

    QDomElement subel = doc.createElement("requirements");
    subel.appendChild(doc.createTextNode(requirements->getName()));
    el.appendChild(subel);
    requirements->saveDocument(current_project_directory.dirName() + "/" + requirements->getName());

    QHash<DocumentView*, QStandardItemModel*> *traceModelList = traceability->getTraceModelList();

    for(DocumentView* document : traceModelList->keys()){

        qDebug() << "filename: " << current_project_directory.dirName() + "/" + document->getName();
        document->saveDocument(current_project_directory.dirName() + "/" + document->getName());
        traceability->saveMatrix(current_project_directory.dirName() + "/" + document->getName() + "_matrix", traceModelList->value(document));

        QDomElement subel = doc.createElement("entry");
        QDomElement docel = doc.createElement("document");
        docel.appendChild(doc.createTextNode(document->getName()));
        QDomElement matel = doc.createElement("matrix");
        matel.appendChild(doc.createTextNode(document->getName()));
        subel.appendChild(docel);
        subel.appendChild(matel);
        el.appendChild(subel);
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

     file.write(doc.toByteArray());
     file.close();


}

void MainWindow::on_actionSave_Project_triggered()
{
    if(!project_open){
        QMessageBox::warning(this, "No project", "No project open!");
        return;
    }

    saveProject();

    QMessageBox::information(this, "Project saved", "Project saved!");
}

void MainWindow::on_actionOpen_Project_triggered()
{
    if(project_open)
        on_actionClose_Project_triggered();

    if(project_open)
        return;

    editor = new DocumentEditorView(this);
    editor->hide();

    QDomDocument doc;
    QString filename = QFileDialog::getOpenFileName(this, QString("Choose Project"), ".", "TRX Project (*.trx)");
    QFile file(filename);
    current_project_directory =  QFileInfo(filename).absoluteDir();
    current_project_name = QFileInfo(filename).baseName();

    qDebug() << "filename: " << filename;

    if (!file.open(QIODevice::ReadOnly | QFile::Text))
        return;

    QString message;

    if (!doc.setContent(&file ,false, &message)) {
        file.close();
        return;
    }

    file.close();

    QDomElement docEl = doc.documentElement();

    QString docName = docEl.toElement().firstChild().nodeValue();
    qDebug() << docEl.toElement().firstChild().nodeValue();

    QDomNode child = docEl.firstChild().nextSibling();
    qDebug() << child.toElement().firstChild().nodeValue();

    qDebug() << QFileInfo(filename).absoluteDir().filePath(child.toElement().firstChild().nodeValue());
    requirements = DocumentView::loadDocument(QFileInfo(filename).absoluteDir().filePath(child.toElement().firstChild().nodeValue()));
    requirements->hide();
    traceability = new TraceabilityView(requirements, this);
    ui->centralWidget->layout()->addWidget(traceability);

    QObject::connect(ui->showReq, SIGNAL(pressed()), this, SLOT(showRequirements()));
    QObject::connect(ui->showEdit, SIGNAL(pressed()), this, SLOT(showEditor()));
    QObject::connect(ui->showTrace, SIGNAL(pressed()), this, SLOT(showTraceability()));
    QObject::connect(editor, SIGNAL(docAdded(DocumentView*)), traceability, SLOT(addModels(DocumentView*)));
    QObject::connect(editor, SIGNAL(removeDocument(int)), traceability, SLOT(removeDocument(int)));

    QHash<DocumentView*, QStandardItemModel*> *traceModelList = traceability->getTraceModelList();
    bool modelset = false;
    child = child.nextSibling();
    while (!child.isNull())
    {
        QDomNode subchild = child.firstChild();
        qDebug() << subchild.toElement().firstChild().nodeValue();
        DocumentView* docview = DocumentView::loadDocument(current_project_directory.dirName() + "/" + subchild.toElement().firstChild().nodeValue());
        subchild = subchild.nextSibling();
        qDebug() << subchild.toElement().firstChild().nodeValue();
        QStandardItemModel *matrix = TraceabilityView::loadMatrix(current_project_directory.dirName() + "/" + subchild.toElement().firstChild().nodeValue()+ "_matrix");

        //traceability->addModels(docview, matrix);
        editor->addLoadedTab(docview);
        matrix->setHorizontalHeaderLabels(docview->getHeader());
        traceModelList->insert(docview, matrix);

        if(!modelset){
            traceability->setMatrixModel(matrix);
            modelset = true;
        }

        child = child.nextSibling();
    }


    traceability->updateReqListModel();
    project_open = true;
    ui->frame_2->hide();
    ui->frame->show();
}



void MainWindow::on_actionClose_Project_triggered()
{
    if(!project_open){
        QMessageBox::warning(this, "No project", "No project open!");
        return;
    }

    QMessageBox::StandardButton button =  QMessageBox::question(this, "Close Project", "Save curent project before closing?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (button == QMessageBox::Ok){
        on_actionSave_Project_triggered();
    } else if (button == QMessageBox::Cancel){
        return;
    }

    project_open = false;
    current_project_directory = QDir();
    current_project_name = "";

    delete editor;
    delete requirements;
    delete traceability;
    ui->frame_2->show();
    ui->frame->hide();
}

void MainWindow::on_pushButton_clicked()
{
    on_actionNew_Project_triggered();
}

void MainWindow::on_pushButton_2_clicked()
{
    on_actionOpen_Project_triggered();
}
