#pragma once
#include "simulator/sim/trajectory/ITrajectory.h" 

struct HolonomicState { Vec2 p{ 0.0f, 0.0f }; };
struct HolonomicControl { Vec2 v{ 0.0f, 0.0f }; };