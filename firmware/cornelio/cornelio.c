/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
        return OLED_ROTATION_270;
}

static void oled_render_layer_state(void) {
    oled_write_ln_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("DEF"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("SYM"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("CONF"), false);
            break;
        default:
            oled_write_ln_P(PSTR("UNDEF"), false);
            break;
    }
    oled_write_ln_P(PSTR("-----"), false);
}

char     key_name = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    // save the row and column (useful even if we can't find a keycode to show)
    last_row = record->event.key.row;
    last_col = record->event.key.col;

    key_name     = ' ';
    last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else {
            keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    key_name = pgm_read_byte(&code_to_name[keycode]);
}

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char)
        ++depad_str;
    return depad_str;
}

static void oled_render_keylog(void) {
    oled_write_ln_P(PSTR("key:"), false);
    oled_write_P(PSTR("->"), false);
    oled_write_char('0' + last_row, false);
    oled_write_P(PSTR("x"), false);
    oled_write_char('0' + last_col, false);
    const char *last_keycode_str = get_u16_str(last_keycode, ' ');
    oled_write_P(PSTR("#"), false);
    oled_write(depad_str(last_keycode_str, ' '), false);
    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);
    if (key_name != ' ') {
      oled_write_P(PSTR("  "), false);
      oled_write_char(key_name, false);
      oled_write_P(PSTR("  "), false);
      oled_write_ln_P(PSTR(" "), false);
      oled_write_ln_P(PSTR(" "), false);
    } else {
      oled_write_ln_P(PSTR(" "), false);
      oled_write_ln_P(PSTR(" "), false);
      oled_write_ln_P(PSTR(" "), false);
      oled_write_ln_P(PSTR(" "), false);
    }
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_render_layer_state();
    oled_render_keylog();
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return process_record_user(keycode, record);
}
#endif // OLED_ENABLE
