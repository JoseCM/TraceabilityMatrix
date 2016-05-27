/********************************************************************************
** Form generated from reading UI file 'documentview.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTVIEW_H
#define UI_DOCUMENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DocumentView
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *addColumnButton;
    QPushButton *addRowButton;
    QPushButton *delRowButtom;
    QPushButton *delColButtom;

    void setupUi(QWidget *DocumentView)
    {
        if (DocumentView->objectName().isEmpty())
            DocumentView->setObjectName(QStringLiteral("DocumentView"));
        DocumentView->resize(400, 300);
        verticalLayout = new QVBoxLayout(DocumentView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(DocumentView);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addColumnButton = new QPushButton(DocumentView);
        addColumnButton->setObjectName(QStringLiteral("addColumnButton"));

        horizontalLayout->addWidget(addColumnButton);

        addRowButton = new QPushButton(DocumentView);
        addRowButton->setObjectName(QStringLiteral("addRowButton"));

        horizontalLayout->addWidget(addRowButton);

        delRowButtom = new QPushButton(DocumentView);
        delRowButtom->setObjectName(QStringLiteral("delRowButtom"));

        horizontalLayout->addWidget(delRowButtom);

        delColButtom = new QPushButton(DocumentView);
        delColButtom->setObjectName(QStringLiteral("delColButtom"));

        horizontalLayout->addWidget(delColButtom);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DocumentView);

        QMetaObject::connectSlotsByName(DocumentView);
    } // setupUi

    void retranslateUi(QWidget *DocumentView)
    {
        DocumentView->setWindowTitle(QApplication::translate("DocumentView", "Form", 0));
        addColumnButton->setText(QApplication::translate("DocumentView", "Add Column", 0));
        addRowButton->setText(QApplication::translate("DocumentView", "Add Row", 0));
        delRowButtom->setText(QApplication::translate("DocumentView", "Delete Row", 0));
        delColButtom->setText(QApplication::translate("DocumentView", "Delete Column", 0));
    } // retranslateUi

};

namespace Ui {
    class DocumentView: public Ui_DocumentView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTVIEW_H
