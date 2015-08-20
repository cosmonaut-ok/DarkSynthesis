#include "physparticle.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "cartesianlabel.h"

PhysParticle::PhysParticle(GraphWidget *graphWidget) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    m_pLabel = new CartesianLabel(QString("Particle"), this);
}
PhysParticle::~PhysParticle() {
    if (m_pLabel) {
        delete m_pLabel;
        m_pLabel = NULL;
    }
}


QRectF PhysParticle::boundingRect() const {
    const qreal adjust = 2.0;
    return QRectF(-10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath PhysParticle::shape() const {
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void PhysParticle::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *) {
    pPainter -> setPen(Qt::NoPen);
    pPainter -> setBrush(Qt::darkGray);
    pPainter -> drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (pOption -> state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    }
    else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    pPainter -> setBrush(gradient);
    pPainter -> setPen(QPen(Qt::black, 0));
    pPainter -> drawEllipse(-10, -10, 20, 20);
}

QVariant PhysParticle::itemChange(GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case ItemPositionHasChanged:
            break;
        default:
            break;
    };
    return QGraphicsItem::itemChange(change, value);
}

void PhysParticle::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void PhysParticle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}