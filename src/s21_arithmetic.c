#include "s21_decimal.h"
#include "s21_support.h"

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  longdec v1, v2, v3;
  dec_to_longdec(value1, &v1);
  dec_to_longdec(value2, &v2);
  normalize_long(&v1, &v2);
  add(v1, v2, &v3);
  longdec_to_dec(v3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return res;
}

int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  longdec v1, v2, v3;
  dec_to_longdec(value1, &v1);
  dec_to_longdec(value2, &v2);
  normalize_long(&v1, &v2);
  sub(v1, v2, &v3);
  longdec_to_dec(v3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return res;
}

int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  longdec v1, v2, v3;
  dec_to_longdec(value1, &v1);
  dec_to_longdec(value2, &v2);
  mul(v1, v2, &v3);
  longdec_to_dec(v3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return res;
}

int s21_div(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  longdec v1, v2, v3;
  dec_to_longdec(value1, &v1);
  dec_to_longdec(value2, &v2);
  div_dec(v1, v2, &v3);
  longdec_to_dec(v3, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return (mantissa_is_zero(v2) ? 3 : res);
}

int s21_mod(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  longdec v1, v2, v3;
  dec_to_longdec(value1, &v1);
  dec_to_longdec(value2, &v2);
  normalize_long(&v1, &v2);
  mod(v1, v2, &v3);
  longdec_to_dec(v3, result);
  if (get_bit(*result, 96))
    init_dec(get_sign(*result), get_pow(*result), 0, 0, 0, result);
  int res = get_bit(*result, 96) * (get_sign(*result) + 1);
  return (mantissa_is_zero(v2) ? 3 : res);
}
