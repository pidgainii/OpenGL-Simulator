#include "simulator/sim/model/unicycle/UnicycleController.h"

UnicycleController::UnicycleController(float speed, float kTheta)
    : v(speed), k_theta(kTheta) {
}

UnicycleControl UnicycleController::compute(const UnicycleState& s,
    const ITrajectory& traj,
    const GVF& gvf) const
{
    Vec2 p{ s.x, s.y };

    float theta_d = gvf.desiredHeading(p, traj);

    float error_theta = std::atan2(std::sin(theta_d - s.theta), std::cos(theta_d - s.theta));

    float omega = k_theta * error_theta;

    return UnicycleControl{ v, omega };
}