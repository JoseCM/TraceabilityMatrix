#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>
#include <QPushButton>
class BooleanWidget : public QWidget
{
    QPushButton *checkBox;

    //enum STATE { NONE, BACKWARDS, FORWARDS};
    //STATE state;
    int state;

    public:

    static QImage *backicon;
    static QImage *foricon;
    static QImage *noneicon;

    BooleanWidget(QWidget * parent = 0) : QWidget(parent)
    {

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QHBoxLayout * layout = new QHBoxLayout(this);
        checkBox = new QPushButton("hello",layout);
        checkBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //layout->addWidget(checkBox,0, Qt::AlignCenter);
        state = 0;
    }

    int getState() { return state;}
    void  setState(int st) { state = st; }
    void  nextState() {

        if(state == 0)
            state = 1;
        else if (state == 1)
            state = 2;
        else
            state = 0;
    }
};


class CheckBoxDelegate : public QItemDelegate
{

public:
    CheckBoxDelegate(QWidget *parent);

    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual void      setEditorData(QWidget * editor, const QModelIndex & index) const;
    virtual void      setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    virtual void      paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // CHECKBOXDELEGATE_H
