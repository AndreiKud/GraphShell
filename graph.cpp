#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::readFromFile(const QString &str, StructType type)
{
    QFile file(str);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << file.errorString();
        return;
    }
    m_Nodes.clear();
    m_Edges.clear();

    switch (type)
    {
        case StructType::EdgeList:
            readEdgeList(file);
            break;
        case StructType::AdjacencyList:
            readAdjacencyList(file);
            break;
        case StructType::IncidenceMatrix:
            readIncidenceMatrix(file);
            break;
        case StructType::AdjacencyMatrix:
            readAdjacencyMatrix(file);
            break;
    }

    toAdjacencyList();

#ifdef QT_DEBUG
    foreach (QList<Node*> nodes, m_AdjList)
    {
        QString tmp;
        foreach (Node* node, nodes)
            tmp += node->getName() + " ";
        qDebug() << tmp.trimmed();
    }
#endif

    file.close();
}

void Graph::readEdgeList(QFile& file)
{
    while (!file.atEnd())
    {
        QString line = file.readLine();
        QStringList eInfo = line.split(" ");
        QString nodeFrom = eInfo[0];
        QString nodeTo = eInfo[1];
        double weight = eInfo[2].toDouble();

        Node *v1, *v2;
        v1 = hasNode(nodeFrom);
        v2 = hasNode(nodeTo);

        if (v1 == nullptr)
        {
            v1 = new Node(nodeFrom);
            m_Nodes.append(v1);
        }
        if (v2 == nullptr)
        {
            v2 = new Node(nodeTo);
            m_Nodes.append(v2);
        }

        if (hasEdge(v1->getName(), v2->getName()) == nullptr)
        {
            Edge* edge = new Edge(v1, v2);
            edge->setWeight(weight);
            m_Edges.append(edge);
        }
    };
}

void Graph::readAdjacencyList(QFile& file)
{
    while (!file.atEnd())
    {
        QString line = file.readLine();
        QStringList lst = line.split(" ");
        Node* v = hasNode(lst[0]);
        if (v == nullptr)
        {
            v = new Node(lst[0]);
            m_Nodes.append(v);
        }

        int numsCont = lst.size();
        for (int i = 1; i < numsCont - 1; i+=2)
        {
            Node* v1 = hasNode(lst[i]);

            if (v1 == nullptr)
            {
                v1 = new Node(lst[i]);
                m_Nodes.append(v1);
            }

            double weight = lst[i + 1].toDouble();
            if (hasEdge(lst[0], lst[i]) == nullptr)
            {
                Edge* e = new Edge(v, v1);
                e->setWeight(weight);
                m_Edges.append(e);
            }
        }
    };
}

void Graph::readAdjacencyMatrix(QFile& file)
{
    if (!file.atEnd())
    {
        QString line = file.readLine();
        for (const QString& str : line.split(" "))
        {
            if (hasNode(str) == nullptr)
                m_Nodes.append(new Node(str));
        }
    }

    short cnt = 0;
    while (!file.atEnd())
    {
        QString line = file.readLine();
        QStringList lst = line.split(" ");

        int numsCont = lst.size();
        for (int i = 0; i < numsCont; i++)
        {
            if (lst[i].trimmed() == "0") continue;

            double weight = lst[i].toDouble();
            if (hasEdge(m_Nodes[cnt]->getName(), m_Nodes[i]->getName()) == nullptr)
            {
                Edge* e = new Edge(m_Nodes[cnt], m_Nodes[i]);
                e->setWeight(weight);
                m_Edges.append(e);
            }
        }
        cnt++;
    };
}

void Graph::readIncidenceMatrix(QFile &file)
{
    int n(0), m(0);
    QString lineNums = file.readLine();
    QStringList lstNums = lineNums.split(" ");
    n = lstNums[0].toInt();
    m = lstNums[1].toInt();

    if (!file.atEnd())
    {
        QString line = file.readLine();
        for (const QString& str : line.split(" "))
        {
            if (hasNode(str) == nullptr)
                m_Nodes.append(new Node(str));
        }
    }

    int i = 0, j = 0;
    double** matr= new double*[n];
    while (!file.atEnd())
    {
        QString line = file.readLine();
        QStringList nums = line.split(" ");
        matr[i] = new double[m];
        j = 0;
        for (const QString& str : nums)
        {
            matr[i][j] = str.toDouble();
            j++;
        }
        i++;

#ifdef QT_DEBUG
        QString tmp = "";
        for (const QString& str : nums)
        {
            tmp += str.trimmed() + " ";
        }
        qDebug() << tmp.trimmed();
#endif
    }

    qDebug() << "\n";
    for (i = 0; i < n; i++)
    {
        QString v1name = "";
        QString v2name = "";
        QString tmpvals = "";
        for (j = 0; j < m; j++)
        {
            tmpvals += QString::number(matr[j][i]) + " ";
            if (qFuzzyIsNull(matr[j][i])) continue;
            if (v1name == "")
                v1name = m_Nodes[j]->getName();
            else
                v2name = m_Nodes[j]->getName();
        }
        qDebug() << tmpvals;
        j--;

        if (hasEdge(v1name, v2name) == nullptr)
        {
            Edge* e = new Edge(hasNode(v1name), hasNode(v2name));
            e->setWeight(matr[j][i]);
            m_Edges.append(e);
        }
    }
}

double Graph::radius()
{
    double rad = std::numeric_limits<double>::max();
    double** distMatr = toAdjacencyMatrix();

    int n = m_AdjList.count();
    double* e = findEccentricity(distMatr);

    rad = *std::min_element(e, &e[n]);

    delete[] e;
    deleteMatrix(distMatr, n);

    return rad;
}

double Graph::diameter()
{
    double diam = std::numeric_limits<double>::min();
    double** distMatr = toAdjacencyMatrix();

    int n = m_AdjList.count();
    double* e = findEccentricity(distMatr);

    diam = *std::max_element(e, &e[n]);

    if (qFuzzyCompare(diam, std::numeric_limits<double>::max()))
        diam = -1;

    delete[] e;
    deleteMatrix(distMatr, n);

    return diam;
}

double *Graph::findEccentricity(double **distMatr)
{
    double maxD = std::numeric_limits<double>::max();
    int n = m_AdjList.count();
    double* e = new double[n];
    for (int i = 0; i < n; i++)
    {
        e[i] = distMatr[i][0];
        for (int j = 0; j < n; j++)
            if (!qFuzzyCompare(maxD, distMatr[i][j]) && !qFuzzyIsNull(distMatr[i][j]))
                e[i] = std::max(e[i], distMatr[i][j]);
    }

    return e;
}

int Graph::power()
{
    int max = 0;
    for (QList<QList<Node*>>::const_iterator it = m_AdjList.cbegin(); it != m_AdjList.cend(); ++it)
    {
        int curCnt = (*it).count();
        if (curCnt > max)
            max = curCnt;
    }
    return max;
}

int Graph::nodeCount()
{
    return m_Nodes.count();
}

int Graph::edgeCount()
{
    return m_Edges.count();
}

int Graph::circuitRank()
{
    return m_Edges.count() - m_Nodes.count() + connectedComponents();
}

int Graph::connectedComponents()
{
    int result = 0;
    QList<QList<Node*>>::iterator it;
    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        (*it)[0]->setUsed(false);
    }
    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        if (!(*it)[0]->getUsed())
        {
            m_Comp.clear();
            DFS((*it)[0]);

#ifdef QT_DEBUG
            qDebug() << "Component:";
            QList<Node*>::iterator it2;
            for (it2 = (*it).begin(); it2 != (*it).end(); ++it2)
                qDebug() <<  (*it2)->getName();
            result++;
#endif
        }
    }
    return result;
}

bool Graph::isTree()
{
    QList<QList<Node*>>::iterator it;
    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        (*it)[0]->setUsed(false);
    }

    if (isCyclic(m_AdjList[0].first(), nullptr))
        return false;

    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        if (!(*it)[0]->getUsed())
            return false;
    }

    return true;
}

bool Graph::isCyclic(Node* v, Node* parent)
{
    v->setUsed(true);
    QList<Edge*> incEdges = v->edges();
    QList<Edge*>::const_iterator it;
    for (it = incEdges.cbegin(); it != incEdges.cend(); ++it)
    {
        Node* to = (*it)->destNode();
        if (!to->getUsed())
        {
           if (isCyclic(to, v))
              return true;
        }
        else if (to != parent)
           return true;
    }
    return false;
}

void Graph::DFS(Node* v)
{
    v->setUsed(true);
    m_Comp.push_back(v);
    QList<Edge*>::const_iterator it;
    QList<Edge*> incEdges = v->edges();
    for (it = incEdges.cbegin(); it != incEdges.cend(); ++it)
    {
        Node* to = (*it)->destNode();
        if (!to->getUsed())
            DFS(to);
    }
}

Node* Graph::hasNode(const QString& name)
{
    for (Node* n : m_Nodes)
    {
        if (n->getName() == name.trimmed())
            return n;
    }

    return nullptr;
}

Edge* Graph::hasEdge(const QString& name1, const QString& name2)
{
    for (Edge* e : m_Edges)
    {
        if (e->sourceNode()->getName() == name1 && e->destNode()->getName() == name2)
            return e;
    }

    return nullptr;
}

void Graph::toAdjacencyList()
{
    m_AdjList.clear();

    for (Node* n : m_Nodes)
    {
        QList<Node*> adjNodes;
        adjNodes.append(n);
        for (const Edge* e : n->edges())
        {
            Node* add;
            if (e->destNode() != n)
                add = e->destNode();

            if (!adjNodes.contains(add))
                adjNodes.append(add);
        }
        m_AdjList.append(adjNodes);
    }
}

double** Graph::toAdjacencyMatrix()
{
    int n = m_AdjList.count();
    double** result = new double*[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = new double[n];
        for (int j = 0; j < n; j++)
            result[i][j] = 0;
    }

    int cnt = 0;
    foreach (const QList<Node*>& vec1, m_AdjList)
    {
        foreach (const Node* node, vec1)
        {
            if (vec1[0] == node) continue;

            int ind = 0;
            foreach (const QList<Node*>& vec2, m_AdjList)
            {
                QString n1 = node->getName();
                QString n2 = vec2[0]->getName();
                if (vec2[0] == node)
                {
                    Edge* e = hasEdge(vec1[0]->getName(), node->getName());
                    if (e != nullptr)
                        result[cnt][ind] = e->getWeight();
                    break;
                }
                ind++;
            }
        }
        cnt++;
    }

    qDebug() << "\n";
    for (int i = 0; i < n; i++)
    {
        QString tmp = " ";
        for (int j = 0; j < n; j++)
            tmp += QString::number(result[i][j]) + " ";
        qDebug() << tmp.trimmed();
    }

    return toDistanceMatrix(result);
}

double** Graph::toDistanceMatrix(double** adjacencyMatrix)
{
    int n = m_AdjList.count();
    double** result = new double*[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            if (!qFuzzyIsNull(adjacencyMatrix[i][j]))
                result[i][j] = adjacencyMatrix[i][j];
            else
                result[i][j] = std::numeric_limits<double>::max();
            if (i == j)
                result[i][j] = 0;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);

    deleteMatrix(adjacencyMatrix, n);
    return result;
}

void Graph::deleteMatrix(double** matr, int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
}
