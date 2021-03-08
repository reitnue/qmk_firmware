#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

enum tap_dance_declarations {
    TD_I_ESC,
    TD_A_CTRL_A,
    TD_C_CTRL_C,
    TD_Z_CTRL_Z,
};


// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
// TD_A_CTRL_A
void td_a_ctrl_a_finished(qk_tap_dance_state_t *state, void *user_data);
void td_a_ctrl_a_reset(qk_tap_dance_state_t *state, void *user_data);
// TD_C_CTRL_C
void td_c_ctrl_c_finished(qk_tap_dance_state_t *state, void *user_data);
void td_c_ctrl_c_reset(qk_tap_dance_state_t *state, void *user_data);
// TD_Z_CTRL_Z
void td_z_ctrl_z_finished(qk_tap_dance_state_t *state, void *user_data);
void td_z_ctrl_z_reset(qk_tap_dance_state_t *state, void *user_data);


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_I_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_ESC), // tap once for "i", twitce for ESC
    [TD_A_CTRL_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_a_ctrl_a_finished, td_a_ctrl_a_reset), // tap once for "a", twice fo Ctrl a
    [TD_C_CTRL_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_c_ctrl_c_finished, td_c_ctrl_c_reset), // tap once for "a", twice fo Ctrl a
    [TD_Z_CTRL_Z] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_z_ctrl_z_finished, td_z_ctrl_z_reset), // tap once for "a", twice fo Ctrl a
};

// COMBOS
enum combo_events {
    QW_CTRL_W,
};

const uint16_t PROGMEM qw_ctrl_w_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [QW_CTRL_W] = COMBO_ACTION(qw_ctrl_w_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case QW_CTRL_W:
            if (pressed) {
              tap_code16(LCTL(KC_W));
            }
            break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_GRV,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,            KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    TD(TD_I_ESC),    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        MO(2),          TD(TD_A_CTRL_A),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,            KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT,        TD(TD_Z_CTRL_Z),    KC_X,    TD(TD_C_CTRL_C),    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,         KC_DOT,  KC_SLSH, MO(3),            KC_UP,   KC_PGDN, \
        KC_LCTL,        KC_LALT, KC_LGUI,                            KC_SPC,                            KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END,  \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        _______, LAG_SWP, LAG_NRM,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    [2] = LAYOUT_65_ansi_blocker(
        _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    [3] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_4,    KC_5,    KC_6,    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, KC_1,    KC_2,    KC_3,    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            KC_0,                               _______, _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    } break;
                }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE || rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
        return;
    }
    int layer = get_highest_layer(layer_state);
    switch (layer) {
        case 3:
            // explicit fallthrough
        case 2:
            rgb_matrix_set_color(36, RGB_WHITE);
            rgb_matrix_set_color(37, RGB_WHITE);
            rgb_matrix_set_color(38, RGB_WHITE);
            rgb_matrix_set_color(39, RGB_WHITE);
            // explicit fallthrough
        case 1:
            // explicit fallthrough
        case 0:
            rgb_matrix_set_color(1, RGB_GREEN);
            rgb_matrix_set_color(2, RGB_GREEN);
            rgb_matrix_set_color(3, RGB_GREEN);
            rgb_matrix_set_color(4, RGB_GREEN);
            rgb_matrix_set_color(5, RGB_GREEN);
            rgb_matrix_set_color(6, RGB_GREEN);
            rgb_matrix_set_color(7, RGB_GREEN);
            rgb_matrix_set_color(8, RGB_GREEN);
            rgb_matrix_set_color(9, RGB_GREEN);
            rgb_matrix_set_color(10, RGB_GREEN);
            rgb_matrix_set_color(11, RGB_GREEN);
            rgb_matrix_set_color(12, RGB_GREEN);
            // explicit fallthrough
        default:
            rgb_matrix_set_color(16, RGB_CYAN); // Q
            rgb_matrix_set_color(17, RGB_CYAN); // W
            rgb_matrix_set_color(23, RGB_MAGENTA); // I
            rgb_matrix_set_color(31, RGB_MAGENTA); // A
            rgb_matrix_set_color(45, RGB_MAGENTA); // Z
            rgb_matrix_set_color(47, RGB_MAGENTA); // C
            break;
    }
    return;
}

// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        return SINGLE_TAP;
    } else if (state->count == 2) {
        return DOUBLE_SINGLE_TAP;
    } else {
        return 99; // Any number higher than the maximum state value you return above
    }
}

// Handle the possible states for each tapdance keycode you define:
// TD_A_CTRL_A
void td_a_ctrl_a_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            tap_code(KC_A);
            break;
        case DOUBLE_SINGLE_TAP:
            register_code16(LCTL(KC_A));
    }
}

void td_a_ctrl_a_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(LCTL(KC_A));
    }
}


// TD_C_CTRL_C
void td_c_ctrl_c_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            tap_code(KC_C);
            break;
        case DOUBLE_SINGLE_TAP:
            register_code16(LCTL(KC_C));
    }
}

void td_c_ctrl_c_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(LCTL(KC_C));
    }
}


// TD_Z_CTRL_Z
void td_z_ctrl_z_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            tap_code(KC_Z);
            break;
        case DOUBLE_SINGLE_TAP:
            register_code16(LCTL(KC_Z));
    }
}

void td_z_ctrl_z_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(LCTL(KC_Z));
    }
}
