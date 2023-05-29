#pragma once

#include "display/lv_core/lv_obj.h"
#include <string>
#include <utility>

class EventLog {
private:
  lv_obj_t *log;

public:
  EventLog(lv_obj_t *);
  ~EventLog();

  void addEntry(const std::string &, const std::string &);
};
