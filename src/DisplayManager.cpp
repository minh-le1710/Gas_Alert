#include "DisplayManager.h"
#include <ESP8266WiFi.h>  // hoặc ESP8266WiFi

DisplayManager::DisplayManager()
 : _u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE) {}

void DisplayManager::begin() {
  _u8g2.begin();
}

TimeStamp DisplayManager::getTime(){
  time_t t = time(nullptr);
  struct tm* tm = localtime(&t);
  TimeStamp ts;
  snprintf(ts.str,6,"%02d:%02d",tm->tm_hour,tm->tm_min);
  return ts;
}

void DisplayManager::drawHeader(bool ok, const TimeStamp& ts){
  _u8g2.clearBuffer();
  if (ok) {
    // vẽ sóng nhỏ→lớn...
    int rssi = WiFi.RSSI(), bars = (rssi>-50?4:rssi>-60?3:rssi>-70?2:rssi>-80?1:0);
    for(int i=0;i<4;i++){
      int x=2+i*6, h=(i+1)*3, y=12-h;
      if(i<bars) _u8g2.drawBox(x,y,4,h);
      else       _u8g2.drawFrame(x,y,4,h);
    }
  } else {
    _u8g2.setFont(u8g2_font_helvR08_tf);
    _u8g2.drawStr(2,12,"No connection");
  }
  _u8g2.setFont(u8g2_font_helvB12_tf);
  _u8g2.drawStr(128-_u8g2.getStrWidth(ts.str),12,ts.str);
}

void DisplayManager::drawAlert(bool highAlert){
  if (highAlert) {
    const char* msg = "High Alert!!!";
    _u8g2.setFont(u8g2_font_helvR08_tf);
    int w = _u8g2.getStrWidth(msg);
    _u8g2.drawStr((128-w)/2,24,msg);
  }
}

void DisplayManager::drawBody(const SensorData& d){
  const int x[3]={8,56,104};
  _u8g2.setFont(u8g2_font_helvR08_tf);
  _u8g2.drawStr(x[0],44,"Temp");
  _u8g2.drawStr(x[1],44,"Hum");
  _u8g2.drawStr(x[2],44,"Gas");
  char buf[16];
  snprintf(buf,sizeof(buf),"%.1fC",d.temp); _u8g2.drawStr(x[0],56,buf);
  snprintf(buf,sizeof(buf),"%.1f%%",d.hum);  _u8g2.drawStr(x[1],56,buf);
  snprintf(buf,sizeof(buf),"%d",d.gas);      _u8g2.drawStr(x[2],56,buf);
}

void DisplayManager::send(){
  _u8g2.sendBuffer();
}
