#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1

typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

//Tap dance enums
enum {
 CAPS_LANG_FN = 0
};


//Declare the functions to be used with your tap dance key(s)

//Function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

//Functions associated with individual tap dances
void clf_finished (qk_tap_dance_state_t *state, void *user_data);
void clf_reset (qk_tap_dance_state_t *state, void *user_data);

//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
		[_LAYER0] = LAYOUT_65_ansi_blocker( /* Base */
			KC_GESC,            KC_1,     KC_2,     KC_3,       KC_4,       KC_5,  KC_6,    KC_7,  KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,   KC_HOME,\
		  KC_TAB,             KC_Q,     KC_W,     KC_E,       KC_R,       KC_T,  KC_Y,    KC_U,  KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC, KC_BSLASH, KC_PGUP,\
			TD(CAPS_LANG_FN),   KC_A,     KC_S,     KC_D,       KC_F,       KC_G,  KC_H,    KC_J,  KC_K,    KC_L,     KC_SCLN,  KC_QUOT,           KC_ENT,    KC_PGDN,\
		  KC_LSFT,            KC_Z,     KC_X,     KC_C,       KC_V,       KC_B,  KC_N,    KC_M,  KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,           KC_UP,     KC_END,\
		  KC_LCTL,            KC_LGUI,  KC_LALT,                KC_SPC,                MO(1),             KC_RCTL,  KC_LEFT,           KC_DOWN,   KC_RIGHT),
		[_LAYER1] = LAYOUT_65_ansi_blocker( /* FN */
			KC_GESC,            KC_F1,    KC_F2,    KC_F3,      KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,   KC_HOME,\
      KC_TRNS,            KC_TRNS,  KC_HOME,  KC_UP,      KC_END,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK,  KC_PAUS, RESET,    KC_PGUP,\
			CTL_T(KC_CAPS),     KC_TRNS,  KC_LEFT,  KC_DOWN,    KC_RIGHT,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          EEP_RST,  KC_PGDN,\
      KC_LSFT,            KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,          KC_VOLU,  KC_MUTE,\
      KC_TRNS,            KC_TRNS,  KC_TRNS,                  KC_TRNS,                   KC_TRNS,          KC_TRNS,  KC_MPRV,          KC_VOLD,  KC_MNXT),
};
void matrix_init_user(void)
{
  //user initialization
}

void matrix_scan_user(void)
{
  //user matrix
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

	return true;
}


//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 8;
}

//Initialize tap structure associated with example tap dance key
static tap clf_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void clf_finished (qk_tap_dance_state_t *state, void *user_data) {
  clf_tap_state.state = cur_dance(state);
  switch (clf_tap_state.state) {
    case SINGLE_TAP:
      register_code(KC_LCTL);
      tap_code(KC_LSFT);
      unregister_code(KC_LCTL);
      break;
    case SINGLE_HOLD:
      layer_on(_LAYER1);
      break;
    case DOUBLE_TAP:
      tap_code(KC_CAPS);
      break;
  }
}

void clf_reset (qk_tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (clf_tap_state.state==SINGLE_HOLD) {
    layer_off(_LAYER1);
  }
  clf_tap_state.state = 0;
}


//Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [CAPS_LANG_FN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, clf_finished, clf_reset, 200)
};
