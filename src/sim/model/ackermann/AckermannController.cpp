#include "simulator/sim/model/ackermann/AckermannController.h"
#include <cmath>
#include <algorithm>

AckermannController::AckermannController(float speed, float deltaMaxRad,
    float wheelbase, float headingGain)
    : v(speed), deltaMax(deltaMaxRad), L(wheelbase), kHdg(headingGain) {
}

AckermannControl AckermannController::compute(const AckermannState& s,
    const ITrajectory& traj, const GVF& gvf) const
{
    Vec2 p{ s.x, s.y };

    float theta_d;
    if (traj.hasParametric()) {
        theta_d = gvf.desiredHeading(p, s.w, traj);  // usa w
    }
    else {
        // fallback implícito para CircleTrajectory etc.
        Vec2  g = traj.gradPhi(p);
        float ph = traj.phi(p);
        float gnorm = std::hypot(g.x, g.y);
        if (gnorm < 1e-8f) gnorm = 1e-8f;
        float nx = g.x / gnorm, ny = g.y / gnorm;
        float e_n = std::tanh(gvf.getK() * ph);
        float vx = -ny - e_n * nx;
        float vy = nx - e_n * ny;
        theta_d = std::atan2(vy, vx);
    }

    float e = std::atan2(std::sin(theta_d - s.theta),
        std::cos(theta_d - s.theta));
    float delta = std::clamp(std::atan(L * kHdg * e), -deltaMax, deltaMax);
    return AckermannControl{ v, delta };
}