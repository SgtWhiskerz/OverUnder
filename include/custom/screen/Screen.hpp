#pragma once

#include "display/lv_core/lv_obj.h"
#include "pros/rtos.hpp"
#include <vector>

/**
 * Brain gui
 * Single instance, and very much not generic
 */
class Screen {
private:
  static const Screen *instance;
  static pros::Mutex mutex;

protected:
  Screen() = default;

public:
  Screen(Screen &other) = delete;
  void operator=(const Screen &other) = delete;

  static const Screen *getScreen();
};
