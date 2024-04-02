

#include QMK_KEYBOARD_H

enum {
    _ALPHA,   // default
    _SPECIAL, // special characters
    _NUMBERS, // numbers/function/motion
    _ADJUST   // 
};

#define KC_SFT_A  MT(MOD_LSFT, KC_A)     // Tap for A, hold for Shift
#define KC_SFT_CL MT(MOD_RSFT, KC_SCLN)  // Tap for ñ (latam keyboard), hold for Shift
#define KC_CTL_Z  MT(MOD_LCTL, KC_Z)     // Tap for Z, hold for Control
#define KC_CTL_SL MT(MOD_RCTL, KC_SLSH)  // Tap for minux (latam keyboard), hold for Control


#define KC_ALT_Q MT(MOD_LALT, KC_Q)  // Tap for Esc, hold for Alt (Option)
#define KC_SPE_SPC LT(_SPECIAL, KC_SPC)  // Tap for Space, hold for Special layer
#define KC_NUM_ENT LT(_NUMBERS, KC_ENT)  // Tap for Enter, hold for Numbers layer

    /* Combomap
     *
     * ,-------------------------------.      ,-------------------------------.
     * |       |     |    ESC    |     |      |    LMB   BSPC    |     |       |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |       |     |    TAB    |     |      |    RMB    |     |     |       |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |       |     |           |     |      |    MMB    |     |     |       |
     * `-------------------------------'      `-------------------------------'
     *            .-----------------.            .-----------------.
     *            |     |     |     |            |     |     |     |
     *            '-----------------'            '-----------------'
     */
const uint16_t PROGMEM combo1[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo5[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM combo6[] = {KC_N, KC_M, COMBO_END};

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
     * | SHFT A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |SHFT ñ |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | CTRL Z|  X  |  C  |  V  |  B  |      |  N  |  M  |  ,  |  .  |CTRL - |
     * `-------------------------------'      `-------------------------------'
     *   .------------------------------.    .----------------------.
     *   | LGUI(NUMBERS)| LGUI| SPC SPE |    | ENT NUM | TAB | MO(3) |
     *   '------------------------------'    '----------------------'
     */
    [_ALPHA] = LAYOUT_split_3x5_3(
         KC_ALT_Q, KC_W,   KC_E,   KC_R,   KC_T,          KC_Y,   KC_U,   KC_I,     KC_O,   KC_P,
         KC_SFT_A, KC_S,   KC_D,   KC_F,   KC_G,          KC_H,   KC_J,   KC_K,     KC_L,   KC_SFT_CL,
         KC_CTL_Z, KC_X,   KC_C,   KC_V,   KC_B,          KC_N,   KC_M,   KC_COMMA, KC_DOT, KC_CTL_SL,
        LM(_NUMBERS, MOD_LGUI), KC_LGUI, KC_SPE_SPC,      KC_NUM_ENT, KC_TAB, MO(_ADJUST)),

    /* Keymap 1: Special characters layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |    !  |  @  |  {  |  }  |  |  |      |  `  |  ~  |     |     |   \   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    #  |  $  |  (  |  )  | RMB |      |  +  |  -  |  /  |  *  |   '   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    %  |  ^  |  [  |  ]  | LMB |      |  &  |  =  |  ,  |  .  |   -   |
     * `-------------------------------'      `-------------------------------'
     *     .-------------------------.          .-----------------.
     *     | ComboToggle |  ;  |  =  |          |  =  |  ;  | DEL |
     *     '-------------------------'          '-----------------'
     */
    [_SPECIAL] = LAYOUT_split_3x5_3(
         KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,          KC_GRV,  KC_TILD, KC_TRNS, KC_TRNS, KC_BSLS,
         KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_BTN2,          KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_QUOT,
         KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_BTN1,          KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_MINS,
                            XXXXXXX, KC_SCLN, KC_EQL,          KC_EQL, KC_SCLN, KC_DEL),

    /* Keymap 2: Numbers/Function/Motion layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |   1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F1   | F2  | F3  | F4  | F5  |      | LFT | DWN | UP  | RGT | VOLUP |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  F6   | F7  | F8  | F9  | F10 |      | MLFT| MDWN| MUP | MRGT| VOLDN |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .-----------------.
     *             | F11 | F12 |     |          |     | PLY | SKP |
     *             '-----------------'          '-----------------'
     */
    [_NUMBERS] = LAYOUT_split_3x5_3(
         KC_1,  KC_2,  KC_3,  KC_4,  KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
         KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLU,
         KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_VOLD,
                    KC_F11, KC_F12, KC_TRNS,         KC_TRNS,  KC_MPLY,  KC_MNXT),
                    
    // Keymap 3: RGB Matrix
                        
    [_ADJUST] = LAYOUT_split_3x5_3(
      RGB_TOG, RGB_MOD, RGB_RMOD, XXXXXXX, XXXXXXX,                      RGB_TOG, RGB_MOD, RGB_RMOD, XXXXXXX, XXXXXXX,
      RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                       RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                       RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT)                    
};


