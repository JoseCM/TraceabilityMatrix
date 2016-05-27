/********************************************************************************
** Form generated from reading UI file 'documenteditorview.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTEDITORVIEW_H
#define UI_DOCUMENTEDITORVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DocumentEditorView
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *addDocButton;
    QTabWidget *tabWidget;

    void setupUi(QWidget *DocumentEditorView)
    {
        if (DocumentEditorView->objectName().isEmpty())
            DocumentEditorView->setObjectName(QStringLiteral("DocumentEditorView"));
        DocumentEditorView->resize(400, 300);
        horizontalLayout = new QHBoxLayout(DocumentEditorView);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addDocButton = new QPushButton(DocumentEditorView);
        addDocButton->setObjectName(QStringLiteral("addDocButton"));

        horizontalLayout->addWidget(addDocButton);

        tabWidget = new QTabWidget(DocumentEditorView);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(DocumentEditorView);

        QMetaObject::connectSlotsByName(DocumentEditorView);
    } // setupUi

    void retranslateUi(QWidget *DocumentEditorView)
    {
        DocumentEditorView->setWindowTitle(QApplication::translate("DocumentEditorView", "Form", 0));
        addDocButton->setText(QApplication::translate("DocumentEditorView", "New Document", 0));
    } // retranslateUi

};

namespace Ui {
    class DocumentEditorView: public Ui_DocumentEditorView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTEDITORVIEW_H
