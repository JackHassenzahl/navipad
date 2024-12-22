// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {
    WIN_FOR,
    WIN_BACK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        RGUI(KC_TAB), RALT(KC_F4), LGUI(KC_LBRC), RGUI(KC_RBRC), MO(1),
        RALT(KC_1), RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_5),
        RALT(KC_6), RALT(KC_7), RALT(KC_8), RALT(KC_9), KC_TRNS,
        RCTL(KC_Z), RCS(KC_Z), KC_CUT, KC_COPY, KC_PSTE
    ),

    [1] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};

const uint16_t PROGMEM encoder_map[][1][2] = {
    [0] = { ENCODER_CCW_CW(WIN_BACK, WIN_FOR) },
    [1] = { ENCODER_CCW_CW(RCTL(KC_TAB), RCTL(KC_TAB)) }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case WIN_FOR:
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
                return false;
            case WIN_BACK:
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_RSFT);
                tap_code(KC_TAB);
                unregister_code(KC_RSFT);
                return false;
        }
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}