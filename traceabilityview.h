#ifndef TRACEABILITYVIEW_H
#define TRACEABILITYVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include "checkboxdelegate.h"
#include "documentview.h"
#include <QPair>
#include <QHash>

namespace Ui {
class TraceabilityView;
}

class TraceabilityView : public QWidget
{
    Q_OBJECT

public:
    explicit TraceabilityView(DocumentView *requirements, QWidget *parent = 0);
    ~TraceabilityView();

public slots:
    void addModels(DocumentView *);
    void addRowToDocument(DocumentView *);
    //void addSubRowToDocument(DocumentView *,int);
    void deleteRowOfDocument(DocumentView*, int, int count);
    void selectedDocumentChanged(int);



private:
    Ui::TraceabilityView *ui;  
    QStandardItemModel *model;
    QHash<DocumentView*, QStandardItemModel*> traceModelList;
    DocumentView *requirements;
    QStandardItemModel otherDocsModel;

};

#endif // TRACEABILITYVIEW_H
