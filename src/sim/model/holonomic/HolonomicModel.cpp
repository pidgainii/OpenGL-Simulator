#include "simulator/sim/model/holonomic/HolonomicModel.h"

HolonomicState HolonomicModel::step(const HolonomicState& s, const HolonomicControl& u, float dt) const {
    HolonomicState ns = s;
    ns.p.x += u.v.x * dt;
    ns.p.y += u.v.y * dt;
    return ns;
}