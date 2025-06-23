# Personal Decor Screen V1.0.0
## Phần cứng
### Thông tin chung
- Sử dụng phần cứng CYD ESP32-2432S028 2USB
- Có thể thay thế bằng ESP32 kết nối màn hình TFT 2.8 inch qua SPI
### Linh kiện
- [CYD ESP32-2432S028 2USB](https://shopee.vn/B%E1%BA%A3ng-M%E1%BA%A1ch-Ph%C3%A1t-Tri%E1%BB%83n-esp32-arduino-lvgl-wifi-bluetooth-2.8-240-*-320-M%C3%A0n-H%C3%ACnh-C%E1%BA%A3m-%E1%BB%A8ng-Th%C3%B4ng-Minh-2.8inch-lcd-tft-i.578443443.24202758643)
- [Pin lithium 3,7V](https://shopee.vn/Pin-d%E1%BA%B9t-3.7V-Dung-L%C6%B0%E1%BB%A3ng-T%E1%BB%AB-40-15000mAh-c%C3%B3-m%E1%BA%A1ch-b%E1%BA%A3o-v%E1%BB%87-pin-cho-tai-nghe-%C4%91%E1%BB%93ng-h%E1%BB%93-ch%C3%ADnh-h%C3%A3ng-i.1191630361.24236610465)
- [Mạch tăng áp tích hợp sạc xả cổng Type-C 5v 2A](https://shopee.vn/M%E1%BA%A1ch-t%C4%83ng-%C3%A1p-t%C3%ADch-h%E1%BB%A3p-s%E1%BA%A1c-x%E1%BA%A3-c%E1%BB%95ng-Type-C-5v-2A-d%C3%B9ng-cho-pin-18650-lion-lithium-3.7v-(M%E1%BA%A1ch-Ch%E1%BA%BF-S%E1%BA%A1c)-i.134796651.15572794517)
- [Vỏ trưng bày DIY](https://shopee.vn/V%E1%BB%8F-case-cho-c%C3%A1c-phi%C3%AAn-b%E1%BA%A3n-DIY-s%E1%BB%AD-d%E1%BB%A5ng-ESP32-2432S028-in-3D-ch%E1%BA%A5t-l%C6%B0%E1%BB%A3ng-t%E1%BB%91t(%C4%90%E1%BB%8CC-K%E1%BB%B8-M%C3%94-T%E1%BA%A2)-i.1155397997.29714618276)
### Cấu hình GPIO
| Display Screen            | GPIO   | Touch Screen        | GPIO   |
|---------------------------|--------|----------------------|--------|
| MISO (TFT_MISO)           | GPIO 12| IRQ (T_IRQ)          | GPIO 36|
| MOSI (TFT_MOSI)           | GPIO 13| MOSI (T_MOSI)        | GPIO 32|
| SCKL (TFT_SCLK)           | GPIO 14| MISO (T_MISO)        | GPIO 39|
| CS (TFT_CS)               | GPIO 15| CLK (T_CLK)          | GPIO 25|
| DC (TFT_DC)               | GPIO 2 | CS (T_CS)            | GPIO 33|
| RST (TFT_RST)             | -1     |                      |        |
| Backlight Pin             | GPIO 21|                      |        |
## Phần mềm
### Tính năng
- MainScreen: Màn hình chính xem lịch, thời gian thực, biểu cảm robot
- SettingScreen: Xem địa chỉ IP, MAC và thông tin Wifi kết nối
- SystemScreen: Theo dõi thông tin hệ thống gồm có Ram, CPU, Nhiệt độ và thông tin phần cứng thiết bị
- WeatherScreen: Cập nhật thời tiết theo thời gian thực dựa trên API từ https://openweathermap.org/current
- WifiSelectScreen: Scan wifi và kết nối tới wifi lựa chọn
- Sử dụng multiWiFi có thể đưa nhiều wifi mặc định vào phần mềm
### Web flash
- Nạp firmware nhanh tại [đây](https://duylonghn.github.io/ESP32/port.html)
