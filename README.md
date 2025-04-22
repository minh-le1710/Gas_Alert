# Gas_Alert

An ESP8266‑based IoT device (Arduino/PlatformIO) that measures temperature, humidity & gas levels, displays them on an OLED screen, and pushes data to Blynk in real time.

## Key Features
- Reads **DHT11** for temperature & humidity  
- Reads **MQ‑2** for gas detection  
- Displays **Time**, **Temp**, **Humidity**, **Gas** on a 128×64 I2C OLED  
- RGB LED indicator: **Green** under normal conditions, **Red** on alert  
- Live dashboard on Blynk (Value widgets on V1–V4, LED widget on V5)

## Hardware
- **ESP8266** (NodeMCU / ESP-12E)  
- **DHT11** temperature & humidity sensor  
- **MQ‑2** gas sensor  
- **0.96″ OLED 128×64** (I2C)  
- **Common‑cathode RGB LED**

## Quick-start
### 1. Prerequisites  
- **Hardware**: ESP8266 (NodeMCU), DHT11, MQ‑2, 0.96″ I2C OLED, RGB LED  
- **Software**:  
  - [VS Code](https://code.visualstudio.com/) with **PlatformIO IDE** extension  
  - A free account on **Blynk** (to create your dashboard & Auth Token)  

### 2. Clone the Repository  
```bash
git clone https://github.com/minh-le1710/Gas_Alert.git
cd Gas_Alert
```
### 3. Wire 
DHT11 → D4 (DATA), 3V3, GND

MQ‑2 → A0 (AO), VIN (5V), GND

OLED → D2 (SDA), D1 (SCL), 3V3, GND

RGB LED → D6 (R), D7 (G), D5 (B), GND

### 4. Configure
Open platformio.ini (or include/blynk_config.h) and set:
```ini
; platformio.ini
[env:nodemcuv2]
build_flags =
  -DBLYNK_TEMPLATE_ID=\"TMPL641Z1U1wp\"
  -DBLYNK_TEMPLATE_NAME=\"relay\"
  -DBLYNK_AUTH_TOKEN=\"<Your-Blynk-Auth-Token>\"
  -DSSID=\"<Your-WiFi-SSID>\"
  -DPASSWORD=\"<Your-WiFi-Password>\"
```
### 5. Build & Upload
- In VS Code: click PlatformIO → Build → then Upload.

- Or via CLI:

```bash
pio run --target upload
```

## Demo
