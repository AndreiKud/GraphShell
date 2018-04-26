#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Graph Shell"));
    connect(&m_Graph, &Graph::log, this, &MainWindow::log);
    connect(&m_Graph, &Graph::clear, this, &MainWindow::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graph;
}

void MainWindow::log(const QString &text)
{
    ui->pteOther->appendPlainText(text);
}

void MainWindow::clear()
{
    ui->pteOther->clear();
    ui->leNodesCnt->clear();
    ui->leEdgesCnt->clear();
    ui->leRadius->clear();
    ui->leDiameter->clear();
    ui->leConnectedComponent->clear();
    ui->leIsTree->clear();
    ui->leGraphPower->clear();
    ui->leCircuitRank->clear();
}

void MainWindow::on_pbVizualize_clicked()
{
    if (graph != nullptr)
    {
        graph->close();
    }

    graph = new GraphWidget();

    for (Edge* e : *m_Graph.getEdges())
    {
        graph->scene()->addItem(e);
    }
    for (Node* n : *m_Graph.getNodes())
    {
        graph->scene()->addItem(n);
    }
    graph->shuffle();
    graph->show();
    graph->invalidateScene();
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
    clear();
    if (m_Graph.getIsEmpty())
        return;

    setCursor(Qt::CursorShape::WaitCursor);
    ui->leNodesCnt->setText(QString::number(m_Graph.nodeCount()));
    ui->leEdgesCnt->setText(QString::number(m_Graph.edgeCount()));
    double d = m_Graph.diameter();
    QString diamStr = qFuzzyCompare(d, -1.0) ? "inf" : QString::number(d);
    ui->leDiameter->setText(diamStr);
    ui->leGraphPower->setText(QString::number(m_Graph.power()));
    double r = m_Graph.radius();
    QString radStr = qFuzzyCompare(r, -1.0) ? "inf" : QString::number(r);
    ui->leRadius->setText(radStr);

    if (!m_Graph.getIsOriented())
    {
        ui->leCircuitRank->setText(QString::number(m_Graph.circuitRank()));
    }
    else
    {
        ui->leCircuitRank->setText("graph is oriented");
    }

    int compCount = 0;
    if (m_Graph.getIsOriented())
    {
        compCount = m_Graph.weaklyConnectedComponents();
    }
    else
    {
        compCount = m_Graph.connectedComponents();
    }
    ui->leConnectedComponent->setText(QString::number(compCount));

    QString isTree = m_Graph.isTree() ? "Yes" : "No";
    ui->leIsTree->setText(isTree);

    ui->pteOther->appendPlainText("Centres:");
    m_Graph.findCentres();
    m_Graph.absoluteCenter();
    m_Graph.matching();
    setCursor(Qt::CursorShape::ArrowCursor);
}

void MainWindow::on_rbOrient_clicked()
{
    clear();
    m_Graph.setIsOriented(true);
    ui->lblConnectedComponent->setText("Strongly conn. comp:");
}

void MainWindow::on_rbNotOrient_clicked()
{
    clear();
    m_Graph.setIsOriented(false);
    ui->lblConnectedComponent->setText("Conn. comp:");
}

void MainWindow::on_pbAddNode_clicked()
{
    QString newNodeName = ui->leNode->text();
    int res = m_Graph.addNode(newNodeName);

    if (res != OK)
    {
        showErr(res);
    }
}

void MainWindow::on_pbDeleteNode_clicked()
{
    QString deleteNodeName = ui->leNode->text();
    int res = m_Graph.deleteNode(deleteNodeName);

    if (res != OK)
    {
        showErr(res);
    }
}

void MainWindow::on_pbAddEdge_clicked()
{
    QString nodeFromName = ui->leNodeFromName->text();
    QString nodeToName = ui->leNodeToName->text();
    double edgeWeight = ui->leEdgeWeight->text().toDouble();

    int res = m_Graph.addEdge(nodeFromName, nodeToName, edgeWeight);

    if (res != OK)
    {
        showErr(res);
    }
}

void MainWindow::on_pbDeleteEdge_clicked()
{
    QString nodeFromName = ui->leNodeFromName->text();
    QString nodeToName = ui->leNodeToName->text();
    int res = m_Graph.deleteEdge(nodeFromName, nodeToName);

    if (res != OK)
    {
        showErr(res);
    }
}

void MainWindow::on_pbDFS_clicked()
{
    QString nodeName = ui->leDFSNodeFrom->text();
    Node* node = m_Graph.hasNode(nodeName);

    if (node == nullptr)
    {
        showErr(SPECIFIED_NODE_NOT_FOUND);
        return;
    }

    ui->pteOther->appendPlainText("DFS from " + nodeName + ":");
    m_Graph.unuseNodes();
    m_Graph.DFS(node, true);
}

void MainWindow::showErr(int errCode)
{
    switch (errCode)
    {
        case SPECIFIED_NODE_NOT_FOUND:
        {
            QMessageBox::warning(this, "Operation failed", "Specified node not found");
            break;
        }
        case SPECIFIED_NODE_ALREADY_EXISTS:
        {
            QMessageBox::warning(this, "Operation failed", "Specified node already exists");
            break;
        }
        case SPECIFIED_NODE_FROM_NOT_FOUND:
        {
            QMessageBox::warning(this, "Operation failed", "Specified node FROM not found");
            break;
        }
        case SPECIFIED_NODE_TO_NOT_FOUND:
        {
            QMessageBox::warning(this, "Operation failed", "Specified node TO not found");
            break;
        }
        case SPECIFIED_EDGE_NOT_FOUND:
        {
            QMessageBox::warning(this, "Operation failed", "Specified edge not found");
            break;
        }
        case SPECIFIED_EDGE_ALREADY_EXISTS:
        {
            QMessageBox::warning(this, "Operation failed", "Specified edge already exists");
            break;
        }
        case EMPTY_NODE_NAME:
        {
            QMessageBox::warning(this, "Operation failed", "Node name cannot be empty");
            break;
        }
    }
}
