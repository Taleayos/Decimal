#ifndef S21_COMPARE_C
#define S21_COMPARE_C

#include "s21_decimal.h"
#include "s21_support.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = TRUE;
  for (int i = 0; i <= 3; i++) {
    if (value_1.bits[i] != value_2.bits[i]) {
      flag = FALSE;
    }
  }
  if (is_zero(value_1) && is_zero(value_2)) flag = TRUE;
  return flag;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int sign_v1 = get_sign(value_1);
  int sign_v2 = get_sign(value_2);
  if (sign_v1 != sign_v2) {
    if (sign_v1 == 0) {
      flag = 1;
    } else {
      flag = 0;
    }
  }
  if (sign_v1 == sign_v2) {
    normalize(&value_1, &value_2);
    flag = mantissa_is_greater(value_1, value_2);
    if (sign_v1 == 1 && flag == 1) {
      flag = FALSE;
    } else if (sign_v1 == 1 && flag == 0) {
      flag = TRUE;
    }
  }
  if (is_zero(value_1) && is_zero(value_2)) flag = FALSE;
  return flag;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_2, value_1);
}
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

#endif  // S21_COMPARE_C