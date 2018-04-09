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

void MainWindow::on_actionEdge_List_triggered()
{
    m_Graph.readFromFile("files/EdgeList.txt", StructType::EdgeList);
}

void MainWindow::on_actionAdjacency_List_triggered()
{
    m_Graph.readFromFile("files/AdjacencyList.txt", StructType::AdjacencyList);
}

void MainWindow::on_actionIncidence_Matrix_triggered()
{
    m_Graph.readFromFile("files/IncidenceMatrix.txt", StructType::IncidenceMatrix);
}

void MainWindow::on_actionAdjacency_Matrix_triggered()
{
    m_Graph.readFromFile("files/AdjacencyMatrix.txt", StructType::AdjacencyMatrix);
}

void MainWindow::on_pbCalcMetrics_clicked()
{
    ui->leNodesCnt->setText(QString::number(m_Graph.nodeCount()));
    ui->leEdgesCnt->setText(QString::number(m_Graph.edgeCount()));
    ui->leDiameter->setText(QString::number(m_Graph.diameter()));
    ui->leGraphPower->setText(QString::number(m_Graph.power()));
    ui->leRadius->setText(QString::number(m_Graph.radius()));
    ui->leCircuitRank->setText(QString::number(m_Graph.circuitRank()));
    ui->leConnectedComponent->setText(QString::number(m_Graph.connectedComponents()));

    QString isTree = m_Graph.isTree() ? "Yes" : "No";
    ui->leIsTree->setText(isTree);
}
