#pragma once

struct Vec2 {
	float x = 0;
	float y = 0;
};

class ITrajectory {
public:
	virtual ~ITrajectory() = default;

	virtual float phi(const Vec2& p) const = 0;
	virtual Vec2 gradPhi(const Vec2& p) const = 0;
};