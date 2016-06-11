#ifndef BOOLEANWIDGET_H
#define BOOLEANWIDGET_H

#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>
#include <QPushButton>

class MyButton : public QPushButton {

public:
    MyButton(QWidget *parent) : QPushButton(parent) {

    }

     virtual void	mousePressEvent(QMouseEvent *e) {
        pressed();
    }

};

class BooleanWidget : public QWidget
{
    Q_OBJECT

    QPushButton *checkBox;

    //enum STATE { NONE, BACKWARDS, FORWARDS};
    //STATE state;
    int state;

public:

    static QImage *backicon;
    static QImage *foricon;
    static QImage *noneicon;

    BooleanWidget(QWidget * parent = 0);

    int getState() { return state;}
    void  setState(int st);
    void setIcon(QIcon &icon){
        checkBox->setIcon(icon);
    }


public slots:
    void  nextState();

};

#endif // BOOLEANWIDGET_H
