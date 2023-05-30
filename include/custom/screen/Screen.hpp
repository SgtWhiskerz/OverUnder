#pragma once

#include "custom/screen/EventLog.hpp"
#include "custom/screen/MotorMonitor.hpp"
#include "display/lv_core/lv_obj.h"
#include "pros/rtos.hpp"
#include <vector>

/**
 * Brain gui
 * Single instance, and very much not generic
 */
class Screen {
private:
  static Screen *instance;
  static pros::Mutex mutex;
  lv_obj_t *tabs;
  EventLog *log;
  MotorMonitor *mMonitor;

protected:
  Screen();
  ~Screen();

public:
  Screen(Screen &other) = delete;
  void operator=(const Screen &other) = delete;

  static Screen *getScreen();
  EventLog *getLog();
  MotorMonitor *getMonitor();
};
