#include "custom/screen/EventLog.hpp"
#include "custom/screen/LogEntry.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_page.h"
#include <utility>

constexpr short SCROLL_SPEED = 250;

EventLog::EventLog(lv_obj_t *parent, std::pair<short, short> pos,
                   std::pair<short, short> size)
    : log(lv_page_create(parent, nullptr)) {
  lv_obj_set_pos(log, pos.first, pos.second);
  lv_obj_set_width(log, size.first);
  lv_obj_set_height(log, size.second);
}

EventLog::~EventLog() { lv_obj_del(log); }

void EventLog::addEntry(const std::string &message,
                        const std::string &description) {
  auto *newEvent = new LogEntry(message, lv_obj_get_parent(log), description);
  lv_page_focus(log, newEvent->getMsg(), SCROLL_SPEED);
}
