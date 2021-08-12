#pragma once

bool custom_key_pair(uint16_t, keyrecord_t *);

enum custom_pair_keycodes {
  CP_2 = SAFE_RANGE,
  CP_6,
  CP_7,
  CP_8,
  CP_9,
  CP_0,
  CP_EQL,
  CP_MINS,
  CP_LBRC,
  CP_RBRC,
  CP_SCLN,
  CP_QUOT,
  CP_BSLS,
  CP_RO,
  CP_SAFE_RANGE
};
