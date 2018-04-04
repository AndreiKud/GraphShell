#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <QObject>
#include <QFile>
#include <QDebug>

#include "node.h"
#include "edge.h"

class Graph : public QObject
{
    Q_OBJECT
    Q_ENUMS(StructType)

public:
    enum StructType { EdgeList, AdjacencyList, AdjacencyMatrix };

public:
    Graph();
    virtual ~Graph();

    void ReadFromFile(const QString& str, StructType type);
    void ReadEdgeList(QFile& file);
    void ReadAdjacencyList(QFile& file);
    void ReadAdjacencyMatrix(QFile& file);
    Node* HasNode(int ind);
    Edge* HasEdge(int ind1, int ind2);
    void ToAdjacencyList();

private:
    QSet<Node*> m_Nodes;
    QSet<Edge*> m_Edges;

    QSet<int>* m_AdjList;

//    QList<QPair<QString, QString>> m_EdgeList;
//    QList<QList<short>> m_NodeList;
};

#endif // GRAPHMANAGER_H
