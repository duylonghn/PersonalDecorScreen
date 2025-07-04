// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.2
// LVGL version: 8.3.6
// Project name: ESP32-2432S028R

#include "ui.h"

lv_obj_t * ui_SettingScreen;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Label5;
lv_obj_t * ui_ssid;
lv_obj_t * ui_ipDevice;
lv_obj_t * ui_mac;
lv_obj_t * ui_backHome1;
lv_obj_t * ui_Label1;
lv_obj_t * ui_btnShutdown;
lv_obj_t * ui_system;
lv_obj_t * ui_Image1;
lv_obj_t * ui_weather;
lv_obj_t * ui_Label14;
lv_obj_t * ui_ipPublic;

// event funtions
void ui_event_backHome1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_MainScreen, LV_SCR_LOAD_ANIM_OVER_LEFT, 50, 0, &ui_MainScreen_screen_init);
    }
}

void ui_event_system(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_SystemScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 50, 0, &ui_SystemScreen_screen_init);
    }
}

void ui_event_Image1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_SystemScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 50, 0, &ui_SystemScreen_screen_init);
    }
}

void ui_event_weather(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_WeatherScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 50, 0, &ui_WeatherScreen_screen_init);
    }
}

// build funtions

void ui_SettingScreen_screen_init(void)
{
    ui_SettingScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SettingScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SettingScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -119);
    lv_obj_set_y(ui_Label2, -95);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "SSID: ");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -130);
    lv_obj_set_y(ui_Label3, -63);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "IP: ");
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label5 = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, -119);
    lv_obj_set_y(ui_Label5, 0);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "MAC:");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ssid = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_ssid, 200);
    lv_obj_set_height(ui_ssid, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ssid, 29);
    lv_obj_set_y(ui_ssid, -95);
    lv_obj_set_align(ui_ssid, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ssid, "Unknown");
    lv_obj_set_style_text_color(ui_ssid, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ssid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ssid, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ssid, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ipDevice = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_ipDevice, 150);
    lv_obj_set_height(ui_ipDevice, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ipDevice, 41);
    lv_obj_set_y(ui_ipDevice, -63);
    lv_obj_set_align(ui_ipDevice, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ipDevice, "0.0.0.0");
    lv_obj_set_style_text_color(ui_ipDevice, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ipDevice, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ipDevice, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ipDevice, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mac = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_mac, 230);
    lv_obj_set_height(ui_mac, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_mac, 35);
    lv_obj_set_y(ui_mac, 0);
    lv_obj_set_align(ui_mac, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mac, "AA:BB:CC:DD:EE:FF");
    lv_obj_set_style_text_color(ui_mac, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_mac, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_mac, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_mac, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_backHome1 = lv_btn_create(ui_SettingScreen);
    lv_obj_set_width(ui_backHome1, 69);
    lv_obj_set_height(ui_backHome1, 21);
    lv_obj_set_x(ui_backHome1, 114);
    lv_obj_set_y(ui_backHome1, 98);
    lv_obj_set_align(ui_backHome1, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_backHome1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_backHome1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_backHome1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_backHome1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_backHome1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_backHome1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_backHome1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Home");
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnShutdown = lv_imgbtn_create(ui_SettingScreen);
    lv_imgbtn_set_src(ui_btnShutdown, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_shutdown48px_png, NULL);
    lv_obj_set_width(ui_btnShutdown, 48);
    lv_obj_set_height(ui_btnShutdown, 48);
    lv_obj_set_x(ui_btnShutdown, -121);
    lv_obj_set_y(ui_btnShutdown, 45);
    lv_obj_set_align(ui_btnShutdown, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_btnShutdown, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_btnShutdown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnShutdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_btnShutdown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_btnShutdown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_system = lv_imgbtn_create(ui_SettingScreen);
    lv_imgbtn_set_src(ui_system, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_settings48px_png, NULL);
    lv_obj_set_width(ui_system, 48);
    lv_obj_set_height(ui_system, 48);
    lv_obj_set_x(ui_system, -39);
    lv_obj_set_y(ui_system, 45);
    lv_obj_set_align(ui_system, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_system, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_system, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_system, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_system, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_system, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_img_create(ui_system);
    lv_img_set_src(ui_Image1, &ui_img_system48px_png);
    lv_obj_set_width(ui_Image1, 32);
    lv_obj_set_height(ui_Image1, 32);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_weather = lv_imgbtn_create(ui_SettingScreen);
    lv_imgbtn_set_src(ui_weather, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_weather48px_png, NULL);
    lv_obj_set_width(ui_weather, 48);
    lv_obj_set_height(ui_weather, 48);
    lv_obj_set_x(ui_weather, 40);
    lv_obj_set_y(ui_weather, 45);
    lv_obj_set_align(ui_weather, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_weather, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_weather, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_weather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_weather, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_weather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label14 = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label14, -97);
    lv_obj_set_y(ui_Label14, -32);
    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label14, "IP Public:");
    lv_obj_set_style_text_color(ui_Label14, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label14, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ipPublic = lv_label_create(ui_SettingScreen);
    lv_obj_set_width(ui_ipPublic, 150);
    lv_obj_set_height(ui_ipPublic, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ipPublic, 41);
    lv_obj_set_y(ui_ipPublic, -32);
    lv_obj_set_align(ui_ipPublic, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ipPublic, "0.0.0.0");
    lv_obj_set_style_text_color(ui_ipPublic, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ipPublic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ipPublic, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ipPublic, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_backHome1, ui_event_backHome1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Image1, ui_event_Image1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_system, ui_event_system, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_weather, ui_event_weather, LV_EVENT_ALL, NULL);

}

void ui_SettingScreen_screen_destroy(void)
{
    if(ui_SettingScreen) lv_obj_del(ui_SettingScreen);

    // NULL screen variables
    ui_SettingScreen = NULL;
    ui_Label2 = NULL;
    ui_Label3 = NULL;
    ui_Label5 = NULL;
    ui_ssid = NULL;
    ui_ipDevice = NULL;
    ui_mac = NULL;
    ui_backHome1 = NULL;
    ui_Label1 = NULL;
    ui_btnShutdown = NULL;
    ui_system = NULL;
    ui_Image1 = NULL;
    ui_weather = NULL;
    ui_Label14 = NULL;
    ui_ipPublic = NULL;

}
