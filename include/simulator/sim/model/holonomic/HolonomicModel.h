#pragma once
#include "HolonomicState.h"

class HolonomicModel {
public:
    HolonomicState step(const HolonomicState& s, const HolonomicControl& u, float dt) const;
};