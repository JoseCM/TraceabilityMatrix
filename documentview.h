#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QWidget>

namespace Ui {
class DocumentView;
}

class DocumentView : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentView(QWidget *parent = 0);
    ~DocumentView();

private:
    Ui::DocumentView *ui;
};

#endif // DOCUMENTVIEW_H
