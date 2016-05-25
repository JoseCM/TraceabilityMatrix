#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QWidget *parent) : QItemDelegate(parent)
{

}

QWidget * CheckBoxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const {

    QWidget *ch = new BooleanWidget(parent);
    return ch;

}
void CheckBoxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const{

   bool tf =  index.model()->data(index, Qt::EditRole).toBool();
   BooleanWidget *ch = static_cast<BooleanWidget*>(editor);
   ch->setChecked(tf);
}
void CheckBoxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const{
   BooleanWidget *ch = static_cast<BooleanWidget*>(editor);
   model->setData(index, ch->isChecked());
}

void CheckBoxDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const{
    drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
}
