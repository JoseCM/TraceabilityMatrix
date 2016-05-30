#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QWidget>
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>
#include <xmlhandler.h>
#include <QXmlStreamWriter>
#include <iostream>

namespace Ui {
class XmlHandler;
}

class XmlHandler : public QWidget
{
    Q_OBJECT

public:
    explicit XmlHandler(QWidget *parent = 0);
    bool writeXml(const QString &fileName);
    bool readXml(const QString &fileName);
    ~XmlHandler();

private slots:
    void on_saveFileButton_clicked();

private:
    Ui::XmlHandler *ui;
    QStandardItemModel *model;
};

#endif // XMLHANDLER_H
