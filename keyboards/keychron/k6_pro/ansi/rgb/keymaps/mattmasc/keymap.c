#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "features/select_word.h"
#include "features/mouse_turbo_click.h"

// Left-hand home row mods
#define HOME_S LGUI_T(KC_S)
#define HOME_T LALT_T(KC_T)
#define HOME_R LSFT_T(KC_R)
#define HOME_D LCTL_T(KC_D)

// Right-hand home row mods
#define HOME_N RCTL_T(KC_N)
#define HOME_A RSFT_T(KC_A)
#define HOME_E LALT_T(KC_E)
#define HOME_I RGUI_T(KC_I)

#define CAPS_NAV LT(0, KC_CAPS)
#define REPEAT_NAV LT(0, REPEAT)
#define GRV_NUM LT(0, KC_GRV)
#define SPC_SYM LT(0, KC_SPC)

#define UNDO LCTL(KC_Z)
#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)

// clang-format off
enum layers {
    _WIN_BASE,
    _GAME,
    _NAV,
    _NUM,
    _SYM,
    _FUN,
    _SETT,
    _1,
    _2,
    _3,
    _MAC_BASE,
    _MAC_FN1,
};

enum custom_keycodes {
  WIN_SELWORD = SAFE_RANGE,
  MAC_SELWORD,
  GAME_CHAT,
  TURBO,
  REPEAT,
  NODK_QT,
  NODK_DQT,
  NODK_CIRC,
  NODK_TILD,
  NODK_GRV,
  KC_EUR,
  // Other custom keys...
};

bool game_chat_set;
uint8_t mod_state;
uint8_t oneshot_mod_state;
uint16_t last_keycode;

#ifdef TAP_DANCE_ENABLE
enum {
    DOT_TD,
};
#define TD_DOT TD(DOT_TD)
#else
#define TD_DOT KC_DOT
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_WIN_BASE] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,  KC_EQL,          KC_BSPC,       KC_DELETE,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
        KC_TAB,      KC_V,    KC_M,    KC_L,    KC_C,    KC_P,  KC_LBRC,   KC_Q,    KC_F,    KC_O,    KC_U,    KC_J,   KC_RBRC,     KC_BSLS,      KC_HOME,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        KC_CAPS,     HOME_S,  HOME_T,  HOME_R,  HOME_D,   KC_Y,  KC_SCLN,    TD_DOT,  HOME_N,  HOME_A,  HOME_E,  HOME_I,           KC_ENT,         KC_PGUP,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
            KC_LSFT,         KC_Z,    KC_K,  KC_X,    KC_G,    KC_W,  KC_SLSH,   KC_B,    KC_H,  KC_QUOT,  KC_COMM,       KC_RSFT,     KC_UP,   KC_PGDN,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_LCTL,    KC_LALT,    REPEAT_NAV,                         SPC_SYM,                         GRV_NUM, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN,  KC_RGHT
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_GAME] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
    KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,  KC_EQL,          KC_BSPC,       KC_DELETE,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
        KC_TAB,    KC_SCLN,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC,     KC_RBRC,      KC_HOME,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        KC_CAPS,   KC_QUOT,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  KC_BSLS,           GAME_CHAT,        KC_PGUP,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_LSFT,        KC_SLSH,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM,  TD_DOT,       KC_RSFT,      KC_UP,   KC_PGDN,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
     KC_LCTL,     KC_LALT,       TURBO,                          KC_SPC,                          REPEAT_NAV,SPC_SYM,GRV_NUM,KC_LEFT, KC_DOWN, KC_RGHT
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_NAV] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,         KC_TRNS,         KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
        KC_TRNS,  KC_TRNS,WIN_SELWORD,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_HOME, KC_UP,  KC_END, KC_DELETE, KC_TRNS,     KC_TRNS,      KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
         KC_TRNS,   KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_TRNS, KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,         KC_TRNS,         KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
            KC_TRNS,         UNDO,     CUT,    COPY,   PASTE,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
     KC_TRNS,     KC_TRNS,      KC_TRNS,                           KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_NUM] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        KC_TRNS,        KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
       KC_TRNS,     KC_ASTR,  KC_6,   KC_5,  KC_4,  KC_PLUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,WIN_SELWORD,KC_TRNS,KC_TRNS,     KC_TRNS,    KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
         KC_TRNS,     KC_3,    KC_2,    KC_1,   KC_0,   KC_EQL, KC_TRNS, KC_TRNS, KC_LCTL, KC_LSFT, KC_LALT,  KC_LGUI,         KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_TRNS,         KC_BSLS, KC_9,   KC_8,    KC_7,  KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_TRNS,    KC_TRNS,     KC_TRNS,                                KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_SYM] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        KC_TRNS,        KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
        KC_TRNS,    KC_EUR,  KC_DLR, KC_PLUS, KC_SLSH, KC_UNDS, KC_TRNS,   KC_AT, KC_AMPR, KC_PIPE, NODK_DQT, KC_HASH, KC_TRNS,     KC_TRNS,    KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        CW_TOGG,    KC_ASTR, KC_QUES, KC_EXLM, KC_COLN, KC_SCLN, CW_TOGG,  KC_EQL, KC_LPRN, KC_LCBR, KC_LBRC, KC_MINS,         KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_TRNS,       NODK_CIRC,NODK_TILD, KC_LT,  KC_GT,  KC_BSLS, NODK_GRV, KC_RPRN, KC_RCBR, KC_RBRC, KC_PERC,     KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_TRNS,    KC_TRNS,     KC_TRNS,                                KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_FUN] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,         KC_TRNS,         KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
       KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_F7,  KC_F8,   KC_F9,  KC_F12,      KC_TRNS,    KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        KC_TRNS,    KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS,  KC_F4,   KC_F5,   KC_F6,   KC_F11,          KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F10,      KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_TRNS,     KC_TRNS,     KC_TRNS,                          KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_SETT] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS, KC_BRID, KC_BRIU, KC_TASK, KC_FILE, RGB_VAD,  RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,        KC_TRNS,      TG(_GAME),
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
       KC_TRNS,    BT_HST1, BT_HST2, BT_HST3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     AC_TOGG,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        RGB_TOG,    RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
            KC_TRNS,       RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  BAT_LVL,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_OS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_1] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
       KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_TRNS,    KC_TRNS,     KC_TRNS,                                KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_2] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
       KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_TRNS,    KC_TRNS,     KC_TRNS,                                KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_3] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
   KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,  KC_TRNS,        KC_TRNS,        KC_TRNS,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
       KC_TRNS,    KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
        KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS,        KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
           KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,  KC_TRNS,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
      KC_TRNS,    KC_TRNS,     KC_TRNS,                                KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
    ),

[_MAC_BASE] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
     KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, RGB_MOD,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_HOME,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,  KC_PGUP,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
//|------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
     KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                       KC_RCMMD,MO(_MAC_FN1),MO(_FUN), KC_LEFT,  KC_DOWN, KC_RGHT
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
     ),

[_MAC_FN1] = LAYOUT_ansi_68(
//,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------------+--------+.
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  RGB_TOG,
//|---------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+----------------+--------+|
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
//|----------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------------------------+--------+|
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
//|-----------------------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------+--------+|
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
//|-----------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+|
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
//`------------+------------+------------+--------------------------------------------------------+--------+--------+--------+--------+--------+--------+'
     ),
};

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
  switch (other_keycode) {
    case QK_MOD_TAP ... QK_MOD_TAP_MAX:
    case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
      other_keycode &= 0xff;  // Get base keycode.
  }

  // Allow same-hand holds with tri_layer and non-alpha keys.
  if (tap_hold_keycode == REPEAT_NAV || tap_hold_keycode == SPC_SYM || tap_hold_keycode == GRV_NUM || other_keycode > KC_Z) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state|default_layer_state);

    switch(layer) {
        case 1:
            rgb_matrix_set_color(18, RGB_RED);
            rgb_matrix_set_color(32, RGB_RED);
            rgb_matrix_set_color(33, RGB_RED);
            rgb_matrix_set_color(34, RGB_RED);
            break;
        default:
            break;
    }
    // Layer indicator only on keys with configured keycodes:
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED &&
            keymap_key_to_keycode(layer, (keypos_t){col,row}) <= KC_TRNS) {
                rgb_matrix_set_color(index, RGB_OFF);
            }
        }
    }
    return false;
}

static void sentence_end(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {

        // Double tapping TD_DOT produces
        // ". <one-shot-shift>" i.e. dot, space and capitalize next letter.
        // This helps to quickly end a sentence and begin another one
        // without having to hit shift.
        case 2:
            /* Check that Shift is inactive */
            if (!(get_mods() & MOD_MASK_SHIFT)) {
                tap_code(KC_SPC);
                /* Internal code of OSM(MOD_LSFT) */
                add_oneshot_mods(MOD_BIT(KC_LEFT_SHIFT));

            } else {
                // send ">" (KC_DOT + shift → ">")
                tap_code(KC_DOT);
            }
            break;

        // Since `sentence_end` is called on each tap
        // and not at the end of the tapping term,
        // the third tap needs to cancel the effects
        // of the double tap in order to get the expected
        // three dots ellipsis.
        case 3:
            // remove the added space of the double tap case
            tap_code(KC_BSPC);
            // replace the space with a second dot
            tap_code(KC_DOT);
            // tap the third dot
            tap_code(KC_DOT);
            break;

        // send KC_DOT on every normal tap of TD_DOT
        default:
            tap_code(KC_DOT);
    }
};

void sentence_end_finished (tap_dance_state_t *state, void *user_data) {
    last_keycode = KC_DOT;
}

tap_dance_action_t tap_dance_actions[] = {
    [DOT_TD] = ACTION_TAP_DANCE_FN_ADVANCED(sentence_end, sentence_end_finished, NULL),
};

inline uint8_t get_tap_kc(uint16_t dual_role_key) {
    // Used to extract the basic tapping keycode from a dual-role key.
    // Example: get_tap_kc(MT(MOD_RSFT, KC_E)) == KC_E
    return dual_role_key & 0xFF;
}

static void process_repeat_key(uint16_t keycode, const keyrecord_t *record) {
    static uint8_t last_modifier = 0;
    if (keycode != REPEAT) {
        // Early return when holding down a pure layer key
        // to retain modifiers
        switch (keycode) {
            case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
            case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            case QK_TO ... QK_TO_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            case REPEAT_NAV:
                return;
        }
        last_modifier = oneshot_mod_state | mod_state;
        switch (keycode) {
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
                if (record->event.pressed) {
                    last_keycode = get_tap_kc(keycode);
                }
                break;
            default:
                if (record->event.pressed) {
                    last_keycode = keycode;
                }
                break;
        }
    } else { // keycode == REPEAT
        if (record->event.pressed) {
            register_mods(last_modifier);
            register_code16(last_keycode);
        } else {
            unregister_code16(last_keycode);
            unregister_mods(last_modifier);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_repeat_key(keycode, record);
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    if (!process_achordion(keycode, record)) { return false; }
    if (!process_win_select_word(keycode, record, WIN_SELWORD)) { return false; }
    if (!process_mac_select_word(keycode, record, MAC_SELWORD)) { return false; }
    if (!process_mouse_turbo_click(keycode, record, TURBO)) { return false; }

    switch (keycode) {
        case CAPS_NAV:
            if (record->tap.count) {
                tap_code16(KC_CAPS);
                return false; // Return false to ignore further processing of key
            } else if (record->event.pressed) {
                layer_on(_NAV);
                update_tri_layer(_NAV, _SYM, _FUN);
                update_tri_layer(_NAV, _NUM, _1);
            } else {
                layer_off(_NAV);
                update_tri_layer(_NAV, _SYM, _FUN);
                update_tri_layer(_NAV, _NUM, _1);
            }
            return false;
        case REPEAT_NAV:
            if (record->tap.count) {
                process_repeat_key(REPEAT, record);
                return false; // Return false to ignore further processing of key
            } else if (record->event.pressed) {
                layer_on(_NAV);
                update_tri_layer(_NAV, _SYM, _FUN);
                update_tri_layer(_NAV, _NUM, _1);
            } else {
                layer_off(_NAV);
                update_tri_layer(_NAV, _SYM, _FUN);
                update_tri_layer(_NAV, _NUM, _1);
            }
            return false;
        case SPC_SYM:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_SPC);
                caps_word_off(); // Turn off Caps World
                return false; // Return false to ignore further processing of key
            } else if (record->event.pressed) {
                layer_on(_SYM);
                update_tri_layer(_SYM, _NAV, _FUN);
                update_tri_layer(_SYM, _NUM, _SETT);
            } else {
                layer_off(_SYM);
                update_tri_layer(_SYM, _NAV, _FUN);
                update_tri_layer(_SYM, _NUM, _SETT);
            }
            return false;
        case GRV_NUM:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_GRV);
                return false; // Return false to ignore further processing of key
            } else if (record->event.pressed) {
                layer_on(_NUM);
                update_tri_layer(_NUM, _NAV, _1);
                update_tri_layer(_NUM, _SYM, _SETT);
            } else {
                layer_off(_NUM);
                update_tri_layer(_NUM, _NAV, _1);
                update_tri_layer(_NUM, _SYM, _SETT);
            }
            return false;
        case KC_ESC:                                       // Cancels chat mode in most games
            if (game_chat_set && record->event.pressed) {  // Checks if GAME_CHAT was pressed in-game
                tap_code16(KC_ESC);
                game_chat_set = false;
                layer_invert(_GAME);                     // Switches back to GAMING layer after chatting
            }
            return true; // Let QMK handle the rest
        case KC_ENT:
            if (game_chat_set && record->event.pressed) {  // Checks if GAME_CHAT was pressed in-game
                tap_code16(KC_ENT);
                game_chat_set = false;
                layer_invert(_GAME);                     // Switches back to GAMING layer after chatting
            }
            return true; // Let QMK handle the rest
        // GAME_CHAT: A key that taps enter to enable chat in-game, and temporarily toggles typing layer
        // When done chatting, pressing enter or esc will automatically swap back to game layer
        case GAME_CHAT:
            if (record->event.pressed) {
                tap_code16(KC_ENT);
                layer_invert(_GAME);
                game_chat_set = true;
            }
            return false;
        case NODK_QT: // Types '
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_QUOT) SS_TAP(X_SPC));
            }
            return false;
        case NODK_DQT: // Types "
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_QUOT)) SS_TAP(X_SPC));
            }
            return false;
        case NODK_CIRC: // Types ^
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_6)) SS_TAP(X_SPC));
            }
            return false;
        case NODK_TILD: // Types ~
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_GRV)) SS_TAP(X_SPC));
            }
            return false;
        case NODK_GRV: // Types `
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_GRV) SS_TAP(X_SPC));
            }
            return false;
        case KC_EUR: // Types €
            if (record->event.pressed) {
                SEND_STRING(SS_RALT(SS_TAP(X_5)));
            }
            return false;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_D):
        case RCTL_T(KC_N):
            return TAPPING_TERM + 20;
        case LSFT_T(KC_R):
        case RSFT_T(KC_A):
            return TAPPING_TERM + 40;
        case LALT_T(KC_T):
        case LALT_T(KC_E):
            return TAPPING_TERM + 60;
        case LGUI_T(KC_S):
        case RGUI_T(KC_I):
            return TAPPING_TERM + 80;
        default:
            return TAPPING_TERM;
    }
}
