#ifndef DOCUMENTEDITORVIEW_H
#define DOCUMENTEDITORVIEW_H

#include <QWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <documentview.h>
#include <list>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStandardItem>


namespace Ui {
class DocumentEditorView;
}


class DocumentEditorView : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentEditorView(QWidget *parent = 0);
    void addLoadedTab(DocumentView*);
    ~DocumentEditorView();

signals:
    void docAdded(DocumentView *);
    void removeDocument(int index);



public slots:
    void addNewTab();
    void deleteTab();
    void loadTab();
    void saveTab();

private:
    Ui::DocumentEditorView *ui;
    std::list<DocumentView*> documentlist;

};

#endif // DOCUMENTEDITORVIEW_H
