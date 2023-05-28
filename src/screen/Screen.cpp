#include "custom/screen/Screen.hpp"
#include "pros/rtos.hpp"
#include <mutex>

const Screen *Screen::instance = nullptr;
pros::Mutex Screen::mutex;

const Screen *Screen::getScreen() {
  std::lock_guard<pros::Mutex> lock(mutex);
  if (instance == nullptr) {
    instance = new Screen();
  }
  return instance;
}
