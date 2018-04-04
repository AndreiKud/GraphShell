#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
    delete[] m_AdjList;
}

void Graph::ReadFromFile(const QString &str, Graph::StructType type)
{
    QFile file(str);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        return;
    }
    m_Nodes.values().clear();
    m_Edges.values().clear();

    switch (type)
    {
    case Graph::EdgeList:
        ReadEdgeList(file);
        break;
    case Graph::AdjacencyList:
        ReadAdjacencyList(file);
        break;
    case Graph::AdjacencyMatrix:
        ReadAdjacencyMatrix(file);
        break;
    }

    ToAdjacencyList();
    file.close();
}

void Graph::ReadEdgeList(QFile& file)
{
    while (!file.atEnd())
    {
        QString line = file.readLine();
        QList<QString> vpair = line.split(" ");
        short ind1 = vpair.first().toShort();
        short ind2 = vpair.last().toShort();
        Node *v1, *v2;
        v1 = new Node(ind1);
        v2 = new Node(ind2);

        m_Nodes.values().append(v1);
        m_Nodes.values().append(v2);
        m_Edges.values().append(new Edge(v1, v2));
    };
}

void Graph::ReadAdjacencyList(QFile& file)
{
    while (!file.atEnd())
    {
        QString line = file.readLine();
        Node* v = new Node(m_Nodes.count());
        m_Nodes.values().append(v);

        QList<short> vlist;
        foreach (QString vert, line.split(" "))
        {
            Edge* e;
            if (Node* v1 = HasNode(vert.toShort()))
            {
                e = new Edge(v, v1);
            }
            else
            {
                Node* v2 = new Node(vert.toShort());
                e = new Edge(v, v2);
            }

            if (!HasEdge(m_Nodes.count(), vert.toShort()))
                m_Edges.values().append(e);
        }
    };
}

void Graph::ReadAdjacencyMatrix(QFile& file)
{
    while (!file.atEnd())
    {
        QString line = file.readLine();
        Node* v = new Node(m_Nodes.count());
        m_Nodes.values().append(v);

        QList<short> vlist;
        foreach (QString vert, line.split(" "))
        {
            Edge* e;
            if (Node* v1 = HasNode(vert.toShort()))
            {
                e = new Edge(v, v1);
            }
            else
            {
                Node* v2 = new Node(vert.toShort());
                e = new Edge(v, v2);
            }

            if (!HasEdge(m_Nodes.count(), vert.toShort()))
                m_Edges.values().append(e);
        }
    };
}

Node *Graph::HasNode(int ind)
{
    foreach (Node* n, m_Nodes.values())
    {
        if (n->Index() == ind) return n;
    }

    return nullptr;
}

Edge *Graph::HasEdge(int ind1, int ind2)
{
    foreach (Edge* e, m_Edges.values())
    {
        if (e->sourceNode()->Index() == ind1 && e->destNode()->Index() == ind2) return e;
    }

    return nullptr;
}

void Graph::ToAdjacencyList()
{
    m_AdjList = new QSet<int>[m_Edges.count()];

    foreach (Edge* e, m_Edges)
    {
        m_AdjList[e->sourceNode()->Index()].insert(e->destNode()->Index());
    }
}
