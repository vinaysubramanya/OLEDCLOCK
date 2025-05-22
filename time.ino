#include <U8g2lib.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

// WiFi credentials
const char *ssid = "";
const char *password = "";

// NTP settings for IST (UTC+5:30)
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org", 19800, 60000); // IST offset: 19800 seconds (5.5*3600)

// Initialize U8g2 for SSD1306 OLED (SDA=23, SCL=22)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 23);

// Weekday names
const char* dayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  Serial.begin(115200);
  
  // Initialize OLED
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 20, "Connecting to WiFi...");
  u8g2.sendBuffer();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, "WiFi connected!");
  u8g2.drawStr(0, 35, "Syncing IST time...");
  u8g2.sendBuffer();
  
  // Initialize NTP client with Indian server
  timeClient.begin();
  
  // Wait for time sync
  while (!timeClient.update()) {
    timeClient.forceUpdate();
    delay(500);
  }
  
  // Set system time (already includes IST offset from NTP client)
  setTime(timeClient.getEpochTime());
  
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, "IST Time Synced!");
  u8g2.sendBuffer();
  delay(2000);
}

void loop() {
  // Update time from NTP periodically
  timeClient.update();
  setTime(timeClient.getEpochTime());
  
  // Get current time in 12-hour format with AM/PM
  char timeStr[20];
  int hour12 = hour() % 12;
  if (hour12 == 0) hour12 = 12; // Convert 0 to 12 for 12-hour format
  sprintf(timeStr, "%02d:%02d:%02d %s", hour12, minute(), second(), (hour() < 12) ? "AM" : "PM");
  
  // Get date in DD/MM/YY format
  char dateStr[20];
  sprintf(dateStr, "%02d/%02d/%02d", day(), month(), year() % 100); // Last 2 digits of year
  
  // Get weekday
  char weekdayStr[10];
  strcpy(weekdayStr, dayNames[weekday()-1]); // weekday() returns 1-7
  
  // Display on OLED
  u8g2.clearBuffer();
  
  // Draw header with weekday
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawUTF8(0, 12, weekdayStr);
  
  // Draw time (large font)
  u8g2.setFont(u8g2_font_logisoso24_tn);
  u8g2.drawStr(5, 42, timeStr);
  
  // Draw date (medium font)
  u8g2.setFont(u8g2_font_ncenB12_tr);
  u8g2.drawStr(25, 60, dateStr);
  
  // WiFi status indicator
  u8g2.setFont(u8g2_font_5x7_tr);
  if (WiFi.status() == WL_CONNECTED) {
    u8g2.drawUTF8(110, 7, "ON");
  } else {
    u8g2.drawUTF8(110, 7, "OFF");
  }
  
  u8g2.sendBuffer();
  
  delay(1000); // Update every second
}