#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCursor>

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

public slots:
    void log(const QString& text);
    void clear();

private slots:
    void on_pbVizualize_clicked();

    void on_actionEdge_List_triggered();

    void on_actionAdjacency_List_triggered();

    void on_actionIncidence_Matrix_triggered();

    void on_actionAdjacency_Matrix_triggered();

    void on_pbCalcMetrics_clicked();

    void on_rbOrient_clicked();

    void on_rbNotOrient_clicked();

    void on_pbAddNode_clicked();

    void on_pbDeleteNode_clicked();

    void on_pbAddEdge_clicked();

    void on_pbDeleteEdge_clicked();

    void on_pbDFS_clicked();

private:
    void showErr(int errCode);

private:
    Graph m_Graph;
    Ui::MainWindow *ui = nullptr;
    GraphWidget* graph = nullptr;
};

#endif // MAINWINDOW_H
