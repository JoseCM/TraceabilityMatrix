/********************************************************************************
** Form generated from reading UI file 'traceabilityview.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACEABILITYVIEW_H
#define UI_TRACEABILITYVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TraceabilityView
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;

    void setupUi(QWidget *TraceabilityView)
    {
        if (TraceabilityView->objectName().isEmpty())
            TraceabilityView->setObjectName(QStringLiteral("TraceabilityView"));
        TraceabilityView->resize(443, 346);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(90);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TraceabilityView->sizePolicy().hasHeightForWidth());
        TraceabilityView->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(TraceabilityView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(TraceabilityView);
        tableView->setObjectName(QStringLiteral("tableView"));
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(tableView);


        retranslateUi(TraceabilityView);

        QMetaObject::connectSlotsByName(TraceabilityView);
    } // setupUi

    void retranslateUi(QWidget *TraceabilityView)
    {
        TraceabilityView->setWindowTitle(QApplication::translate("TraceabilityView", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TraceabilityView: public Ui_TraceabilityView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACEABILITYVIEW_H
