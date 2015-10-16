#include "cartesiangraphdataobj.h"

CartesianGraphDataObj::CartesianGraphDataObj() {
    m_tickStep = 10.0;
}

CartesianGraphDataObj::CartesianGraphDataObj(const CartesianGraphDataObj &Obj) {
    m_origin = Obj.m_origin;
    m_tickStep = Obj.m_tickStep;
    m_x_min = Obj.m_x_min;
    m_x_max = Obj.m_x_max;
    m_y_min = Obj.m_y_min;
    m_y_max = Obj.m_y_max;

    /*
    for (int idx1 = 0; idx1 < Obj.m_Vectors.size(); idx1++) {
        PhysVector *pObj = new PhysVector(Obj.m_Vectors.at(idx1));
        m_Vectors.push_back(pObj);
    }

    QList<PhysVector *> m_Vectors;
    QList<PhysParticle *> m_Particles;
    */
}

CartesianGraphDataObj::CartesianGraphDataObj(
        QPointF origin,
        double tickStep,
        double x_min,
        double x_max,
        double y_min,
        double y_max) {
    m_origin = origin;
    m_tickStep = tickStep;
    m_x_min = x_min;
    m_x_max = x_max;
    m_y_min = y_min;
    m_y_max = y_max;
}

CartesianGraphDataObj::~CartesianGraphDataObj() {
    m_Vectors.clear();
    m_Particles.clear();
}

CartesianGraphDataObj &CartesianGraphDataObj::operator=(const CartesianGraphDataObj &obj) {
    if (&obj != this) {
    }
    return *this;
}


QDataStream &operator<<(QDataStream &out, const CartesianGraphDataObj &obj) {
    return out;
}

QDataStream &operator>>(QDataStream &in, CartesianGraphDataObj &obj) {\
    return in;
}
