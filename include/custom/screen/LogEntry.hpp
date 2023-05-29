#pragma once

#include "display/lv_core/lv_obj.h"
#include <string>

/**
 * A button with text explaing an event
 * if the button is pressed, use a popup to share details
 */
class LogEntry {
private:
  lv_obj_t *btn;
  lv_obj_t *msgBox;

public:
  LogEntry(const std::string &, lv_obj_t *, const std::string &);
  ~LogEntry();

  /**
   * @returns lv_btn event display
   */
  lv_obj_t* getMsg();
};
