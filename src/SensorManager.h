#pragma once
#include <DHT.h>
struct SensorData { float temp, hum; int gas; };
class SensorManager {
public:
  SensorManager(uint8_t pinDHT, uint8_t typeDHT, uint8_t pinMQ2);
  void begin();
  SensorData read();
private:
  DHT   _dht;
  uint8_t _mq2Pin;
};
