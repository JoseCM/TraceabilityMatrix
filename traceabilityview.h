#ifndef TRACEABILITYVIEW_H
#define TRACEABILITYVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include "checkboxdelegate.h"

namespace Ui {
class TraceabilityView;
}

class TraceabilityView : public QWidget
{
    Q_OBJECT

public:
    explicit TraceabilityView(QWidget *parent = 0);
    ~TraceabilityView();

public slots:
    void addModels(QStandardItem*);

private:
    Ui::TraceabilityView *ui;  
    QList<QStandardItemModel*> modellist;
    QStandardItemModel otherDocsModel;

};

#endif // TRACEABILITYVIEW_H
