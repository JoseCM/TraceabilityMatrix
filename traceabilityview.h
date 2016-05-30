#ifndef TRACEABILITYVIEW_H
#define TRACEABILITYVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include "checkboxdelegate.h"
#include "documentview.h"

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
    QStandardItemModel *model;
    QList<QStandardItemModel*> traceModelList;
    QStandardItemModel otherDocsModel;
    DocumentView *requirements;

};

#endif // TRACEABILITYVIEW_H
