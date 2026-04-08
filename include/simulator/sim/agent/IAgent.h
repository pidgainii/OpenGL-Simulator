#pragma once
#include "simulator/sim/common/Pos.h"

class IAgent {
public:
    virtual ~IAgent() = default;

    // advances internal state by dt
    virtual void step(float dt) = 0;

    // current pos
    virtual Pos pos() const = 0;
};