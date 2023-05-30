#include "custom/screen/Screen.hpp"
#include "custom/screen/EventLog.hpp"
#include "custom/screen/MotorMonitor.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_tabview.h"
#include "pros/rtos.hpp"
#include <mutex>
#include <utility>

Screen *Screen::instance = nullptr;
pros::Mutex Screen::mutex;

Screen::Screen()
    : tabs(lv_tabview_create(lv_scr_act(), nullptr)),
      log(new EventLog(lv_tabview_add_tab(tabs, "Event Log"))),
      mMonitor(new MotorMonitor(lv_tabview_add_tab(tabs, "Monitor"))) {}

Screen::~Screen() {
  // it shouldn't be this easy.
  lv_obj_del(tabs);
}

Screen *Screen::getScreen() {
  std::lock_guard<pros::Mutex> lock(mutex);
  if (instance == nullptr) {
    instance = new Screen();
  }
  return instance;
}

EventLog *Screen::getLog() { return log; }

MotorMonitor *Screen::getMonitor() { return mMonitor; }
