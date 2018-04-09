#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphwidget.h"
#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbVizualize_clicked();

    void on_actionEdge_List_triggered();

    void on_actionAdjacency_List_triggered();

    void on_actionIncidence_Matrix_triggered();

    void on_actionAdjacency_Matrix_triggered();

    void on_pbCalcMetrics_clicked();

private:
    Graph m_Graph;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
