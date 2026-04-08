#include "simulator/sim/model/ackermann/AckermannController.h"

AckermannController::AckermannController(float speed, float deltaMaxRad)
    : v(speed), deltaMax(deltaMaxRad) {
}

AckermannControl AckermannController::compute(const AckermannState& s,
    const ITrajectory& traj,
    const GVF& gvf) const
{
    Vec2 p{ s.x, s.y };
    float theta_d = gvf.desiredHeading(p, traj);

    float e = std::atan2(std::sin(theta_d - s.theta), std::cos(theta_d - s.theta));
    float delta = std::clamp(e, -deltaMax, deltaMax);

    return AckermannControl{ v, delta };
}