#pragma once
#include "include/simulator/sim/trajectory/ITrajectory.h"
#include "include/simulator/sim/trajectory/CircleTrajectory.h"
#include "include/simulator/sim/trajectory/LemniscateTrajectory.h"
#include "include/simulator/sim/trajectory/LineTrajectory.h"
#include "include/simulator/sim/trajectory/TrajectoryType.h"
#include <memory>


inline std::unique_ptr<ITrajectory> MakeTrajectory(TrajectoryType type) {
    switch (type) {
    case TrajectoryType::Circle:      return std::make_unique<CircleTrajectory>(20.0f);
    case TrajectoryType::Lemniscate:  return std::make_unique<LemniscateTrajectory>(35.0f);
    case TrajectoryType::Line:        return std::make_unique<LineTrajectory>(0.0f);
    default:                          return std::make_unique<CircleTrajectory>(20.0f);
    }
}