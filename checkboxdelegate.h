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
#include "booleanwidget.h"




class CheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT


public:
    CheckBoxDelegate(QWidget *parent);

    virtual QWidget * createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    virtual void      setEditorData(QWidget * editor, const QModelIndex & index) const;
    virtual void      setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    virtual void      paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

};

#endif // CHECKBOXDELEGATE_H
