#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>
#include <documentview.h>
#include <QStandardItem>
#include <QCheckBox>
#include <QItemEditorFactory>
#include <QItemDelegate>
#include <documenteditorview.h>
#include <traceabilityview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DocumentEditorView *editor;
    TraceabilityView *traceability;
};

#endif // MAINWINDOW_H
