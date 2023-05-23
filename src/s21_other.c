#include "s21_decimal.h"
#include "s21_support.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  int mod = 0;
  int power = get_pow(value);
  int sign = get_sign(value);
  init_dec(sign, 0, 0, 0, 0, result);
  if (power > 28) return 1;
  if (power > 0) {
    s21_decimal mod_val = {{10, 0, 0, 0}};
    for (int i = 0; i < power; i++) {
      mod = simple_fmod(value, mod_val);
      simple_div(value, mod_val, &value);
    }
    *result = value;
    if (mod >= 5) {
      result->bits[0] += 1;
    }
  } else {
    *result = value;
  }
  set_pow(result, 0);
  set_sign(result, sign);
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int sign = get_sign(value);
  int power = get_pow(value);
  init_dec(sign, 0, 0, 0, 0, result);
  if (power > 28) return 1;
  if (power == 0) *result = value;
  s21_decimal div_value = {0};
  while (power != 0) {
    init_dec(0, 0, 0, 0, 10, &div_value);
    simple_div(value, div_value, result);
    value = *result;
    power--;
  }
  set_pow(result, 0);
  set_sign(result, sign);
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;
  int power = get_pow(value);
  if (power > 28) return 1;
  int sign = get_sign(value);
  s21_decimal div_value = {0};
  div_value.bits[0] = pow(10, power);
  int mod = simple_fmod(value, div_value);
  s21_truncate(value, result);
  if (sign && mod > 0) result->bits[0] += 1;
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 1;
  if (get_sign(value) == 0) {
    set_sign(&value, 1);
    *result = value;
    flag = 0;
  } else if (get_sign(value) == 1) {
    set_sign(&value, 0);
    *result = value;
    flag = 0;
  }
  return flag;
}
