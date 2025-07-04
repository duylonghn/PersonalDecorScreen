// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.2
// LVGL version: 8.3.6
// Project name: ESP32-2432S028R

#include "ui.h"

lv_obj_t * ui_SystemScreen;
lv_obj_t * ui_backHome2;
lv_obj_t * ui_Label6;
lv_obj_t * ui_temp;
lv_obj_t * ui_Label8;
lv_obj_t * ui_tempValue;
lv_obj_t * ui_cpu;
lv_obj_t * ui_Label9;
lv_obj_t * ui_cpuValue;
lv_obj_t * ui_ram;
lv_obj_t * ui_Label10;
lv_obj_t * ui_ramValue;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Label12;
lv_obj_t * ui_Label13;
lv_obj_t * ui_chipModel;
lv_obj_t * ui_cpuFreq;
lv_obj_t * ui_flashSize;

// event funtions
void ui_event_backHome2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_SettingScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 50, 0, &ui_SettingScreen_screen_init);
    }
}

// build funtions

void ui_SystemScreen_screen_init(void)
{
    ui_SystemScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SystemScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SystemScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SystemScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_backHome2 = lv_btn_create(ui_SystemScreen);
    lv_obj_set_width(ui_backHome2, 69);
    lv_obj_set_height(ui_backHome2, 21);
    lv_obj_set_x(ui_backHome2, 114);
    lv_obj_set_y(ui_backHome2, 98);
    lv_obj_set_align(ui_backHome2, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_backHome2, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_backHome2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_backHome2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_backHome2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_backHome2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_backHome2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label6 = lv_label_create(ui_backHome2);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Back");
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_temp = lv_arc_create(ui_SystemScreen);
    lv_obj_set_width(ui_temp, 80);
    lv_obj_set_height(ui_temp, 80);
    lv_obj_set_x(ui_temp, 100);
    lv_obj_set_y(ui_temp, -70);
    lv_obj_set_align(ui_temp, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_temp, LV_STATE_DISABLED);       /// States
    lv_arc_set_value(ui_temp, 50);
    lv_obj_set_style_pad_left(ui_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_temp, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_temp, 7, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_temp, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_temp, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_temp, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_temp, 3, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_temp);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label8, 0);
    lv_obj_set_y(ui_Label8, 28);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "TEMP");
    lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_tempValue = lv_label_create(ui_temp);
    lv_obj_set_width(ui_tempValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_tempValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_tempValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_tempValue, "50°C");
    lv_obj_set_style_text_color(ui_tempValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_tempValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cpu = lv_arc_create(ui_SystemScreen);
    lv_obj_set_width(ui_cpu, 80);
    lv_obj_set_height(ui_cpu, 80);
    lv_obj_set_x(ui_cpu, 1);
    lv_obj_set_y(ui_cpu, -70);
    lv_obj_set_align(ui_cpu, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_cpu, LV_STATE_DISABLED);       /// States
    lv_arc_set_value(ui_cpu, 50);
    lv_obj_set_style_pad_left(ui_cpu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cpu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cpu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cpu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_cpu, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_cpu, 7, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_cpu, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_cpu, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_cpu, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_cpu, 3, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_cpu);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, 0);
    lv_obj_set_y(ui_Label9, 28);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "CPU");
    lv_obj_set_style_text_color(ui_Label9, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cpuValue = lv_label_create(ui_cpu);
    lv_obj_set_width(ui_cpuValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cpuValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cpuValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cpuValue, "50%");
    lv_obj_set_style_text_color(ui_cpuValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cpuValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ram = lv_arc_create(ui_SystemScreen);
    lv_obj_set_width(ui_ram, 80);
    lv_obj_set_height(ui_ram, 80);
    lv_obj_set_x(ui_ram, -97);
    lv_obj_set_y(ui_ram, -70);
    lv_obj_set_align(ui_ram, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_ram, LV_STATE_DISABLED);       /// States
    lv_obj_clear_flag(ui_ram, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_arc_set_value(ui_ram, 50);
    lv_obj_set_style_pad_left(ui_ram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ram, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ram, 7, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_ram, 7, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_ram, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ram, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ram, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ram, 3, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Label10 = lv_label_create(ui_ram);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label10, 0);
    lv_obj_set_y(ui_Label10, 28);
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "RAM");
    lv_obj_set_style_text_color(ui_Label10, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ramValue = lv_label_create(ui_ram);
    lv_obj_set_width(ui_ramValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ramValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_ramValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ramValue, "50%");
    lv_obj_set_style_text_color(ui_ramValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ramValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label11 = lv_label_create(ui_SystemScreen);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label11, -99);
    lv_obj_set_y(ui_Label11, -8);
    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label11, "Chip Model: ");
    lv_obj_set_style_text_color(ui_Label11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label12 = lv_label_create(ui_SystemScreen);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label12, -105);
    lv_obj_set_y(ui_Label12, 43);
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "Flash Size:");
    lv_obj_set_style_text_color(ui_Label12, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label13 = lv_label_create(ui_SystemScreen);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label13, -107);
    lv_obj_set_y(ui_Label13, 18);
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label13, "CPU Freq:");
    lv_obj_set_style_text_color(ui_Label13, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chipModel = lv_label_create(ui_SystemScreen);
    lv_obj_set_width(ui_chipModel, 150);
    lv_obj_set_height(ui_chipModel, 15);
    lv_obj_set_x(ui_chipModel, 37);
    lv_obj_set_y(ui_chipModel, -8);
    lv_obj_set_align(ui_chipModel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_chipModel, "ESP32-D0WD-V3");
    lv_obj_set_style_text_color(ui_chipModel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_chipModel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cpuFreq = lv_label_create(ui_SystemScreen);
    lv_obj_set_width(ui_cpuFreq, 150);
    lv_obj_set_height(ui_cpuFreq, 15);
    lv_obj_set_x(ui_cpuFreq, 37);
    lv_obj_set_y(ui_cpuFreq, 18);
    lv_obj_set_align(ui_cpuFreq, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cpuFreq, "240 MHz");
    lv_obj_set_style_text_color(ui_cpuFreq, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cpuFreq, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_flashSize = lv_label_create(ui_SystemScreen);
    lv_obj_set_width(ui_flashSize, 150);
    lv_obj_set_height(ui_flashSize, 15);
    lv_obj_set_x(ui_flashSize, 37);
    lv_obj_set_y(ui_flashSize, 43);
    lv_obj_set_align(ui_flashSize, LV_ALIGN_CENTER);
    lv_label_set_text(ui_flashSize, "4194304");
    lv_obj_set_style_text_color(ui_flashSize, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_flashSize, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_backHome2, ui_event_backHome2, LV_EVENT_ALL, NULL);

}

void ui_SystemScreen_screen_destroy(void)
{
    if(ui_SystemScreen) lv_obj_del(ui_SystemScreen);

    // NULL screen variables
    ui_SystemScreen = NULL;
    ui_backHome2 = NULL;
    ui_Label6 = NULL;
    ui_temp = NULL;
    ui_Label8 = NULL;
    ui_tempValue = NULL;
    ui_cpu = NULL;
    ui_Label9 = NULL;
    ui_cpuValue = NULL;
    ui_ram = NULL;
    ui_Label10 = NULL;
    ui_ramValue = NULL;
    ui_Label11 = NULL;
    ui_Label12 = NULL;
    ui_Label13 = NULL;
    ui_chipModel = NULL;
    ui_cpuFreq = NULL;
    ui_flashSize = NULL;

}
