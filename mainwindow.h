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

    void closeEvent ( QCloseEvent * event );

public slots:
    void showEditor();
    void showTraceability();
    void showRequirements();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_actionNew_Project_triggered();
    void on_actionOpen_Project_triggered();
    void on_actionSave_Project_triggered();

    void on_actionClose_Project_triggered();

private:
    Ui::MainWindow *ui;
    DocumentEditorView *editor;
    TraceabilityView *traceability;
    DocumentView *requirements;
    QDir current_project_directory;
    QString current_project_name;
    bool project_open = false;
};

#endif // MAINWINDOW_H
