#include QMK_KEYBOARD_H
#include "custom_key_pair.h"
#include "keymap_jp.h"

enum index_code {
  CUSTOM,
  RAW,
  SHIFTED,
};

const uint16_t keypair[][3] = {
  // custom raw      shifted
  {CP_2,    KC_2,    JP_AT},
  {CP_6,    KC_6,    JP_CIRC},
  {CP_7,    KC_7,    JP_AMPR},
  {CP_8,    KC_8,    JP_ASTR},
  {CP_9,    KC_9,    JP_LPRN},
  {CP_0,    KC_0,    JP_RPRN},
  {CP_EQL,  JP_EQL,  JP_PLUS},
  {CP_MINS, JP_MINS, JP_UNDS},
  {CP_LBRC, JP_LBRC, JP_LCBR},
  {CP_RBRC, JP_RBRC, JP_RCBR},
  {CP_SCLN, JP_SCLN, JP_COLN},
  {CP_QUOT, JP_QUOT, JP_DQUO},
  {CP_BSLS, KC_JYEN, JP_PIPE},
  {CP_RO,   KC_JYEN, JP_UNDS},
};

static int pair_index(int custom_codes) {
  for (int i = 0; i < sizeof(keypair)/sizeof(keypair[0]); i++) {
    if (keypair[i][CUSTOM] == custom_codes) return i;
  }
  return -1;
}

bool custom_key_pair(uint16_t keycode, keyrecord_t *record) {
  static uint16_t origin_code = _______;
  static uint16_t stash_code  = _______;
  static uint8_t  stash_shift = 0;

  if (keycode == KC_LSFT || keycode == KC_RSFT) {
    if (record->event.pressed) {
      stash_shift |= MOD_BIT(keycode);
      int index = pair_index(origin_code);
      if (index != -1) {
        stash_code = keypair[index][SHIFTED];
        unregister_code16(keypair[index][RAW]);
        register_code16(stash_code);
        return false;
      }
    } else {
      stash_shift &= ~MOD_BIT(keycode);
      int index = pair_index(origin_code);
      if (index != -1 && stash_shift == 0) {            
        stash_code = keypair[index][RAW];
        unregister_code16(keypair[index][SHIFTED]);
        register_code16(stash_code);
        return false;
      }
    }
    return true;
  }

  int index = pair_index(keycode);
  if (index != -1) {
    if (record->event.pressed) {
      uint8_t shift_bits = stash_shift & MOD_MASK_SHIFT;
      origin_code = keypair[index][CUSTOM];
      stash_code  = (shift_bits) ? keypair[index][SHIFTED] : keypair[index][RAW];
      unregister_mods(shift_bits);
      register_code16(stash_code);
    }
    else {
      origin_code = _______;
      unregister_code16(stash_code);
      register_mods(stash_shift);
    }
    return false;
  }

  return true;
}
