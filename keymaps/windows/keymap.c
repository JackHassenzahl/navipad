// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {
    WIN_FOR,
    WIN_BACK,
    DESK_FOR,
    DESK_BACK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        LT(6, KC_MPLY), KC_MUTE, KC_VOLD, KC_VOLU, MO(1),
        RGUI(KC_1), RGUI(KC_2), RGUI(KC_3), RGUI(KC_TAB), TO(0),
        RGUI(KC_4), RGUI(KC_5), RGUI(KC_6), RALT(KC_F4), TO(2),
        RCTL(KC_T), RCTL(KC_W), RCS(KC_TAB), RCTL(KC_TAB), TO(4)
    ),

    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3),
        KC_HOME, KC_END, KC_PGUP, RSFT(KC_UP), KC_TRNS,
        RCTL(KC_Z), RCS(KC_Z), KC_PGDN, RSFT(KC_DOWN), KC_TRNS,
        RCTL(KC_X), RCTL(KC_C), RCTL(KC_V), RCTL(KC_F), KC_TRNS
    ),

    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [4] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(5),
        MS_ACL2, KC_BTN4, KC_BTN3, KC_BTN5, KC_TRNS,
        MS_ACL1, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS,
        MS_ACL0, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS
    ),

    [5] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [6] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};

const uint16_t PROGMEM encoder_map[][1][2] = {
    [0] = { ENCODER_CCW_CW(WIN_BACK, WIN_FOR) },
    [1] = { ENCODER_CCW_CW(DESK_BACK, DESK_FOR) },
    [2] = { ENCODER_CCW_CW(KC_DOWN, KC_UP) },
    [3] = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [4] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
    [5] = { ENCODER_CCW_CW(KC_WH_L, KC_WH_R) },
    [6] = { ENCODER_CCW_CW(KC_NO, KC_NO) }
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
            case DESK_FOR:
                register_code(KC_RGUI);
                register_code(KC_RCTL);
                tap_code(KC_RGHT);
                unregister_code(KC_RCTL);
                unregister_code(KC_RGUI);
                return true;
            case DESK_BACK:
                register_code(KC_RGUI);
                register_code(KC_RCTL);
                tap_code(KC_LEFT);
                unregister_code(KC_RCTL);
                unregister_code(KC_RGUI);
            return true;
        }
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}