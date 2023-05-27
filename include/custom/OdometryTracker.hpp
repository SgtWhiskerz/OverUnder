#pragma once

#include "okapi/impl/device/rotarysensor/rotationSensor.hpp"
#include <array>

class OdometryTracker {
public:
  struct SensorOffset {
    double lDist = 0.0;
    double rDist = 0.0;
    double cDist = 0.0;
  };

  struct Position {
    double x = 0.0;
    double y = 0.0;
    double heading = 0.0;
  };

  struct PolarCoord {
    double mag = 0.0;
    double theta = 0.0;
  };

  struct CartesianCoord {
    double x = 0.0;
    double y = 0.0;
  };

  OdometryTracker(std::array<okapi::RotationSensor, 3>, SensorOffset, double);

  void tick();

private:
  okapi::RotationSensor left;
  okapi::RotationSensor right;
  okapi::RotationSensor center;

  SensorOffset offsets;

  double wheelDiam;

  double initHead;

  double lastL;
  double lastR;
  double lastC;

  double lastHead; // TODO: start looking somewhere

  Position pos;

  void addOffset(const CartesianCoord &, const double &);

protected:
};
