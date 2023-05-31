#include "custom/screen/EventLog.hpp"
#include "custom/screen/LogEntry.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_page.h"
#include <utility>

constexpr short SCROLL_SPEED = 250;

EventLog::EventLog(lv_obj_t *parent) : log(lv_page_create(parent, nullptr)) {
	lv_obj_set_size(log, lv_obj_get_width(parent), lv_obj_get_height(parent));
	lv_obj_align(log, parent, LV_ALIGN_CENTER, 0, 0);
	lv_page_set_scroll_propagation(log, false);
}

EventLog::~EventLog() { lv_obj_del(log); }

void EventLog::addEntry(const std::string &message,
                        const std::string &description) {
  auto *newEvent = new LogEntry(message, log, description);
  lv_page_focus(log, newEvent->getMsg(), SCROLL_SPEED);
}
