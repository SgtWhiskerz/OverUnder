#include "custom/screen/MotorMonitor.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_chart.h"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include <string>
#include <utility>
#include <vector>

constexpr short POINT_COUNT = 5;

MotorMonitor::MotorMonitor(
    const std::vector<std::pair<std::string, okapi::AbstractMotor *>> &motors,
    lv_obj_t *parent = lv_scr_act())
    : chart(lv_chart_create(parent, nullptr)) {

  lv_chart_set_point_count(chart, POINT_COUNT);

  list.reserve(motors.size());
  for (const auto &entry : motors) { // randomize colors?
    list[entry.second] =
        std::make_pair(entry.first, lv_chart_add_series(chart, LV_COLOR_CYAN));
  }
}

MotorMonitor::MotorMonitor(lv_obj_t *parent)
    : chart(lv_chart_create(parent, nullptr)) {}

MotorMonitor::MotorMonitor() : MotorMonitor(lv_scr_act()) {}

MotorMonitor::~MotorMonitor() { lv_obj_del(chart); }

MotorMonitor &MotorMonitor::addMotor(const std::string &name,
                                     okapi::AbstractMotor *motor) {
  list[motor] = std::make_pair(name, lv_chart_add_series(chart, LV_COLOR_CYAN));
  return *this;
}

void MotorMonitor::tick() {
  for (auto &entry : list) {
    lv_chart_set_next(chart, entry.second.second,
                      entry.first->getTemperature());
  }
  lv_chart_refresh(chart);
}
