#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QFile>
#include <QDebug>

#include "node.h"
#include "edge.h"
#include "resources.h"

struct Center
{
    Edge* e = nullptr;
    double distFromLeftVert = 0;
    double maxDist = 0;
};

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
    int weaklyConnectedComponents();
    void findCentres();
    bool isTree();
    int absoluteCenter();
    int matching();

    QList<Node*>* getNodes();
    QList<Edge*>* getEdges();
    bool getIsEmpty() const;
    Node* hasNode(const QString& name);
    Edge* hasEdge(const QString& name1, const QString& name2);
    int addNode(const QString& name);
    int deleteNode(const QString& name);
    int addEdge(const QString& nameFrom, const QString& nameTo, double weight, bool bIsAdditional = false);
    int deleteEdge(const QString& nameFrom, const QString& nameTo);

    void unuseNodes();
    void DFS(Node* v, bool bLogging = false);
    void toAdjacencyList();
    double** toAdjacencyMatrix();
    double** toDistanceMatrix(double** adjacencyMatrix);
    bool** toAttainabilityMatrix(double** distanceMatrix);

    bool getIsOriented() const;
    void setIsOriented(bool bIsOriented);

private:
    bool isCyclic(Node *v, Node *parent, QList<Node*>* cycle);
    double* findEccentricity(double** distMatr);

    int lca(int a, int b);
    void markPath(int v, int b, int children);
    int findPath(int root);
    QVector<int> start();

    template<typename T>
    void deleteMatrix(T** matr, int cnt);

signals:
    void log(const QString &text);
    void clear();

private:
    QList<Node*> m_Nodes;
    QList<Edge*> m_Edges;
    QList<QList<Node*>> m_AdjList;
    QVector<Node*> m_Comp;
    bool m_bIsOriented;
    bool m_bIsEmpty;

    /*
     * m_Match - для каждой вершины содержит смежную ей в паросочетании
     * m_Pred - массив предков, в котором для каждой нечётной вершины (т.е. до которой расстояние в дереве путей нечётно, т.е. это первые концы рёбер в паросочетании) будем хранить предка - чётную вершину.
     * m_Blossom - вершины, принадлежащие текущему цветку.
     * m_Used - пройденные вершины.
     * m_Base - база (начало цикла).
     */
    QVector<int> m_Match, m_Pred, m_Base, q;
    QVector<bool> m_Used, m_Blossom;
//    QVector<QVector<int>> g;
};

#endif // GRAPHMANAGER_H
