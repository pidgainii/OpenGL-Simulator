#include "simulator/sim/model/unicycle/UnicycleModel.h"

UnicycleState UnicycleModel::step(const UnicycleState& s, const UnicycleControl& u, float dt) const {
    UnicycleState ns = s;

    ns.x += u.v * std::cos(s.theta) * dt;
    ns.y += u.v * std::sin(s.theta) * dt;
    ns.theta += u.omega * dt;
    
    return ns;
}