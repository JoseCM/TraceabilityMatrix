#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QItemDelegate>
#include <QCheckBox>
#include <QHBoxLayout>

class BooleanWidget : public QWidget
{
    QCheckBox * checkBox;

    public:

    BooleanWidget(QWidget * parent = 0) : QWidget(parent)
    {
        checkBox = new QCheckBox(this);
        QHBoxLayout * layout = new QHBoxLayout(this);
        layout->addWidget(checkBox,0, Qt::AlignCenter);

    }

    bool isChecked(){return checkBox->isChecked();}
    void setChecked(bool value){checkBox->setChecked(value);}
};


class CheckBoxDelegate : public QItemDelegate
{

public:
    CheckBoxDelegate(QWidget *parent);

    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual void	setEditorData(QWidget * editor, const QModelIndex & index) const;
    virtual void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    virtual void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // CHECKBOXDELEGATE_H
