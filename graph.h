#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <QObject>
#include <QFile>
#include <QDebug>

#include "node.h"
#include "edge.h"

enum class StructType
{
    EdgeList,
    AdjacencyList,
    AdjacencyMatrix,
    IncidenceMatrix
};

class Graph : public QObject
{
    Q_OBJECT
    Q_ENUMS(StructType)

public:
    Graph();
    virtual ~Graph();

    void readFromFile(const QString& str, StructType type);
    void readEdgeList(QFile& file);
    void readAdjacencyList(QFile& file);
    void readAdjacencyMatrix(QFile& file);
    void readIncidenceMatrix(QFile& file);

    double radius();
    double diameter();
    int power();
    int nodeCount();
    int edgeCount();
    int circuitRank();
    int connectedComponents();
    bool isTree();

    Node* hasNode(const QString& name);
    Edge* hasEdge(const QString& name1, const QString& name2);
    void toAdjacencyList();
    double** toAdjacencyMatrix();
    double** toDistanceMatrix(double** adjacencyMatrix);

private:
    void DFS(Node* v);
    bool isCyclic(Node *v, Node *parent);
    double* findEccentricity(double** distMatr);
    void deleteMatrix(double** matr, int cnt);

private:
    QList<Node*> m_Nodes;
    QList<Edge*> m_Edges;
    QList<QList<Node*>> m_AdjList;
    QVector<Node*> m_Comp;
};

#endif // GRAPHMANAGER_H
