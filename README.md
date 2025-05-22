
# ⏰ ESP32 OLED NTP Clock

This project displays real-time Indian Standard Time (IST) on an SSD1306 OLED display using an ESP32 board. Time is fetched from an NTP server and shown in 12-hour format with date, weekday, and WiFi status.

---

## Features

- 🕒 Real-time 12-hour clock with AM/PM  
- 📅 Date in DD/MM/YY format  
- 📆 Day of the week (Mon, Tue, etc.)  
- 📶 WiFi connection indicator (ON/OFF)  
- 🌐 NTP synchronization from `in.pool.ntp.org`

---

## Hardware Used

- ESP32 Dev Board  
- SSD1306 OLED Display (I2C)  
  - SDA → GPIO 23  
  - SCL → GPIO 22

---

## Libraries Required

Install these libraries from the Arduino Library Manager:

- `U8g2`  
- `WiFi`  
- `NTPClient`  
- `WiFiUdp`  
- `TimeLib`

---

## ⚙️ Setup

1. Clone the repository:  
   ```bash
   git clone https://github.com/yourusername/ESP32-OLED-NTP-Clock.git
   ```

2. Open the `.ino` file in Arduino IDE

3. Enter your WiFi credentials:  
   ```cpp
   const char *ssid = "YOUR_WIFI_SSID";
   const char *password = "YOUR_WIFI_PASSWORD";
   ```

4. Upload the code to your ESP32

---

## Demo

You can download the demo image here:  
[ESP32 OLED Demo Image](https://drive.google.com/file/d/16pe0XmlFHVWIpMVkH1cILu1ehH07WTPX/view?usp=sharing)

---

## 📄 License

This project is licensed under the MIT License.
