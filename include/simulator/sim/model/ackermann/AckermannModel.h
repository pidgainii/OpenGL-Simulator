#pragma once

#include "AckermannState.h"
#include <cmath>

class AckermannModel {
    float L;
public:
    explicit AckermannModel(float wheelbase);
    AckermannState step(const AckermannState& s, const AckermannControl& u, float dt) const;
};