#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QLineEdit>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QItemSelection>

namespace Ui {
class DocumentView;
}

class DocumentView : public QWidget, public QStandardItem
{
    Q_OBJECT
    QMessageBox* msgBox;

public:
    explicit DocumentView(QString &name, QWidget *parent = 0);
    QStringList getHeader();
    QStandardItemModel* getModel() { return model; }
    QString getName() {return name;}
    int getIndexGlobalRow(QModelIndex &index);
    QStringList getColumnNames();
    ~DocumentView();

public slots:
    void addColumn();
    void addRow();
    void deleteColumn();
    void deleteRow();
    void mousePressEvent(QMouseEvent *event);
    void addSubRow();

    void dataChanged(QModelIndex,QModelIndex,QVector<int>);

signals:
    void addRowToDocument(DocumentView*, int);
    void deleteRowOfDocument(DocumentView*, int, int);

private:
    Ui::DocumentView *ui;
    QStandardItemModel *model;
    QString name;
    QStringList labels;
};

#endif // DOCUMENTVIEW_H
