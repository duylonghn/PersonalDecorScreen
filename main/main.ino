#include <lvgl.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <time.h>
#include "ui.h"
#include "ui_helpers.h"
#include "all_frames.h"
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// Main
extern lv_obj_t *ui_btnWifi;
extern lv_obj_t *ui_backCorrect;
extern lv_obj_t *ui_backIncorrect;
extern lv_obj_t *ui_labelDate;
// Wifi
extern lv_obj_t *ui_scanWifi;
extern lv_obj_t *ui_containerWifiList;
extern lv_obj_t *ui_loadWifi;
extern lv_obj_t *ui_loadConnectWifi;
// Setting
extern lv_obj_t *ui_ssid;
extern lv_obj_t *ui_ipDevice;
extern lv_obj_t *ui_ipPublic;
extern lv_obj_t *ui_btnShutdown;
extern lv_obj_t *ui_system;
// System
extern lv_obj_t *ui_tempValue;
extern lv_obj_t *ui_ramValue;
extern lv_obj_t *ui_cpuValue;
extern lv_obj_t *ui_chipModel;
extern lv_obj_t *ui_cpuFreq;
extern lv_obj_t *ui_flashSize;
extern lv_obj_t *ui_SystemScreen;
// Weather
extern lv_obj_t *ui_WeatherScreen;
extern lv_obj_t *ui_feelsLike;
extern lv_obj_t *ui_tempMax;
extern lv_obj_t *ui_tempMin;
extern lv_obj_t *ui_humidity;
extern lv_obj_t *ui_wind;
extern lv_obj_t *ui_pressure;
extern lv_obj_t *ui_visibility;
extern lv_obj_t *ui_infoData;
extern lv_obj_t *ui_city;
extern lv_obj_t *ui_labelTime1;
extern lv_obj_t *ui_labelDate1;
extern lv_obj_t *ui_weatherMain;
extern lv_obj_t *ui_weatherDes;
extern lv_obj_t *ui_icon01d72p;
extern lv_obj_t *ui_icon01n72p;
extern lv_obj_t *ui_icon02d72p;
extern lv_obj_t *ui_icon02n72p;
extern lv_obj_t *ui_icon03d03n72p;
extern lv_obj_t *ui_icon04d04n72p;
extern lv_obj_t *ui_icon09d09n72p;
extern lv_obj_t *ui_icon10d72p;
extern lv_obj_t *ui_icon10n72p;
extern lv_obj_t *ui_icon11d11n72p;
extern lv_obj_t *ui_icon13d13n72p;
extern lv_obj_t *ui_icon50d50n72p;

lv_obj_t *MainScreen, *SettingScreen, *WifiSelectScreen, *WifiPasswordScreen;
lv_obj_t *ssidName, *passValue, *keyboard;
lv_obj_t *calendar, *timeLabel;

//=========================== Touch & TFT display ===========================
#define T_CS 33
#define T_IRQ 36
#define T_CLK 25
#define T_MOSI 32
#define T_MISO 39

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(T_CS, T_IRQ);
WiFiUDP ntpUDP;
WiFiMulti wifiMulti;
TFT_eSPI tft = TFT_eSPI();

void my_touch_read_cb(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    int x = map(p.x, 200, 3700, 0, 320);
    int y = map(p.y, 240, 3800, 0, 240);
    x = constrain(x, 0, 319);
    y = constrain(y, 0, 239);

    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}
//=========================== Robot face ===========================
static lv_img_dsc_t robotImgDsc;
#define SLEEP_START_FRAME 90
#define SLEEP_END_FRAME 132
#define TOTAL_FRAMES 477
#define SLEEP_TIMEOUT_MIN 3000
#define SLEEP_TIMEOUT_MAX 5000
#define FRAME_DELAY 42

static int currentFrame = 0;
static bool isSleep = false;
static unsigned long sleepStartTime = 0;
static unsigned long sleepDuration = 0;
static unsigned long lastFrameTime = 0;

unsigned long randomSleepTimeout() {
  return random(SLEEP_TIMEOUT_MIN, SLEEP_TIMEOUT_MAX);
}

void updateRobotFace() {
  unsigned long currentTime = millis();

  if (isSleep && (currentTime - sleepStartTime >= sleepDuration)) {
    isSleep = false;
    sleepDuration = randomSleepTimeout();
  }

  if (!isSleep && (currentFrame == SLEEP_START_FRAME)) {
    sleepStartTime = currentTime;
    isSleep = true;
  }

  if (currentTime - lastFrameTime >= FRAME_DELAY) {
    lastFrameTime = currentTime;

    if (isSleep) {
      currentFrame++;
      if (currentFrame > SLEEP_END_FRAME) {
        currentFrame = SLEEP_START_FRAME;
      }
    } else {
      currentFrame = (currentFrame + 1) % TOTAL_FRAMES;
    }

    robotImgDsc.header.always_zero = 0;
    robotImgDsc.header.w = FRAME_WIDTH;
    robotImgDsc.header.h = FRAME_HEIGHT;
    robotImgDsc.header.cf = LV_IMG_CF_ALPHA_1BIT;
    robotImgDsc.data_size = (FRAME_WIDTH * FRAME_HEIGHT) / 8;
    robotImgDsc.data = frames[currentFrame];

    lv_img_set_src(ui_imageRobot, &robotImgDsc);
  }
}

//=========================== Wifi Setting ===========================
String selectedSSID = "";
String ipPublic = "0.0.0.0";

TaskHandle_t wifiAutoConnectHandle = NULL;
volatile bool stopAutoConnect = false;

void ui_update_wifi_info(const char *ssid, const char *ip) {
  lv_label_set_text(ui_ssid, ssid);
  lv_label_set_text(ui_ipDevice, ip);
  lv_label_set_text(ui_ipPublic, ipPublic.c_str());

  String mac = WiFi.macAddress();
  lv_label_set_text(ui_mac, mac.c_str());

  if (strcmp(ssid, "Không kết nối") == 0 || strcmp(ssid, "Unknown") == 0) {
    lv_obj_clear_flag(ui_disableWifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_enableWifi, LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_clear_flag(ui_enableWifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_disableWifi, LV_OBJ_FLAG_HIDDEN);
  }
}

void wifiAutoConnectTaskFunc(void *param) {
  wifiMulti.addAP("Duy Long", "Khong@biet");
  wifiMulti.addAP("DuyLong", "12341234");
  wifiMulti.addAP("Wifi T1", "12341234");

  while (!stopAutoConnect) {
    if (WiFi.status() != WL_CONNECTED) {
      int retry = 0;
      while (wifiMulti.run() != WL_CONNECTED && retry++ < 10 && !stopAutoConnect) {
        delay(500);
      }

      lv_async_call([](void *data) {
        if (WiFi.status() == WL_CONNECTED) {
          get_location();
          ui_update_wifi_info(WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
          update_Weather_Data();
        } else {
          ui_update_wifi_info("Unknown", "0.0.0.0");
        }
      },
                    NULL);
    }
    for (int i = 0; i < 60 && !stopAutoConnect; ++i) delay(1000);
  }
  vTaskDelete(NULL);
}

void connectToWiFiAsync(String ssid, String password) {
  lv_obj_clear_flag(ui_loadConnectWifi, LV_OBJ_FLAG_HIDDEN);

  struct WifiParam {
    String ssid;
    String password;
  };

  WifiParam *p = new WifiParam{ ssid, password };

  xTaskCreate([](void *param) {
    WifiParam *p = static_cast<WifiParam *>(param);
    WiFi.begin(p->ssid.c_str(), p->password.c_str());
    bool connected = false;

    for (int i = 0; i < 20; i++) {
      if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        break;
      }
      delay(300);
    }

    lv_async_call([](void *data) {
      WifiParam *p = static_cast<WifiParam *>(data);
      lv_obj_add_flag(ui_loadConnectWifi, LV_OBJ_FLAG_HIDDEN);

      if (WiFi.status() == WL_CONNECTED) {
        get_location();
        update_Weather_Data();
        ui_update_wifi_info(WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
        lv_obj_clear_flag(ui_backCorrect, LV_OBJ_FLAG_HIDDEN);
        lv_timer_create([](lv_timer_t *t) {
          lv_obj_add_flag(ui_backCorrect, LV_OBJ_FLAG_HIDDEN);
          lv_timer_del(t);
          _ui_screen_change(&ui_WifiSelectScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 300, 0, ui_WifiSelectScreen_screen_init);
        },
                        1500, NULL);
      } else {
        lv_obj_clear_flag(ui_backIncorrect, LV_OBJ_FLAG_HIDDEN);
        lv_timer_create([](lv_timer_t *t) {
          lv_obj_add_flag(ui_backIncorrect, LV_OBJ_FLAG_HIDDEN);
          lv_timer_del(t);
        },
                        1500, NULL);
      }
      delete p;
    },
                  p);

    vTaskDelete(NULL);
  },
              "wifiConnectTask", 8192, p, 1, NULL);
}

//=========================== Button ===========================
void event_shutdown_cb(lv_event_t *e) {
  ESP.restart();
}

void event_system_cb(lv_event_t *e) {
  _ui_screen_change(&ui_SystemScreen, LV_SCR_LOAD_ANIM_FADE_IN, 300, 0, onSystemScreenLoad);
}

void event_ssid_button_cb(lv_event_t *e) {
  const char *ssid = (const char *)lv_event_get_user_data(e);
  selectedSSID = String(ssid);
  lv_label_set_text(ssidName, ssid);
}

void event_keyboard_cb(lv_event_t *e) {
  uint16_t btn_id = lv_btnmatrix_get_selected_btn(keyboard);
  const char *btn_txt = lv_keyboard_get_btn_text(keyboard, btn_id);
  if (btn_txt && strcmp(btn_txt, LV_SYMBOL_OK) == 0) {
    String password = lv_textarea_get_text(passValue);
    connectToWiFiAsync(selectedSSID, password);
  }
}

void event_scan_wifi_cb(lv_event_t *e) {
  stopAutoConnect = true;
  if (wifiAutoConnectHandle != NULL) {
    vTaskDelete(wifiAutoConnectHandle);
    wifiAutoConnectHandle = NULL;
  }

  lv_obj_clear_flag(ui_loadWifi, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clean(ui_containerWifiList);

  xTaskCreatePinnedToCore([](void *param) {
    int n = WiFi.scanNetworks();
    std::vector<String> *ssidList = new std::vector<String>();
    for (int i = 0; i < n; i++) ssidList->push_back(WiFi.SSID(i));

    lv_async_call([](void *data) {
      auto *ssids = static_cast<std::vector<String> *>(data);
      lv_obj_clean(ui_containerWifiList);

      for (const String &ssidStr : *ssids) {
        const char *ssidCStr = strdup(ssidStr.c_str());
        lv_obj_t *btn = lv_btn_create(ui_containerWifiList);
        lv_obj_set_size(btn, lv_pct(100), 40);
        lv_obj_add_event_cb(btn, event_ssid_button_cb, LV_EVENT_CLICKED, (void *)ssidCStr);
        lv_obj_set_style_bg_color(btn, lv_color_white(), LV_PART_MAIN);
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, ssidCStr);
        lv_obj_center(label);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_16, LV_PART_MAIN);
        lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
      }
      lv_obj_add_flag(ui_loadWifi, LV_OBJ_FLAG_HIDDEN);
      delete ssids;
    },
                  ssidList);
    vTaskDelete(NULL);
  },
                          "wifiScanTask", 8192, NULL, 1, NULL, 1);
}

//=========================== Time ===========================
#define UTC_OFFSET 7 * 3600

void setupTime() {
  configTime(UTC_OFFSET, 0, "pool.ntp.org", "time.nist.gov");
  struct tm timeinfo;
  int retry = 0;
  while (!getLocalTime(&timeinfo) && retry++ < 30) {
    delay(500);
  }
}

void setupTimeTask(void *param) {
  setupTime();
  vTaskDelete(NULL);
}

void updateClockDisplay() {
  static unsigned long lastUpdate = 0;
  static bool calendarUpdated = false;
  if (millis() - lastUpdate < 1000) return;
  lastUpdate = millis();

  if (WiFi.status() == WL_CONNECTED) {
    time_t now = time(NULL);
    if (now < 1609459200) return;

    struct tm *ti = localtime(&now);
    char timeStr[16];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", ti);
    lv_label_set_text(timeLabel, timeStr);

    char dateStr[32];
    strftime(dateStr, sizeof(dateStr), "%a, %d/%m/%Y", ti);
    lv_label_set_text(ui_labelDate, dateStr);

    if (!calendarUpdated) {
      lv_calendar_date_t today;
      today.year = ti->tm_year + 1900;
      today.month = ti->tm_mon + 1;
      today.day = ti->tm_mday;
      lv_calendar_set_today_date(calendar, today.year, today.month, today.day);
      lv_calendar_set_showed_date(calendar, today.year, today.month);
      calendarUpdated = true;
    }
  }
}

//=========================== GUI ===========================
void uiTask(void *param) {
  while (true) {
    lv_timer_handler();
    updateClockDisplay();
    updateRobotFace();
    if (lv_scr_act() == ui_SystemScreen) {
      updateSystemInfo();
    }
    delay(5);
  }
}

void updateArc(lv_obj_t *arc, int value) {
  value = constrain(value, 0, 100);
  lv_arc_set_value(arc, value);

  // Chọn màu theo mức
  lv_color_t color;
  if (value <= 50)
    color = lv_color_hex(0x00FF00);  // Xanh lá
  else if (value <= 80)
    color = lv_color_hex(0xFFFF00);  // Vàng
  else
    color = lv_color_hex(0xFF0000);  // Đỏ

  lv_obj_set_style_arc_color(arc, color, LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(arc, color, LV_PART_KNOB);
}

//=========================== System Moniter ===========================
volatile uint32_t idleCounter = 0;

void idleTask(void *parameter) {
  while (1) {
    idleCounter++;
    vTaskDelay(pdMS_TO_TICKS(5));  // Mỗi lần idle tăng là 5ms
  }
}

void updateSystemInfo() {
  // TEMP
  int temp = (int)temperatureRead();
  temp = constrain(temp, 0, 100);
  lv_label_set_text_fmt(ui_tempValue, "%d\u00B0C", temp);
  updateArc(ui_temp, temp);

  // RAM
  uint32_t freeHeap = ESP.getFreeHeap();
  uint32_t totalHeap = ESP.getHeapSize();
  uint8_t ramUsedPercent = 100 - ((freeHeap * 100) / totalHeap);
  lv_label_set_text_fmt(ui_ramValue, "%d%%", ramUsedPercent);
  updateArc(ui_ram, ramUsedPercent);

  // CPU
  static uint32_t lastIdleCount = 0;
  static uint32_t lastMillis = 0;

  if (millis() - lastMillis >= 1000) {
    uint32_t currentIdle = idleCounter;
    uint32_t deltaIdle = currentIdle - lastIdleCount;
    lastIdleCount = currentIdle;

    // Giả sử delayMicroseconds(100), tức mỗi lần idle là 100us
    float idleTimeMs = deltaIdle * 5;  // tính ra ms
    uint8_t cpuUsage = 100 - constrain((idleTimeMs / 1000.0f) * 100, 0, 100);

    lv_label_set_text_fmt(ui_cpuValue, "%d%%", cpuUsage);
    updateArc(ui_cpu, cpuUsage);

    lastMillis = millis();
  }

  // Thông tin hệ thống
  lv_label_set_text(ui_chipModel, ESP.getChipModel());
  lv_label_set_text_fmt(ui_cpuFreq, "%d MHz", ESP.getCpuFreqMHz());
  lv_label_set_text_fmt(ui_flashSize, "%d KB", ESP.getFlashChipSize() / 1024);
}

void onSystemScreenLoad() {
  updateSystemInfo();
}

//=========================== Weather ===========================
String openWeatherMapApiKey = "6835331adfd4a27998460cea9c6cbf79";
double lat = 0;
double lon = 0;
String city = "Unknown";

const int daylightOffset_sec = 0;
#define INTERVAL_UPDATING_WEATHER_DATA 300
char ca_Info_Status[50];
String jsonBuffer;

char timeStr[16] = "";
char dateStr[32] = "";

String str_Weather_Main, str_Weather_Icon, str_Weather_Description;
String str_Temperature, str_Feels_Like, str_Temp_Max, str_Temp_Min;
String str_Humidity, str_Wind_Speed, str_Pressure, str_Visibility;

void get_location() {
  if (WiFi.status() == WL_CONNECTED) {
    String jsonBuffer = httpGETRequest("http://ip-api.com/json");
    JSONVar data = JSON.parse(jsonBuffer);

    if (JSON.typeof(data) != "undefined") {
      lat = double(data["lat"]);
      lon = double(data["lon"]);

      city = JSON.stringify(data["city"]);
      city.replace("\"", "");  // Loại bỏ dấu "

      ipPublic = JSON.stringify(data["query"]);
      ipPublic.replace("\"", "");  // Lấy IP public từ trường "query"
    } else {
      lat = 0;
      lon = 0;
      city = "Unknown";
      ipPublic = "0.0.0.0";
    }
  } else {
    lat = 0;
    lon = 0;
    city = "Unknown";
    ipPublic = "0.0.0.0";
  }
}

void get_Data_from_OpenWeatherMap() {
  lv_label_set_text(ui_infoData, "Update weather data...");
  lv_timer_handler();

  Serial.println();
  Serial.println("-------------");
  Serial.println("Update weather data (Getting Weather Data from OpenWeatherMap).");
  Serial.println("Please wait...");
  delay(500);

  // Check WiFi connection status.
  if (WiFi.status() == WL_CONNECTED) {
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?lat=" + String(lat, 6) + "&lon=" + String(lon, 6) + "&appid=" + openWeatherMapApiKey + "&units=metric";

    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println();
    Serial.println("Weather Data in JSON form :");
    Serial.println(jsonBuffer);
    JSONVar myObject = JSON.parse(jsonBuffer);

    // JSON.typeof(jsonVar) can be used to get the type of the var.
    if (JSON.typeof(myObject) == "undefined") {
      strcpy(ca_Info_Status, "(Failed : Parsing input failed !)");

      Serial.println("Parsing input failed !");

      lv_label_set_text(ui_infoData, "");
      lv_timer_handler();
      return;
    }

    Serial.println();
    Serial.println("Weather Data taken");

    str_Weather_Main = JSON.stringify(myObject["weather"][0]["main"]);
    str_Weather_Main.replace("\"", "");  //--> Removes the Double quotes (") character in the string.
    str_Weather_Icon = JSON.stringify(myObject["weather"][0]["icon"]);
    str_Weather_Icon.replace("\"", "");
    str_Weather_Description = JSON.stringify(myObject["weather"][0]["description"]);
    str_Weather_Description.replace("\"", "");

    str_Temperature = JSON.stringify(myObject["main"]["temp"]);
    str_Feels_Like = JSON.stringify(myObject["main"]["feels_like"]);
    str_Temp_Max = JSON.stringify(myObject["main"]["temp_max"]);
    str_Temp_Min = JSON.stringify(myObject["main"]["temp_min"]);

    str_Humidity = JSON.stringify(myObject["main"]["humidity"]);
    str_Wind_Speed = JSON.stringify(myObject["wind"]["speed"]);
    str_Pressure = JSON.stringify(myObject["main"]["pressure"]);
    str_Visibility = JSON.stringify(myObject["visibility"]);

    Serial.println();
    Serial.print("Weather Main : ");
    Serial.println(str_Weather_Main);
    Serial.print("Weather Icon : ");
    Serial.println(str_Weather_Icon);
    Serial.print("Weather Description : ");
    Serial.println(str_Weather_Description);

    Serial.print("Temperature : ");
    Serial.print(str_Temperature);
    Serial.println(" °C");
    Serial.print("Feels Like : ");
    Serial.print(str_Feels_Like);
    Serial.println(" °C");
    Serial.print("Temp Max : ");
    Serial.print(str_Temp_Max);
    Serial.println(" °C");
    Serial.print("Temp Min : ");
    Serial.print(str_Temp_Min);
    Serial.println(" °C");

    Serial.print("Humidity : ");
    Serial.print(str_Humidity);
    Serial.println(" %");
    Serial.print("Wind Speed : ");
    Serial.print(str_Wind_Speed);
    Serial.println(" m/s");
    Serial.print("Pressure : ");
    Serial.print(str_Pressure);
    Serial.println(" hPa");
    Serial.print("Visibility : ");
    Serial.print(str_Visibility);
    Serial.println(" m");

    Serial.println("-------------");
    Serial.println();

    strcpy(ca_Info_Status, "(Succeed)");

    lv_label_set_text(ui_infoData, "");
    lv_timer_handler();
    delay(1000);
  } else {
    strcpy(ca_Info_Status, "(Failed : WiFi Disconnected !)");

    Serial.println("WiFi Disconnected");
    Serial.println("-------------");
    Serial.println();
  }
}

String httpGETRequest(const char *serverName) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}

void get_DateTime() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate < 1000) return;
  lastUpdate = millis();

  if (WiFi.status() == WL_CONNECTED) {
    time_t now = time(NULL);
    if (now < 1609459200) return;

    struct tm *ti = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", ti);
    lv_label_set_text(ui_labelTime1, timeStr);

    strftime(dateStr, sizeof(dateStr), "%a, %d/%m/%Y", ti);
    lv_label_set_text(ui_labelDate1, dateStr);
  }
}

void hideAllWeatherIcons() {
  lv_obj_add_flag(ui_icon01d72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon01n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon02d72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon02n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon03d03n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon04d04n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon09d09n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon10d72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon10n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon11d11n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon13d13n72p, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_icon50d50n72p, LV_OBJ_FLAG_HIDDEN);
}

void update_Weather_Data() {
  get_DateTime();
  get_Data_from_OpenWeatherMap();

  lv_label_set_text(ui_city, city.c_str());
  lv_label_set_text(ui_weatherMain, str_Weather_Main.c_str());

  hideAllWeatherIcons();
  if (str_Weather_Icon == "01d") {
    lv_obj_clear_flag(ui_icon01d72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "01n") {
    lv_obj_clear_flag(ui_icon01n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "02d") {
    lv_obj_clear_flag(ui_icon02d72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "02n") {
    lv_obj_clear_flag(ui_icon02n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "03d" || str_Weather_Icon == "03n") {
    lv_obj_clear_flag(ui_icon03d03n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "04d" || str_Weather_Icon == "04n") {
    lv_obj_clear_flag(ui_icon04d04n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "09d" || str_Weather_Icon == "09n") {
    lv_obj_clear_flag(ui_icon09d09n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "10d") {
    lv_obj_clear_flag(ui_icon10d72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "10n") {
    lv_obj_clear_flag(ui_icon10n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "11d" || str_Weather_Icon == "11n") {
    lv_obj_clear_flag(ui_icon11d11n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "13d" || str_Weather_Icon == "13n") {
    lv_obj_clear_flag(ui_icon13d13n72p, LV_OBJ_FLAG_HIDDEN);
  } else if (str_Weather_Icon == "50d" || str_Weather_Icon == "50n") {
    lv_obj_clear_flag(ui_icon50d50n72p, LV_OBJ_FLAG_HIDDEN);
  }

  lv_label_set_text(ui_weatherDes, str_Weather_Description.c_str());

  float f_Temp = str_Temperature.toFloat();
  char ca_Temp[10];
  dtostrf(f_Temp, 4, 1, ca_Temp);
  strcat(ca_Temp, "°C");
  lv_label_set_text(ui_temperature, ca_Temp);

  float f_Feels_Like = str_Feels_Like.toFloat();
  char ca_Feels_Like[12];  // tăng thêm để chứa chuỗi và đơn vị
  dtostrf(f_Feels_Like, 4, 1, ca_Feels_Like);
  strcat(ca_Feels_Like, " °C");
  lv_label_set_text(ui_feelsLike, ca_Feels_Like);

  float f_Temp_Max = str_Temp_Max.toFloat();
  char ca_Temp_Max[12];
  dtostrf(f_Temp_Max, 4, 1, ca_Temp_Max);
  strcat(ca_Temp_Max, " °C");
  lv_label_set_text(ui_tempMax, ca_Temp_Max);

  float f_Temp_Min = str_Temp_Min.toFloat();
  char ca_Temp_Min[12];
  dtostrf(f_Temp_Min, 4, 1, ca_Temp_Min);
  strcat(ca_Temp_Min, " °C");
  lv_label_set_text(ui_tempMin, ca_Temp_Min);

  str_Humidity += " %";
  lv_label_set_text(ui_humidity, str_Humidity.c_str());

  float f_Wind_Speed = str_Wind_Speed.toFloat() * 3.6;
  char ca_Wind_Speed[14];
  dtostrf(f_Wind_Speed, 4, 1, ca_Wind_Speed);
  strcat(ca_Wind_Speed, " km/h");
  lv_label_set_text(ui_wind, ca_Wind_Speed);

  str_Pressure += " hPa";
  lv_label_set_text(ui_pressure, str_Pressure.c_str());

  float f_Visibility = str_Visibility.toFloat() / 1000;
  char ca_Visibility[10];
  dtostrf(f_Visibility, 4, 1, ca_Visibility);
  strcat(ca_Visibility, " km");
  lv_label_set_text(ui_visibility, ca_Visibility);

  char ca_Info[70];
  lv_snprintf(ca_Info, sizeof(ca_Info), "Last data update: %s %s", timeStr, ca_Info_Status);
  lv_label_set_text(ui_infoData, ca_Info);
}

void weatherUpdateTask(void *param) {
  const TickType_t delayTicks = 1000 / portTICK_PERIOD_MS;
  int counter = 0;
  while (true) {
    get_DateTime();

    if (counter >= 60) {
      counter = 0;
      if (lv_scr_act() == ui_WeatherScreen) {
        update_Weather_Data();
      }
    }
    counter++;
    vTaskDelay(delayTicks);
  }
}

//=========================== Setup ===========================
void setup() {
  Serial.begin(115200);
  lv_init();
  touchscreenSPI.begin(T_CLK, T_MISO, T_MOSI, T_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(1);
  tft.begin();
  tft.setRotation(1);

  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf1[320 * 10];
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 320 * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touch_read_cb;
  lv_indev_drv_register(&indev_drv);

  ui_init();

  MainScreen = ui_MainScreen;
  SettingScreen = ui_SettingScreen;
  WifiSelectScreen = ui_WifiSelectScreen;
  WifiPasswordScreen = ui_WifiPasswordScreen;
  ssidName = ui_ssidName;
  passValue = ui_passValue;
  keyboard = ui_keyboard;
  calendar = ui_calendarMonth;
  timeLabel = ui_labelTime;

  lv_scr_load(MainScreen);

  ui_update_wifi_info("Unknown", "0.0.0.0");

  lv_obj_add_event_cb(ui_scanWifi, event_scan_wifi_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(ui_btnShutdown, event_shutdown_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(keyboard, event_keyboard_cb, LV_EVENT_VALUE_CHANGED, NULL);

  xTaskCreatePinnedToCore(uiTask, "uiTask", 8192, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(wifiAutoConnectTaskFunc, "wifiAutoConnect", 8192, NULL, 1, &wifiAutoConnectHandle, 0);
  xTaskCreatePinnedToCore(idleTask, "IdleTask", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(weatherUpdateTask, "weatherUpdateTask", 8192, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore([](void *param) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Sau khi kết nối thì setup time
    setupTime();
    vTaskDelete(NULL);
  },
                          "ntpTask", 4096, NULL, 1, NULL, 0);
}

void loop() {}