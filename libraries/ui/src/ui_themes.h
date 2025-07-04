// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.2
// LVGL version: 8.3.6
// Project name: ESP32-2432S028R

#ifndef _UI_THEMES_H
#define _UI_THEMES_H

#ifdef __cplusplus
extern "C" {
#endif

#define UI_THEME_COLOR_BLACK 0

#define UI_THEME_DEFAULT 0

#define UI_THEME_DARK 1

extern const ui_theme_variable_t _ui_theme_color_Black[2];
extern const ui_theme_variable_t _ui_theme_alpha_Black[2];

extern const uint32_t * ui_theme_colors[2];
extern const uint8_t * ui_theme_alphas[2];
extern uint8_t ui_theme_idx;

void ui_theme_set(uint8_t theme_idx);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
