#ifndef PHYSPARTICLEDATAOBJ_H
#define PHYSPARTICLEDATAOBJ_H


class PhysParticleDataObj {
public:
    PhysParticleDataObj();
    PhysParticleDataObj(const PhysParticleDataObj &);
    ~PhysParticleDataObj();

    PhysParticleDataObj &operator=(const PhysParticleDataObj &);

    double mass() const { return m_mass; }
    void mass(const double val) { m_mass = val; }
private:
    double m_mass;

};

#endif // PHYSPARTICLEDATAOBJ_H
