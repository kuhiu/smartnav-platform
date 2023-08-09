#include <Tracker.hpp>

Tracker *Tracker::__instance = nullptr;

Tracker *Tracker::getInstance() {
  if (__instance == nullptr) {
    __instance = new Tracker;
  }
  return __instance;
}