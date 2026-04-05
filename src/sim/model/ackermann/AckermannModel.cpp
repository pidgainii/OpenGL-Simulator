#include "simulator/sim/model/ackermann/AckermannModel.h"

AckermannModel::AckermannModel(float wheelbase) : L(wheelbase) {}

AckermannState AckermannModel::step(const AckermannState& s, const AckermannControl& u, float dt) const {
    AckermannState ns = s;
    ns.x += u.v * std::cos(s.theta) * dt;
    ns.y += u.v * std::sin(s.theta) * dt;
    ns.theta += (u.v / L) * std::tan(u.delta) * dt;
    return ns;
}