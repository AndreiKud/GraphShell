#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::ReadFromFile(const QString &str, StructType type)
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
        case StructType::EdgeList:
            ReadEdgeList(file);
            break;
        case StructType::AdjacencyList:
            ReadAdjacencyList(file);
            break;
        case StructType::AdjacencyMatrix:
            ReadAdjacencyMatrix(file);
            break;
        case StructType::IncidenceMatrix:
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
        QStringList eInfo = line.split(" ");
        QString nodeFrom = eInfo[0];
        QString nodeTo = eInfo[1];
        double weight = eInfo[2].toDouble();

        Node *v1, *v2;
        v1 = new Node(nodeFrom);
        v2 = new Node(nodeTo);

        m_Nodes.values().append(v1);
        m_Nodes.values().append(v2);
        Edge* edge = new Edge(v1, v2);
        edge->SetWeight(weight);
        m_Edges.values().append(edge);
    };
    ToAdjacencyList();
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
    ToAdjacencyList();
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
    ToAdjacencyList();
}

void Graph::ReadIncidenceMatrix(QFile &file)
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
    ToAdjacencyList();
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
    m_AdjList.clear();

    foreach (Edge* e, m_Edges)
    {

//        m_AdjList[e->sourceNode()->Index()].insert(e->destNode()->Index());
    }
}
