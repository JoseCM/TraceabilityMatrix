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

private:
    Ui::TraceabilityView *ui;
    QStandardItemModel *model;

};

#endif // TRACEABILITYVIEW_H
