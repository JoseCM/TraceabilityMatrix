#include "checkboxdelegate.h"
#include <QDebug>
#include <QPainter>


CheckBoxDelegate::CheckBoxDelegate(QWidget *parent) : QItemDelegate(parent)
{

}

QWidget * CheckBoxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {

    BooleanWidget *ch = new BooleanWidget( parent);
    return ch;

}
void CheckBoxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const{

   int tf =  index.model()->data(index, Qt::EditRole).toInt();
   BooleanWidget *ch = static_cast<BooleanWidget*>(editor);
   ch->setState(tf);

}

void CheckBoxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const{

   BooleanWidget *ch = static_cast<BooleanWidget*>(editor);
   model->setData(index, ch->getState());


}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{
   // drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);

   drawDecoration(painter, option, option.rect, index.data().toInt() == 1? QPixmap::fromImage(*(BooleanWidget::backicon)) :
                                                index.data().toInt() == 2? QPixmap::fromImage(*(BooleanWidget::foricon)) :
                                                                           QPixmap::fromImage(*(BooleanWidget::noneicon)));
}
