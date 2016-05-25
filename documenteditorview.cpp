#include "documenteditorview.h"
#include "ui_documenteditorview.h"

DocumentEditorView::DocumentEditorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentEditorView)
{
    ui->setupUi(this);

    QObject::connect(ui->addDocButton, SIGNAL(pressed()), this, SLOT(addNewTab()));
}

DocumentEditorView::~DocumentEditorView()
{
    delete ui;
}

void DocumentEditorView::addNewTab(){

    bool ok;
    QString text = QInputDialog::getText(this, tr("Document Name"), tr("Document Name:"), QLineEdit::Normal, "Doc", &ok);
    if (ok && !text.isEmpty())
        ui->tabWidget->addTab(new DocumentView(this), text);
}

