#pragma once
#include <U8g2lib.h>
#include "SensorManager.h"
#include <time.h>
struct TimeStamp { char str[6]; };

class DisplayManager {
public:
  DisplayManager();
  void begin();
  TimeStamp getTime();
  void drawHeader(bool wifiOK, const TimeStamp&);
  void drawBody(const SensorData&);
  void drawAlert(bool highAlert);
  void send();
private:
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C _u8g2;
};
