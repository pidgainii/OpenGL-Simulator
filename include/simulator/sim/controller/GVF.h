#pragma once
#include "simulator/sim/trajectory/ITrajectory.h"
#include <cmath>

class GVF {
	float k;
public:
	GVF(float gain = 0.2f) : k(gain) {};

    Vec2 field(const Vec2& p, const ITrajectory& path) const {
        Vec2 g = path.gradPhi(p);
        Vec2 t{ -g.y, g.x };

        float ph = path.phi(p);
        Vec2 n{ -k * ph * g.x, -k * ph * g.y };

        Vec2 V{ t.x + n.x, t.y + n.y };

        float nrm = norm(V);
        if (nrm > 1e-6f) {
            V.x /= nrm;
            V.y /= nrm;
        }
        return V;
    }

	float desiredHeading(const Vec2& p, const ITrajectory& path) const {
		
		// Tangente
		Vec2 g = path.gradPhi(p);
		Vec2 t{ -g.y, g.x };     

		// Normal
		float ph = path.phi(p);
		Vec2 n{ -k * ph * g.x, -k * ph * g.y }; 

		Vec2 V{ t.x + n.x, t.y + n.y };
		return std::atan2(V.y, V.x);

	}
};