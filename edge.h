#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
    enum { Type = UserType + 2 };

public:
    Edge(Node *sourceNode, Node *destNode);
    ~Edge() override;

    Node* sourceNode() const;
    Node* destNode() const;

    void adjust();

    int type() const override { return Type; }
    void setWeight(double rWeight) { m_dWeight = rWeight; }
    double getWeight() { return m_dWeight; }

    bool getIsAdditonal() const;
    void setIsAdditonal(bool bIsAdditonal);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Node *source = nullptr, *dest = nullptr;

    QPointF m_SourcePoint;
    QPointF m_DestPoint;
    double arrowSize;
    double m_dWeight;
    bool m_bIsAdditonal;
};

#endif // EDGE_H
