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

    void on_pbRead_clicked();

private:
    Graph m_GM;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
