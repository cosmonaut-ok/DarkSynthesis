#include <QtWidgets>

#include "physbaseitem.h"
#include "cartesianlabel.h"
#include "cartesiangraph.h"
#include "cartesiangraphdataobj.h"
#include "physparticle.h"
#include "physvector.h"
#include "graphwidget.h"

std::map<int, QString> CartesianGraph::m_listEditableProps = {
    {0, QString("X-Axis Label")},
    {1, QString("Y-Axis Label")},
    {2, QString("Axis Tick Increment")},
    {3, QString("X-Axis Extent")},
    {4, QString("Y-Axis Extent")}
};

CartesianGraph::CartesianGraph(GraphWidget *pGraphWidget, const QString &Name, CartesianGraphDataObj *pDataObj)  : QGraphicsItem() {
    m_pGraphWidget = pGraphWidget;
    m_pDataObj = (pDataObj) ? pDataObj : new CartesianGraphDataObj(Name);
    m_borderWidth = 5;
    m_x_label = new CartesianLabel(QString("x: <Enter label>"), this);
    m_y_label = new CartesianLabel(QString("y: <Enter label>"), this);
    m_x_label -> setPos(QPointF(200 + m_borderWidth, 0));
    m_y_label -> setPos(QPointF(0, 200 + m_borderWidth));

    // Draw the text for the extents
    QRectF rc = boundingRect();
    m_pXMin = new CartesianLabel(QString::number(m_pDataObj -> xMin()), this);
    m_pXMax = new CartesianLabel(QString::number(m_pDataObj -> xMax()), this);
    m_pYMin = new CartesianLabel(QString::number(m_pDataObj -> yMin()), this);
    m_pYMax = new CartesianLabel(QString::number(m_pDataObj -> yMax()), this);
    m_pXMin -> setPos(QPointF(rc.x() - (m_pXMin -> boundingRect().width() / 2), -(m_pXMin -> boundingRect().height() / 2)));
    m_pXMax -> setPos(QPointF(rc.width() - (m_pXMax -> boundingRect().width() / 2), -(m_pXMax -> boundingRect().height() / 2)));
    m_pYMin -> setPos(QPointF(m_pYMin -> boundingRect().width() / 2, rc.y() + (m_pYMin -> boundingRect().height() / 2)));
    m_pYMax -> setPos(QPointF(m_pYMax -> boundingRect().width() / 2, rc.height() + (m_pYMax -> boundingRect().height() / 2)));
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    createConnections();
}

CartesianGraph::CartesianGraph(const CartesianGraph &obj) : QGraphicsItem() {
    if (&obj != this) {
        if (m_pDataObj)
            delete m_pDataObj;
        m_pDataObj = new CartesianGraphDataObj(obj.DataObj());
        m_pGraphWidget = obj.graphWidget();
        delete m_x_label;
        delete m_y_label;
        m_x_label = new CartesianLabel(obj.XAxisLabel(), this);
        m_y_label = new CartesianLabel(obj.YAxisLabel(), this);
        m_x_label ->setPos(QPointF(200 + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, -200 - m_borderWidth));
    }
}

CartesianGraph::~CartesianGraph() {
    delete m_pDataObj;
    m_pDataObj = NULL;
    m_pGraphWidget = NULL;
    delete m_x_label; m_x_label = NULL;
    delete m_y_label; m_y_label = NULL;
}


// operator overloads
CartesianGraph &CartesianGraph::operator=(const CartesianGraph &obj) {
    // check to see if we're assigning this to itself
    if (&obj != this) {
        if (m_pDataObj)
            delete m_pDataObj;
        // m_pDataObj = new CartesianGraphDataObj(obj.DataObj());
        m_pGraphWidget = obj.graphWidget();
        delete m_x_label;
        delete m_y_label;
        m_x_label = new CartesianLabel(obj.XAxisLabel(), this);
        m_y_label = new CartesianLabel(obj.YAxisLabel(), this);
        m_x_label ->setPos(QPointF(200 + m_borderWidth, 0));
        m_y_label ->setPos(QPointF(0, -200 - m_borderWidth));
    }
    return *this;
}

void CartesianGraph::init() {
    m_pDataObj -> init();
}

void CartesianGraph::createConnections() {
    connect(this, SIGNAL(reorderObjNav(QGraphicsItem *)), m_pGraphWidget, SLOT(onReorderObjNav(QGraphicsItem *)));
    connect(this, SIGNAL(changeItemName(const QString &, const QString &)), m_pGraphWidget, SLOT(onChangeItemName(const QString &, const QString &)));
    connect(this, SIGNAL(repaint()), m_pGraphWidget, SLOT(onRepaint()));
}

void CartesianGraph::onChangeItemName(const QString &strOld, const QString &strNew) {
    emit changeItemName(strOld, strNew);
}

void CartesianGraph::onRepaint() {
    qDebug("CartesianGraph::onRepaint()");
    emit repaint();
}

void CartesianGraph::XExtent(const QString &str) {
    m_pDataObj -> xMax(str.toDouble());
    m_pDataObj -> xMin(-(str.toDouble()));
    m_pXMax ->setPlainText(QString::number(m_pDataObj -> xMax()));
    m_pXMin ->setPlainText(QString::number(m_pDataObj -> xMin()));
}

void CartesianGraph::YExtent(const QString &str) {
    m_pDataObj -> yMax(str.toDouble());
    m_pDataObj -> yMin(-(str.toDouble()));

    m_pYMin ->setPlainText(QString::number(m_pDataObj -> yMin()));
    m_pYMax ->setPlainText(QString::number(m_pDataObj -> yMax()));
}


CartesianGraph *CartesianGraph::copy() {
    CartesianGraph *pObj = NULL;

    return pObj;
}

void CartesianGraph::onReorderObjNav(QGraphicsItem *pObj) {
    qDebug("CartesianGraph::onReorderObjNav");
    emit reorderObjNav(pObj);
}

void CartesianGraph::onPropChange(const QString &str) {
    qDebug("CartesianGraph::onPropChange(): updating info");
    update();
}

QRectF CartesianGraph::boundingRect() const {
    return QRectF(-200, -200, 400, 400);
}

QPainterPath CartesianGraph::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void CartesianGraph::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter -> setPen(Qt::NoPen);
    painter -> setBrush(Qt::darkGray);
    painter -> setPen(QPen(Qt::black, 2));
    painter -> drawLine(QLine(0, 200, 0, -200));    // vertical axis
    painter -> drawLine(QLine(-200, 0, 200, 0));    // horizontal axis

    // Draw the tickmarks
    int tickDrawLength = 5;
    double tickStep = m_pDataObj -> tickStep();
    QRectF rc = boundingRect();

    // Figure out the number of ticks
    int numTicksX = (m_pDataObj -> xMax() / tickStep) * 2;    // *2 because of both sides +/- sides to axis
    int numTicksY = (m_pDataObj -> yMax() / tickStep) * 2;

    // The width of coordinate space between ticks - x-axis
    int pxPerTickX = rc.width() / numTicksX;

    // The width of coordinate space between ticks - y-axis
    int pxPerTickY = rc.width() / numTicksY;

    // Do vertical lines... Draw left to right
    int axisStartPoint = rc.x();
    for (int i = 1; i < numTicksX; i++) {
        if (axisStartPoint + pxPerTickX * i == 0)
            continue;
        painter -> drawLine(QLine(axisStartPoint + pxPerTickX * i, tickDrawLength, axisStartPoint + pxPerTickX * i, -tickDrawLength));
    }

    // Do Horizontal lines... Draw left to right
    axisStartPoint = rc.y();
    for (int j = 1; j < numTicksY; j++) {
        if (axisStartPoint + pxPerTickY * j == 0)
            continue;
        painter -> drawLine(QLine(tickDrawLength, axisStartPoint + pxPerTickY * j, -tickDrawLength, axisStartPoint + pxPerTickY * j));
    }

    // Draw the end ticks of axis' along with the extent text
    painter -> setPen(QPen(Qt::black, 4));
    painter -> drawLine(QLine(rc.x(), tickDrawLength + 5, rc.x(), -tickDrawLength - 5));
    painter -> drawLine(QLine(rc.width(), tickDrawLength + 5, rc.width(), -tickDrawLength - 5));
    painter -> drawLine(QLine(tickDrawLength + 5, rc.y(), -tickDrawLength - 5, rc.y()));
    painter -> drawLine(QLine(tickDrawLength + 5, rc.height(), -tickDrawLength - 5, rc.height()));
}

QVariant CartesianGraph::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case ItemPositionHasChanged:
            /*
             foreach (Edge *edge, edgeList)
                edge -> adjust();
            m_pgraphWidget -> itemMoved();
            */
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void CartesianGraph::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CartesianGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
