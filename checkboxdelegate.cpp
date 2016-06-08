#include "checkboxdelegate.h"
#include <QDebug>
#include <QPainter>
QImage* BooleanWidget::backicon = new QImage(":/row-pre.png");
QImage* BooleanWidget::foricon = new QImage(":/row-pos.png");
QImage* BooleanWidget::noneicon = new QImage(":/row-pos.png");

CheckBoxDelegate::CheckBoxDelegate(QWidget *parent) : QItemDelegate(parent)
{

}

QWidget * CheckBoxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {

    QWidget *ch = new BooleanWidget(parent);
    return ch;

}
void CheckBoxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const{

   int tf =  index.model()->data(index, Qt::EditRole).toInt();
   BooleanWidget *ch = static_cast<BooleanWidget*>(editor);
   ch->nextState();

}
void CheckBoxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const{

   BooleanWidget *ch = static_cast<BooleanWidget*>(editor);
   model->setData(index, ch->getState());
}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{
   // drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
    if(index.data().toInt() == 0)
        return;
   drawDecoration(painter, option, option.rect, index.data().toInt() == 1? QPixmap::fromImage(*(BooleanWidget::backicon)) :
                                                                           QPixmap::fromImage(*(BooleanWidget::foricon)));
   //painter->drawImage(option.rect, *(BooleanWidget::backicon));
}
