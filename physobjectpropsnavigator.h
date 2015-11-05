#ifndef PHYSOBJECTPROPSNAVIGATOR_H
#define PHYSOBJECTPROPSNAVIGATOR_H

#include <QTableWidget>
#include <QGraphicsItem>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLineEdit>

#include "cartesiangraph.h"
#include "physparticle.h"
#include "physvector.h"

class PhysObjectPropsNavigator : public QTableWidget {
    Q_OBJECT
public:
    PhysObjectPropsNavigator(QWidget * = NULL);

    void buildCartesianGraphTable(CartesianGraph *);
    void buildVectorTable(PhysVector *);
    void buildParticleTable(PhysParticle *);

    void updateVectorTable(PhysVector *);
    void updateParticleTable(PhysParticle *);
    void updateCartesianGraphTable(CartesianGraph *);
signals:

public slots:
    void onChangeObj(QGraphicsItem *);
    void onUpdateObj(QGraphicsItem *);
private:

    // CartesianGraph
    QDoubleSpinBox *m_pXaxisTickInc;
    QDoubleSpinBox *m_pXaxisExtent;
    QDoubleSpinBox *m_pYaxisExtent;
    QLineEdit *m_pCartesianGraphName;

    // PhysVectors
    QDoubleSpinBox *m_pVectorMag;
    QDoubleSpinBox *m_pVectorThetaAngle;
    QComboBox *m_pVectorThetaAxisOrient;
    QLineEdit *m_pVectorAssocParticle;
    QLineEdit *m_pVectorName;

    // PhysParticles
    QLineEdit *m_pParticleName;

};

#endif // PHYSOBJECTPROPSNAVIGATOR_H
