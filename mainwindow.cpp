#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Graph Shell"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbVizualize_clicked()
{
    GraphWidget *graph = new GraphWidget;
    graph->show();
}

void MainWindow::on_pbRead_clicked()
{
    m_GM.ReadFromFile("files/AdjacencyMatrix.txt", Graph::StructType::AdjacencyList);
}
