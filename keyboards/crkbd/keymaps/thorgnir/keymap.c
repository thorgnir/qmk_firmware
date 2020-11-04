#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
//   LOWER,
//   RAISE,
//   ADJUST
};



#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
// #define KC_LOWER LOWER
// #define KC_RAISE RAISE
#define KC_RST   RESET
// #define KC_GUIEI GUI_T(KC_LANG2)
// #define KC_ALTKN ALT_T(KC_LANG1)

// #define RBR_RGU MT(MOD_RGUI, KC_RBRC)
// #define F12_RGU MT(MOD_RGUI, KC_F12)
#define PLS_LCT MT(MOD_LCTL, KC_PPLS)
#define CAPS_LCT MT(MOD_LCTL, KC_CAPS)
#define EQL_LCT MT(MOD_LCTL, KC_PEQL)
// #define APP_LCT MT(MOD_LCTL, KC_APP)
// #define EQL_RCT MT(MOD_RCTL, KC_PEQL)
// #define QUO_RCT MT(MOD_RCTL, KC_QUOT)
// #define APP_RCT MT(MOD_RCTL, KC_APP)
// #define MIN_RCT MT(MOD_RCTL, KC_MINS)
#define RGUI_MIN MT(MOD_RGUI, KC_MINS)
#define RGUI_QUOT MT(MOD_RGUI, KC_QUOT)
#define EQL_LAL MT(MOD_LALT, KC_EQL)
#define BSL_RAL MT(MOD_RALT, KC_BSLS)

// #define NBS_LCT MT(MOD_LCTL, KC_NUBS)
// #define BSH_LAL MT(MOD_LALT, KC_BSLS)
// #define APP_RAL MT(MOD_RALT, KC_APP)

#define BSP_RSH MT(MOD_RSFT, KC_BSPC)
#define SPC_LSH MT(MOD_LSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(\
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, RGUI_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,                          KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, BSL_RAL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          TAB_RSE,SPC_LSH,ENT_LWR,     ESC_LWR, BSP_RSH, DEL_RSE\
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT(\
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_UNDS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC,                       KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RBRC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|

     PLS_LCT, KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RGUI_MIN,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|

     EQL_LAL,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_RALT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,_______,_______,     _______, _______, _______\


  ),

  [_RAISE] = LAYOUT(\
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_F1,   KC_F4,   KC_F7,   KC_F10, KC_LBRC,                      KC_RBRC, KC_HOME,  KC_UP,   KC_END,  KC_INS,  KC_CAPS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_F2,   KC_F5,   KC_F8,   KC_F11, KC_LCBR,                      KC_RCBR, KC_LEFT,  KC_DOWN, KC_RGHT, KC_PGUP, KC_RGUI,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT, KC_F3,   KC_F6,   KC_F9,   KC_F12, XXXXXXX,                      KC_PSCR, XXXXXXX,  XXXXXXX, XXXXXXX, KC_PGDN, KC_RALT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,_______,_______,     _______, _______, _______\
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT(\
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,_______,_______,     _______, _______, _______\
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}



layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;d
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;

  }
  return true;
}
