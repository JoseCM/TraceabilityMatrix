#ifndef DOCUMENTEDITORVIEW_H
#define DOCUMENTEDITORVIEW_H

#include <QWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <documentview.h>
#include <list>

namespace Ui {
class DocumentEditorView;
}


class DocumentEditorView : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentEditorView(QWidget *parent = 0);
    ~DocumentEditorView();

public slots:
    void addNewTab();

private:
    Ui::DocumentEditorView *ui;
    std::list<DocumentView*> documentlist;

};

#endif // DOCUMENTEDITORVIEW_H
