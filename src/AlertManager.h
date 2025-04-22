#pragma once
#include "SensorManager.h"
class AlertManager {
public:
  AlertManager(uint8_t r,uint8_t g,uint8_t b,
               float tTh,float hTh,int gTh);
  void begin();
  bool check(const SensorData&);
  void updateLED(bool normal);
private:
  uint8_t _r,_g,_b;
  float _t,_h; int _gT;
};
