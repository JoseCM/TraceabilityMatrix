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
#include <QTableView>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMessageBox* msgBox;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showEditor();
    void showTraceability();
    void showRequirements();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_actionNew_Project_triggered();

private:
    Ui::MainWindow *ui;
    DocumentEditorView *editor;
    TraceabilityView *traceability;
    DocumentView *requirements;
};

#endif // MAINWINDOW_H
