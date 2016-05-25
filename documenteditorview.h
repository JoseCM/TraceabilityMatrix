#ifndef DOCUMENTEDITORVIEW_H
#define DOCUMENTEDITORVIEW_H

#include <QWidget>

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
};

#endif // DOCUMENTEDITORVIEW_H
