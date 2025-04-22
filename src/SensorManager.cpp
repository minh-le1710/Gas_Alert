#include "SensorManager.h"
#include <Arduino.h>

SensorManager::SensorManager(uint8_t pinDHT, uint8_t typeDHT, uint8_t pinMQ2)
 : _dht(pinDHT, typeDHT), _mq2Pin(pinMQ2) {}

void SensorManager::begin() {
  _dht.begin();
}

SensorData SensorManager::read() {
  SensorData d;
  d.temp = _dht.readTemperature();
  d.hum  = _dht.readHumidity();
  d.gas  = analogRead(_mq2Pin);
  return d;
}
