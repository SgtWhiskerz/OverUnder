#pragma once

#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_chart.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * Itterate a list of motors/motor groups and track motor tempurature over time
 * using a chart
 */
class MotorMonitor {
  /*
   * Keep track of:
   *   - Motors
   *   - Readable names
   *   - Data series of tempuratures
   */
private:
  std::unordered_map<okapi::AbstractMotor *,
                     std::pair<std::string, lv_chart_series_t *>>
      list; // Overly complicated? possibly. but fuck it
  lv_obj_t *chart;

public:
  MotorMonitor(
      const std::vector<std::pair<std::string, okapi::AbstractMotor *>> &,
      lv_obj_t *);
  ~MotorMonitor();

  void addMotor(const std::pair<std::string, okapi::AbstractMotor *> &);

  void tick();
};
