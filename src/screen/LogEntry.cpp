#include "custom/screen/LogEntry.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_objx/lv_btn.h"
#include "display/lv_objx/lv_label.h"
#include "display/lv_objx/lv_mbox.h"
#include <string>

constexpr short LABEL_PADDING = 30;

LogEntry::LogEntry(const std::string &msg, lv_obj_t *parent,
                   const std::string & /*desc*/ = "")
    : btn(lv_btn_create(parent, nullptr)), msgBox(nullptr) {
  lv_obj_t *label = lv_label_create(
      btn, nullptr); // No idea if i should cache this in the object
                     // Memory leak can be avoided with the LVGL lib
  lv_label_set_text(label, msg.c_str());
  lv_obj_set_size(btn, lv_obj_get_width(parent),
                  lv_obj_get_height(label) + LABEL_PADDING);
  lv_obj_t *lstChld = lv_obj_get_child_back(parent, nullptr);
  lv_obj_align(btn, lstChld, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

LogEntry::~LogEntry() {
  // Avoid memory leak
  lv_obj_del(btn);
  lv_obj_del(msgBox);
}

lv_obj_t *LogEntry::getMsg() { return btn; }
