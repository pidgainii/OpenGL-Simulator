#pragma once

#include "UnicycleState.h"
#include <cmath>

class UnicycleModel {
public:

    UnicycleModel() = default;

    UnicycleState step(const UnicycleState& s, const UnicycleControl& u, float dt) const;
};