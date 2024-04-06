#include QMK_KEYBOARD_H
#include "quantum/keymap_extras/keymap_spanish_latin_america.h"


bool should_process_keypress(void) { return true; }

enum {
    _ALPHA,   // default
    _SPECIAL, // special characters
    _NUMBERS, // numbers/function/motion
    _ADJUST   // 
};

void dance_e_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_E);
  } else {
    register_code (ES_ACUT);
    register_code (KC_E);
  }
}

void dance_e_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_E);
  } else {
    unregister_code (ES_ACUT);
    unregister_code (KC_E);
  }
}

void dance_i_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_I);
  } else {
    register_code (ES_ACUT);
    register_code (KC_I);
  }
}

void dance_i_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_I);
  } else {
    unregister_code (ES_ACUT);
    unregister_code (KC_I);
  }
}

void dance_o_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_O);
  } else {
    register_code (ES_ACUT);
    register_code (KC_O);
  }
}

void dance_o_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_O);
  } else {
    unregister_code (ES_ACUT);
    unregister_code (KC_O);
  }
}

void dance_u_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_U);
  } else {
    register_code (ES_ACUT);
    register_code (KC_U);
  }
}

void dance_u_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_U);
  } else {
    unregister_code (ES_ACUT);
    unregister_code (KC_U);
  }
}

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;
static td_state_t td_state;

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}
 
void sfta_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code (KC_A);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      register_code (ES_ACUT);
      register_code (KC_A);
  }
}

void sfta_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code (KC_A);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code (ES_ACUT);
      unregister_code (KC_A);
  }
}

enum {
  TD_DOT_CLN,
  TD_COMM_SCLN,
  TD_L_UNDS,
  SFT_A,
  CT_E,
  CT_I,
  CT_O,
  CT_U
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_DOT_CLN]  = ACTION_TAP_DANCE_DOUBLE(ES_DOT, ES_COLN),
  [TD_COMM_SCLN]  = ACTION_TAP_DANCE_DOUBLE(ES_COMM, ES_SCLN),
  [TD_L_UNDS]  = ACTION_TAP_DANCE_DOUBLE(KC_L, ES_UNDS),
  [SFT_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sfta_finished, sfta_reset),
  [CT_E] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_e_finished, dance_e_reset),
  [CT_I] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_i_finished, dance_i_reset),
  [CT_O] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_o_finished, dance_o_reset),
  [CT_U] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_u_finished, dance_u_reset)
};

#define KC_SFT_A  MT(MOD_LSFT, KC_A)     // Tap for A, hold for Shift
#define KC_SFT_CL MT(MOD_RSFT, ES_NTIL)  // Tap for ñ (latam keyboard), hold for Shift
#define KC_CTL_Z  MT(MOD_LCTL, KC_Z)     // Tap for Z, hold for Control
#define KC_CTL_SL MT(MOD_RCTL, ES_MINS)  // Tap for minus (latam keyboard), hold for Control


#define KC_ALT_Q MT(MOD_LALT, KC_Q)  // Tap for Esc, hold for Alt (Option)
#define KC_NUM_SPC LT(_NUMBERS, KC_SPC)  // Tap for Space, hold for Special layer
#define KC_SPE_ENT LT(_SPECIAL, KC_ENT)  // Tap for Enter, hold for Numbers layer

    /* Combomap
     *
     * ,-----------------------------.      ,-----------------------------.
     * |     |     |     |    LMB    |      |     |     |     |     |     |
     * |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-----|
     * |     |    TAB   ESC   RMB    |      |     |   BSPC    |     |     |
     * |-----+-----+-----+-----+-----|      |-----+-----+-----+-----+-----|
     * |     |     |     |    MMB    |      |     |     |     |     |     |
     * `-----------------------------'      `-----------------------------'
     *             .-----------------.       .-----------------.
     *             |     |     |     |       |     |     |     |
     *             '-----------------'       '-----------------'
     */
const uint16_t PROGMEM combo1[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo5[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_V, KC_B, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo1, KC_ESC),
    COMBO(combo2, KC_TAB),
    COMBO(combo3, KC_BSPC),
    COMBO(combo4, KC_BTN1),
    COMBO(combo5, KC_BTN2),
    COMBO(combo6, KC_BTN3),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Alpha layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |     Q |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |   P   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | SHFT A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  | L(_)|SHFT ñ |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | CTRL Z|  X  |  C  |  V  |  B  |      |  N  |  M  |,(;) |.(:) |CTRL - |
     * `-------------------------------'      `-------------------------------'
     *   .------------------------------.     .----------------------.
     *   | LGUI(NUMBERS)| LGUI| SPC NUM |     | ENT SPE | TAB | MO(3) |
     *   '------------------------------'     '----------------------'
     */
    [_ALPHA] = LAYOUT_split_3x5_3(
         KC_ALT_Q,  KC_W,   TD(CT_E),  KC_R,   KC_T,      KC_Y,   TD(CT_U),   TD(CT_I),         TD(CT_O),       KC_P,
         TD(SFT_A), KC_S,   KC_D,      KC_F,   KC_G,      KC_H,   KC_J,       KC_K,             TD(TD_L_UNDS),  KC_SFT_CL,
         KC_CTL_Z, KC_X,    KC_C,      KC_V,   KC_B,      KC_N,   KC_M,       TD(TD_COMM_SCLN), TD(TD_DOT_CLN), KC_CTL_SL,
        LM(_NUMBERS, MOD_LGUI), KC_LGUI, KC_NUM_SPC,      KC_SPE_ENT, KC_TAB, MO(_ADJUST)),

    /* Keymap 1: Special characters layer
     *
     * ,------------------------------.      ,------------------------------.
     * |   !  |  ?  |  {  |  }  |  |  |      |  "  |  '  |  &  |  ¡  |  ¿   |
     * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+------|
     * |   #  |  @  |  (  |  )  |  \  |      |  +  |  -  |  /  |  *  |  =   |
     * |------+-----+-----+-----+-----|      |-----+-----+-----+-----+------|
     * |   %  |  $  |  [  |  ]  |  /  |      |  ó  |  ~  |  ,  |  .  |  ^   |
     * `------------------------------'      `------------------------------'
     *                .----------------.     .-----------------.
     *                |    |     |     |     |     |     |     |
     *                '----------------'     '-----------------'
     */
    [_SPECIAL] = LAYOUT_split_3x5_3(
         ES_EXLM, ES_QUES, ES_LCBR, ES_RCBR, ES_PIPE,          ES_DQUO, ES_QUOT, ES_AMPR, ES_IEXL, ES_IQUE,
         ES_NUMB, ES_AT,   ES_LPRN, ES_RPRN, ES_BSLS,          ES_PLUS, ES_MINS, ES_SLSH, ES_ASTR, ES_EQL ,
         ES_PERC, ES_DLR,  ES_LBRC, ES_RBRC, ES_SLSH,          ES_ACUT, ES_TILD, ES_COMM, ES_DOT,  ES_CIRC,
                           KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),

    /* Keymap 2: Numbers/Function/Motion layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |   1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F1   | F2  | F3  | F4  | F5  |      | LFT | DWN | UP  | RGT | VOLUP |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F6   | F7  | F8  | F9  | F10 |      | HOME| END | INS | DEL | VOLDN |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .--------------------.
     *             | F11 | F12 | PLY |          | SKP  | PGUP | PGDN |
     *             '-----------------'          '--------------------'
     */
    [_NUMBERS] = LAYOUT_split_3x5_3(
         KC_1,  KC_2,  KC_3,  KC_4,  KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
         KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU,
         KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,         KC_HOME, KC_END,  KC_INS,  KC_DEL, KC_VOLD,
                    KC_F11, KC_F12, KC_MPLY,         KC_MNXT,  KC_PGUP,  KC_PGDN),
                    
    // Keymap 3: RGB Matrix
                        
    [_ADJUST] = LAYOUT_split_3x5_3(
      RGB_TOG, RGB_MOD, RGB_RMOD, XXXXXXX, XXXXXXX,                      RGB_TOG, RGB_MOD, RGB_RMOD, XXXXXXX, XXXXXXX,
      RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                       RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                       RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT)                    
};


