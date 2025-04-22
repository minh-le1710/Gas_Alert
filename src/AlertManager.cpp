#include "AlertManager.h"
#include <Arduino.h>

AlertManager::AlertManager(uint8_t r,uint8_t g,uint8_t b,
                           float tTh,float hTh,int gTh)
 : _r(r),_g(g),_b(b), _t(tTh),_h(hTh),_gT(gTh) {}

void AlertManager::begin(){
  pinMode(_r,OUTPUT); pinMode(_g,OUTPUT); pinMode(_b,OUTPUT);
}

bool AlertManager::check(const SensorData& d){
  return d.temp<=_t && d.hum<=_h && d.gas<=_gT;
}

void AlertManager::updateLED(bool norm){
  analogWrite(_r, norm?0:1023);
  analogWrite(_g, norm?1023:0);
  analogWrite(_b, 0);
}
