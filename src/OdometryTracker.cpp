#include "custom/OdometryTracker.hpp"
#include <array>
#include <cmath>
#include <tuple>

constexpr double FULL_ROT = 360.0;

OdometryTracker::OdometryTracker(std::array<okapi::RotationSensor, 3> sensors,
                                 SensorOffset _offsets, double _wheelDiam)
    : left(sensors.at(0)), right(sensors.at(1)), center(sensors.at(2)),
      offsets(_offsets), wheelDiam(_wheelDiam), lastL(left.get()),
      lastR(right.get()), lastC(center.get()) {}

constexpr double convDist(const double &sensVal, const double &wheelDiam) {
  return sensVal / FULL_ROT * wheelDiam;
}

constexpr double calcHeading(const double &gWheelDiff,
                             const double &betweenWheels) {
  return gWheelDiff / betweenWheels;
}

OdometryTracker::CartesianCoord
calcLOffset(const double &headingDiff,
            const OdometryTracker::SensorOffset &offsets,
            const std::tuple<double, double> &sensorVals) {
  OdometryTracker::CartesianCoord localOff;
  if (headingDiff == 0.0) { // Other option ldist = rdist
    localOff = {.x = std::get<0>(sensorVals),
                .y = std::get<1>(sensorVals)}; // Tuples are weird
  } else {
    const double con = 2 * std::sin(headingDiff / 2);
    // NOTE: double check that this scalar multiplication is the same between
    // matrix and vector
    localOff = {
        .x = con * (std::get<0>(sensorVals) / headingDiff) + offsets.cDist,
        .y = con * (std::get<0>(sensorVals) / headingDiff) + offsets.rDist};
  }
  return localOff;
}

OdometryTracker::CartesianCoord
calcGOffset(const OdometryTracker::CartesianCoord &lOffset,
            const double &angleAdjuster) {
  OdometryTracker::PolarCoord polar = {
      .mag = std::hypot(lOffset.x, lOffset.y),
      // Possible error here for Quadrants II - IV
      .theta = std::atan2(lOffset.y, lOffset.x)};
  polar.theta -= angleAdjuster;

  OdometryTracker::CartesianCoord globalOff = {
      .x = polar.mag * std::cos(polar.theta),
      .y = polar.mag * std::sin(polar.theta)};
  return globalOff;
}

void OdometryTracker::addOffset(const OdometryTracker::CartesianCoord &off,
                                const double &heading) {
  pos.heading += heading;
  pos.x += off.x;
  pos.y += off.y;
}

void OdometryTracker::tick() {
  double lVal = left.get();
  double rVal = right.get();
  double cVal = center.get();

  // double lDist = convDist(lVal - lastL, wheelDiam);
  double rDist = convDist(rVal - lastR, wheelDiam);
  double cDist = convDist(cVal - lastC, wheelDiam);

  lastL = lVal;
  lastR = rVal;
  lastC = cVal;

  double glDist = convDist(lVal, wheelDiam);
  double grDist = convDist(rVal, wheelDiam);

  double heading =
      initHead + calcHeading(glDist - grDist, offsets.lDist + offsets.rDist);
  double headingDiff = heading - lastHead;

  CartesianCoord localOff =
      calcLOffset(headingDiff, offsets, std::make_tuple(cDist, rDist));

  double avgHeading = initHead + (heading / 2);

  CartesianCoord globalOff = calcGOffset(localOff, avgHeading);

  addOffset(globalOff, avgHeading * -1);
}
