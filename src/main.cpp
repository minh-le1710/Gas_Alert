#include <Arduino.h>

// ————— CẤU HÌNH CHUNG —————
#define DHTPIN          D4
#define DHTTYPE         DHT11
#define MQ2_PIN         A0

#define LED_R_PIN       D6
#define LED_G_PIN       D7
#define LED_B_PIN       D5

#define TEMP_THRESHOLD  40.0f
#define HUM_THRESHOLD   70.0f
#define GAS_THRESHOLD   300

#define BLYNK_TEMPLATE_ID   "TMPL641Z1U1wp"
#define BLYNK_TEMPLATE_NAME "relay"
#define BLYNK_AUTH_TOKEN    "14E3ut4MY2XRxcV1mPHg3igw6CllDWpz"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "SensorManager.h"
#include "DisplayManager.h"
#include "AlertManager.h"

#define BLYNK_TEMPLATE_ID   "TMPL641Z1U1wp"
#define BLYNK_TEMPLATE_NAME "relay"
#define BLYNK_AUTH_TOKEN    "14E3ut4MY2XRxcV1mPHg3igw6CllDWpz"

const char* ssid="vivo S17e", *pw="minh1710";

SensorManager   sm(DHTPIN,DHT11,  MQ2_PIN);
DisplayManager  dm;
AlertManager    am(LED_R_PIN,LED_G_PIN,LED_B_PIN,
                  TEMP_THRESHOLD,HUM_THRESHOLD,GAS_THRESHOLD);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid,pw);
  while(WiFi.status()!=WL_CONNECTED) delay(200);
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pw);
  configTime(7*3600,0,"pool.ntp.org");

  sm.begin();
  dm.begin();
  am.begin();
}

void loop(){
  Blynk.run();

  // đọc + hiển thị
  auto data   = sm.read();
  auto ts     = dm.getTime();
  bool  wifiOK= (WiFi.status()==WL_CONNECTED);
  dm.drawHeader(wifiOK,ts);
  dm.drawAlert(data.temp > TEMP_THRESHOLD);
  dm.drawBody(data);
  dm.send();

  // LED + Blynk
  bool norm = am.check(data);
  am.updateLED(norm);
  Blynk.virtualWrite(V1, ts.str);
  Blynk.virtualWrite(V2, data.temp);
  Blynk.virtualWrite(V3, data.hum);
  Blynk.virtualWrite(V4, data.gas);
  Blynk.virtualWrite(V5, norm?1:0);

  delay(1000);
}
