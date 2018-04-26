#include "graph.h"

#define DOUBLE_MAX std::numeric_limits<double>::max()
#define DOUBLE_MIN std::numeric_limits<double>::min()

Graph::Graph() :
    m_bIsOriented(true),
    m_bIsEmpty(true)
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
    emit clear();

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
    qDebug() << "\nMy adjacency list:";
    QString tmp;
    for (QList<Node*>& nodes : m_AdjList)
    {
        tmp = "";
        for (Node* node : nodes)
            tmp += node->getName() + " ";
        qDebug() << tmp.trimmed();
    }
    qDebug() << "\nMy nodes:";
    tmp = "";
    for (Node* node : m_Nodes)
        tmp += node->getName() + " ";
    qDebug() << tmp.trimmed();

    qDebug() << "\nMy edges:";
    for (Edge* edge : m_Edges)
        qDebug() << edge->sourceNode()->getName() + "-" + edge->destNode()->getName();
#endif

    m_bIsEmpty = false;
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
            v1 = new Node(nodeFrom, nodeCount());
            m_Nodes.append(v1);
        }
        if (v2 == nullptr)
        {
            v2 = new Node(nodeTo, nodeCount());
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
            v = new Node(lst[0], nodeCount());
            m_Nodes.append(v);
        }

        int numsCont = lst.size();
        for (int i = 1; i < numsCont - 1; i+=2)
        {
            Node* v1 = hasNode(lst[i]);

            if (v1 == nullptr)
            {
                v1 = new Node(lst[i], nodeCount());
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
                m_Nodes.append(new Node(str, nodeCount()));
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

// TODO: negative/postive
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
                m_Nodes.append(new Node(str, nodeCount()));
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
    }

    for (i = 0; i < m; i++)
    {
        QString v1name = "";
        QString v2name = "";
        QString tmpvals = "";
        double weight = 0.0;
        for (j = 0; j < n; j++)
        {
            tmpvals += QString::number(matr[j][i]) + " ";
            if (qFuzzyIsNull(matr[j][i])) continue;
            weight = matr[j][i];
            if (matr[j][i] < 0)
                v1name = m_Nodes[j]->getName();
            else
                v2name = m_Nodes[j]->getName();
        }
        j--;

        if (hasEdge(v1name, v2name) == nullptr)
        {
            Edge* e = new Edge(hasNode(v1name), hasNode(v2name));
            if (weight < 0) weight *= -1;
            e->setWeight(weight);
            m_Edges.append(e);
        }
    }
    deleteMatrix<double>(matr, n);
}

double Graph::radius()
{
    if (!getIsOriented() && connectedComponents() > 1)
        return -1;

    double rad = DOUBLE_MAX;
    double** distMatr = toAdjacencyMatrix();

    int n = m_AdjList.count();
    double* e = findEccentricity(distMatr);

    for (int i = 0; i < n; i++)
    {
        if (!qFuzzyCompare(e[i], DOUBLE_MAX) && !qFuzzyIsNull(e[i]))
        {
            rad = qMin(rad, e[i]);
        }
    }
//    rad = *std::min_element(e, &e[n]);

    delete[] e;
    deleteMatrix<double>(distMatr, n);

    return rad;
}

double Graph::diameter()
{
    if (!getIsOriented() && connectedComponents() > 1)
        return -1;

    double diam = DOUBLE_MIN;
    double** distMatr = toAdjacencyMatrix();

    int n = m_AdjList.count();
    double* e = findEccentricity(distMatr);

    for (int i = 0; i < n; i++)
    {
        if (!qFuzzyCompare(e[i], DOUBLE_MAX) && !qFuzzyIsNull(e[i]))
        {
            diam = qMax(diam, e[i]);
        }
    }
//    diam = *std::max_element(e, &e[n]);

    if (qFuzzyCompare(diam, DOUBLE_MAX))
        diam = -1;

    delete[] e;
    deleteMatrix<double>(distMatr, n);

    return diam;
}

double *Graph::findEccentricity(double **distMatr)
{
    double maxD = DOUBLE_MAX;
    int n = m_AdjList.count();
    double* e = new double[n];
    for (int i = 0; i < n; i++)
    {
        e[i] = /*distMatr[i][0]*/DOUBLE_MIN;
        for (int j = 0; j < n; j++)
            if (!qFuzzyCompare(maxD, distMatr[i][j]) && !qFuzzyIsNull(distMatr[i][j]))
                e[i] = std::max(e[i], distMatr[i][j]);
    }

    return e;
}

int Graph::lca(int a, int b)
{
    int n = nodeCount();
    QVector<bool> _used(n);
    _used.fill(false);
    for (;;) {
        a = m_Base[a];
        _used[a] = true;
        if (m_Match[a] == -1) break;
        a = m_Pred[m_Match[a]];
    }
    for (;;) {
        b = m_Base[b];
        if (_used[b])  return b;
        b = m_Pred[m_Match[b]];
    }
}

void Graph::markPath(int v, int b, int children)
{
    while (m_Base[v] != b)
    {
        m_Blossom[m_Base[v]] = m_Blossom[m_Base[m_Match[v]]] = true;
        m_Pred[v] = children;
        children = m_Match[v];
        v = m_Pred[m_Match[v]];
    }
}

int Graph::findPath(int root)
{
    m_Used.fill(false);
    m_Pred.fill(-1);
    int n = nodeCount();
    for (int i = 0; i< n; ++i)
        m_Base[i] = i;

    m_Used[root] = true;
    int qh = 0, qt = 0;
    q[qt++] = root;
    while (qh < qt)
    {
        int v = q[qh++];
        for (int i = 1; i < m_AdjList[v].count(); ++i)
        {
            int to = m_AdjList[v][i]->getIndex();
            if (m_Base[v] == m_Base[to] || m_Match[v] == to)
                continue;
            if (to == root || (m_Match[to] != -1 && m_Pred[m_Match[to]] != -1))
            {
                int curbase = lca(v, to);
                m_Blossom.fill(0);
                markPath(v, curbase, to);
                markPath(to, curbase, v);
                for (int i = 0; i < n; ++i)
                {
                    if (m_Blossom[m_Base[i]])
                    {
                        m_Base[i] = curbase;
                        if (!m_Used[i]) {
                            m_Used[i] = true;
                            q[qt++] = i;
                        }
                    }
                }
            }
            else if (m_Pred[to] == -1)
            {
                m_Pred[to] = v;
                if (m_Match[to] == -1)
                    return to;
                to = m_Match[to];
                m_Used[to] = true;
                q[qt++] = to;
            }
        }
    }

    return -1;
}

QVector<int> Graph::start()
{
    int n = nodeCount();
    m_Match.fill(-1);
    for (int i = 0; i< n; i++)
        if (m_Match[i] == -1)
        {
            int v = findPath(i);
            while (v != -1)
            {
                int pv = m_Pred[v], ppv = m_Match[pv];
                m_Match[v] = pv;
                m_Match[pv] = v;
                v = ppv;
            }
        }

    return m_Match;
}

// TODO: matching tests
int Graph::matching()
{
    if (m_bIsOriented)
        return -1;

    int result = 0;
    int n = nodeCount();
    m_Used.resize(n); m_Blossom.resize(n); q.resize(n);
    m_Match.resize(n); m_Pred.resize(n); m_Base.resize(n);

    QVector<int> edges = start();
    QSet<int> exclude;
    emit log("Most matching edges:");
    for (int i = 0; i < n; i++)
    {
        if (edges[i] != -1 && !exclude.contains(i) && !exclude.contains(edges[i]))
        {
            emit log(m_AdjList[i][0]->getName() + '-' + m_AdjList[edges[i]][0]->getName());
            exclude.insert(i);
            exclude.insert(edges[i]);
        }
    }

    return result;
}

int Graph::power()
{
    int max = 0;
    for (QList<QList<Node*>>::const_iterator it = m_AdjList.cbegin(); it != m_AdjList.cend(); ++it)
    {
        int curCnt = 0;
        for (Edge* e : *(*it)[0]->edges())
        {
            if (!e->getIsAdditonal())
                curCnt++;
        }

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
    int res = 0;
    for (Edge* e : m_Edges)
    {
        if (!e->getIsAdditonal())
            res++;
    }
    return res;
}

int Graph::circuitRank()
{
    return edgeCount() - nodeCount() + connectedComponents();
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
            result++;
        }
    }
    return result;
}

int Graph::weaklyConnectedComponents()
{
    if (!m_bIsOriented)
        return -1;

    int result = 0;
    int n = m_AdjList.count();
    bool** attainabilityMatrix = toAttainabilityMatrix(toDistanceMatrix(toAdjacencyMatrix()));
    bool** attainabilityMatrixTrans = new bool*[n];

    for(int i = 0; i < n; i++)
    {
        attainabilityMatrixTrans[i] = new bool[n];
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            attainabilityMatrixTrans[j][i] = attainabilityMatrix[i][j];
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            attainabilityMatrix[i][j] = attainabilityMatrix[i][j] && attainabilityMatrixTrans[i][j];
        }
    }

    QVector<QVector<bool>> attMatrix;
    for(int i = 0; i < n; i++)
    {
        QVector<bool> line;
        for(int j = 0; j < n; j++)
            line.append(attainabilityMatrix[i][j] && attainabilityMatrixTrans[i][j]);
        attMatrix.append(line);
    }

    //подсчет компонент связности
    int index = 0;
    while (attMatrix.length() > 0)
    {
        QList<int> numbers;
        numbers.append(0);
        for (int j = 1; j < attMatrix.length(); j++)
        {
            if (attMatrix[index][j])
            {
                numbers.append(j);
            }
        }

        std::reverse(numbers.begin(), numbers.end());
        for (int number : numbers)
        {
            for (QVector<bool>& vec : attMatrix)
            {
                vec.removeAt(number);
            }
            attMatrix.removeAt(number);
        }

        result++;
    }

    deleteMatrix<bool>(attainabilityMatrix, n);
    deleteMatrix<bool>(attainabilityMatrixTrans, n);
    return result;
}

// FIXME: wrong
void Graph::findCentres()
{
    int n = m_AdjList.count();
    double** distMatr = toAdjacencyMatrix();
    double* e = new double[n];
    double rad = DOUBLE_MAX;

    for (int i = 0; i < n; i++)
    {
        e[i] = DOUBLE_MIN;
        for (int j = 0; j < n; j++)
            if (!qFuzzyIsNull(distMatr[i][j]))
                e[i] = std::max(e[i], distMatr[i][j]);
    }

    for (int i = 0; i < n; i++)
    {
        if (!qFuzzyCompare(e[i], DOUBLE_MAX) && !qFuzzyIsNull(e[i]))
        {
            rad = qMin(rad, e[i]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (qFuzzyCompare(e[i], rad))
            emit log(m_AdjList[i][0]->getName());
    }

    delete[] e;
    deleteMatrix<double>(distMatr, n);
}

bool Graph::isTree()
{
    QList<QList<Node*>>::iterator it;
    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        (*it)[0]->setUsed(false);
    }

    QList<Node*> cycle;
    if (isCyclic(m_AdjList[0].first(), nullptr, &cycle))
        return false;

    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        if (!(*it)[0]->getUsed())
            return false;
    }

    return true;
}

// TODO: absolute center tests
int Graph::absoluteCenter()
{
    int result = 0;

    if ((connectedComponents() > 1) || m_bIsOriented)
        return -1;

    int n = nodeCount();
    double **d = toDistanceMatrix(toAdjacencyMatrix());
    QVector<Center> sentres;
    Center min_dot_on_edge;
    Center s;
    s.maxDist = DOUBLE_MAX;
    bool flag = false;
    min_dot_on_edge.maxDist = DOUBLE_MAX;
    for (QList<Node*> lst : m_AdjList)
    {
        for (Node* nodeTo : lst)
        {
            if (lst[0] == nodeTo)
                continue;

            Edge* edge = hasEdge(lst[0]->getName(), nodeTo->getName());
            Q_CHECK_PTR(edge);

            Center max_dist_dot_ver;
            double e = edge->getWeight();
            for (double j = 0; j <= e; j += 0.01)
            {
                max_dist_dot_ver.maxDist = DOUBLE_MIN;

                for (int i = 0; i < n; i++)
                {
                    double k;
                    k = qMin(j + d[edge->sourceNode()->getIndex()][i], e - j + d[edge->destNode()->getIndex()][i]);
                    if (k > max_dist_dot_ver.maxDist)
                    {
                        max_dist_dot_ver.maxDist = k;
                        max_dist_dot_ver.distFromLeftVert = j;
                        max_dist_dot_ver.e = edge;
                    }
                }
                if (max_dist_dot_ver.maxDist < min_dot_on_edge.maxDist)
                {
                    min_dot_on_edge = max_dist_dot_ver;
                }
                if (!flag && qFuzzyCompare(max_dist_dot_ver.maxDist, min_dot_on_edge.maxDist))
                {
                    flag = true;
                    sentres.push_back(max_dist_dot_ver);
                }
                if (qFuzzyCompare(max_dist_dot_ver.maxDist, s.maxDist))
                {
                    sentres.push_back(max_dist_dot_ver);
                }
            }
            if (min_dot_on_edge.maxDist < s.maxDist)
            {
                s = min_dot_on_edge;
                sentres.clear();
                sentres.push_back(s);
            }
        }
    }

    bool skip = true;
    QSet<Node*> settt;
    for (Center s : sentres)
    {
        if (skip)
        {
            skip = false;
            continue;
        }

        Node* from = s.e->sourceNode();
        Node* to = s.e->destNode();
        if (qFuzzyIsNull(s.distFromLeftVert))
        {
            if (!settt.contains(from))
            {
                log("Absolute center: " + from->getName());
                settt.insert(from);
                log("Absolute radius = " + QString::number(s.maxDist));
            }
        }
        else
        {
            if (qFuzzyCompare(s.distFromLeftVert, s.e->getWeight()))
            {
                if (!settt.contains(to))
                {
                    log("Absolute center: " + to->getName());
                    settt.insert(to);
                    log("Absolute radius = " + QString::number(s.maxDist));
                }
            }
            else
            {
                log("Absolute center is a point on : ("  +
                    from->getName() + ", " + to->getName() +
                    "), value is: " + QString::number(s.distFromLeftVert));
                log("Absolute radius = " + QString::number(s.maxDist));
            }
        }
    }

    return result;
}

QList<Node *> *Graph::getNodes()
{
    return &m_Nodes;
}

QList<Edge *> *Graph::getEdges()
{
    return &m_Edges;
}

bool Graph::getIsEmpty() const
{
    return m_bIsEmpty;
}

// FIXME: smth strange
bool Graph::isCyclic(Node* v, Node* parent, QList<Node*>* cycle)
{
    v->setUsed(true);
    QList<Edge*>* incEdges = v->edges();
    QList<Edge*>::const_iterator it;
    for (it = incEdges->cbegin(); it != incEdges->cend(); ++it)
    {
        if ((*it)->sourceNode() != v)
            continue;

        Node* to = (*it)->destNode();
        cycle->append(to);
        if (!to->getUsed())
        {
           if (isCyclic(to, v, cycle))
              return true;
        }
        else if (to != parent)
        {
            emit log("Cycle: ");
            QString cstr = "";
            for (Node* node : *cycle)
            {
                cstr += node->getName() + " - ";
            }
            emit log(cstr.remove(cstr.length() - 3, 3));
            cycle->clear();
            return true;
        }
    }
    cycle->clear();
    return false;
}

void Graph::DFS(Node* v, bool bLogging /*= false*/)
{
    v->setUsed(true);
    m_Comp.push_back(v);
    QList<Edge*>::const_iterator it;
    QList<Edge*>* incEdges = v->edges();
    for (it = incEdges->cbegin(); it != incEdges->cend(); ++it)
    {
        Node* to = (*it)->destNode();

        if (to == v)
            continue;

        if (bLogging)
            emit log(to->getName());
        if (!to->getUsed())
            DFS(to, bLogging);
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

int Graph::addNode(const QString &name)
{
    if (name.isEmpty())
    {
        return EMPTY_NODE_NAME;
    }

    if (hasNode(name) != nullptr)
    {
        return SPECIFIED_NODE_ALREADY_EXISTS;
    }

    Node* newNode = new Node(name, nodeCount());
    QList<Node*> newNodeLst;
    newNodeLst.append(newNode);
    m_AdjList.append(newNodeLst);
    m_Nodes.append(newNode);
    return OK;
}

int Graph::deleteNode(const QString &name)
{
    if (name.isEmpty())
    {
        return EMPTY_NODE_NAME;
    }

    Node* dNode = hasNode(name);
    if (dNode == nullptr)
    {
        return SPECIFIED_NODE_NOT_FOUND;
    }

    for (QList<Node*>& lst : m_AdjList)
    {
        for (Node* node : lst)
        {
            if (node == lst[0])
                continue;

            if (node == dNode)
                lst.removeOne(dNode);
        }

        if (dNode == lst[0])
            m_AdjList.removeOne(lst);
    }

    for (QList<Node*>& lst : m_AdjList)
    {
        deleteEdge(lst[0]->getName(), dNode->getName());
        deleteEdge(dNode->getName(), lst[0]->getName());
    }

    m_Nodes.removeOne(dNode);
    return OK;
}

int Graph::addEdge(const QString &nameFrom, const QString &nameTo, double weight, bool bIsAdditional/* = false*/)
{
    if (nameFrom.isEmpty())
    {
        return EMPTY_NODE_NAME;
    }
    if (nameTo.isEmpty())
    {
        return EMPTY_NODE_NAME;
    }

    if (hasEdge(nameFrom, nameTo) != nullptr)
    {
        return SPECIFIED_EDGE_ALREADY_EXISTS;
    }

    Node* nodeFrom = hasNode(nameFrom);
    Node* nodeTo = hasNode(nameTo);

    if (nodeFrom == nullptr)
    {
        return SPECIFIED_NODE_FROM_NOT_FOUND;
    }
    if (nodeTo == nullptr)
    {
        return SPECIFIED_NODE_TO_NOT_FOUND;
    }

    for (QList<Node*>& lst : m_AdjList)
    {
        if (lst[0] == nodeFrom && !lst.contains(nodeTo))
            lst.append(nodeTo);

        if (!getIsOriented())
        {
            if (lst[0] == nodeTo && !lst.contains(nodeFrom))
                lst.append(nodeFrom);
        }
    }

    Edge* newEdge = new Edge(nodeFrom, nodeTo);
    newEdge->setWeight(weight);
    newEdge->setIsAdditonal(bIsAdditional);
    if (!m_Edges.contains(newEdge))
        m_Edges.append(newEdge);

    return OK;
}

int Graph::deleteEdge(const QString &nameFrom, const QString &nameTo)
{
    if (nameFrom.isEmpty())
    {
        return EMPTY_NODE_NAME;
    }
    if (nameTo.isEmpty())
    {
        return EMPTY_NODE_NAME;
    }

    Edge* delEdge = hasEdge(nameFrom, nameTo);

    if (delEdge == nullptr)
    {
        return SPECIFIED_EDGE_NOT_FOUND;
    }

    Node* nodeFrom = hasNode(nameFrom);
    Node* nodeTo = hasNode(nameTo);

    if (nodeFrom == nullptr)
    {
        return SPECIFIED_NODE_FROM_NOT_FOUND;
    }
    if (nodeTo == nullptr)
    {
        return SPECIFIED_NODE_TO_NOT_FOUND;
    }

    for (QList<Node*>& lst : m_AdjList)
    {
        if (nodeFrom == lst[0])
        {
            nodeFrom->edges()->removeOne(delEdge);
            nodeTo->edges()->removeOne(delEdge);
            lst.removeOne(nodeTo);
        }

        if (!getIsOriented())
        {
            if (lst[0] == nodeTo)
            {
                nodeFrom->edges()->removeOne(delEdge);
                nodeTo->edges()->removeOne(delEdge);
                lst.removeOne(nodeFrom);
            }
        }
    }

    m_Edges.removeOne(delEdge);

    return OK;
}

void Graph::unuseNodes()
{
    QList<QList<Node*>>::iterator it;
    for (it = m_AdjList.begin(); it != m_AdjList.end(); ++it)
    {
        (*it)[0]->setUsed(false);
    }
}

void Graph::toAdjacencyList()
{
    m_AdjList.clear();

    for (Node* n : m_Nodes)
    {
        QList<Node*> adjNodes;
        adjNodes.append(n);
        for (const Edge* e : *n->edges())
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

    qDebug() << "\nMy adjacency matrix:\n";
    for (int i = 0; i < n; i++)
    {
        QString tmp = " ";
        for (int j = 0; j < n; j++)
            tmp += QString::number(result[i][j]) + " ";
        qDebug() << tmp.trimmed();
    }

    return toDistanceMatrix(result);
}

bool **Graph::toAttainabilityMatrix(double **distanceMatrix)
{
    int n = m_AdjList.count();
    bool** result = new bool*[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = new bool[n];
        for (int j = 0; j < n; j++)
        {
            if (!qFuzzyCompare(distanceMatrix[i][j], DOUBLE_MAX))
            {
                result[i][j] = true;
            }
            else
            {
                result[i][j] = false;
            }
        }
    }

    deleteMatrix<double>(distanceMatrix, n);
    return result;
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
                result[i][j] = DOUBLE_MAX;
            if (i == j)
                result[i][j] = 0;
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);

    deleteMatrix<double>(adjacencyMatrix, n);
    return result;
}

bool Graph::getIsOriented() const
{
    return m_bIsOriented;
}

void Graph::setIsOriented(bool bIsOriented)
{
    m_bIsOriented = bIsOriented;

    for (QList<Node*>& lst : m_AdjList)
    {
        for (Node* node : lst)
        {
            if (node == lst[0])
                continue;

            Edge* e = hasEdge(lst[0]->getName(), node->getName());
            Q_CHECK_PTR(e);
            if (!bIsOriented)
            {
                addEdge(node->getName(), lst[0]->getName(), e->getWeight(), true);
            }
            else
            {
                if (e->getIsAdditonal())
                {
                    deleteEdge(lst[0]->getName(), node->getName());
                }
            }
        }
    }
}

template<typename T>
void Graph::deleteMatrix(T** matr, int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
}
