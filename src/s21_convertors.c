#include "s21_decimal.h"
#include "s21_support.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = convertation_error;
  if (src < 0) {
    set_sign(dst, 1);
    src = src * -1;
  }
  dst->bits[0] = src;
  flag = OK;
  return flag;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = convertation_error;
  if (dst == NULL) {
    return convertation_error;
  }
  if (get_pow(src) > 0) {
    s21_decimal result = {{0}};
    s21_truncate(src, &result);
    src = result;
  }
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    if (src.bits[0] > MAX_INT) {
      flag = convertation_error;
    } else if (get_sign(src) == 0) {
      *dst = src.bits[0];
      flag = OK;
    } else if (get_sign(src) == 1) {
      *dst = -src.bits[0];
      flag = OK;
    }
  }
  return flag;
}

int s21_from_decimal_to_float(s21_decimal value, float *result) {
  int flag = OK;
  int decimal_pow = 0;  // степень decimal
  double double_result = +0;  // накапливаем результат вычисления decimal
  if (result == NULL) {
    flag = convertation_error;
  } else {
    for (int i = 0; i < 32; i++) {
      if (get_bit(value, i) == 1) {
        double_result += pow(2, i);
      }
    }
    for (int i = 32; i < 96; i++) {
      if (get_bit(value, i) == 1) {
        flag = convertation_error;
      }
    }
    decimal_pow = get_pow(value);
    while (decimal_pow > 0) {
      double_result /= 10;
      decimal_pow--;
    }
    if (get_sign(value) == 1) {
      double_result *= -1;
    }

    *result = (float)double_result;
  }
  return flag;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = OK;
  int pow_decimal = 0;
  double temp = (double)src;
  if ((dst == NULL) || (temp > 7.922816251e+29) || (temp < -7.922816251e+29)) {
    flag = convertation_error;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;  // занулим на всякий случай
    // установим знак
    if (temp < 0) {
      set_sign(dst, 1);
      temp *= -1;
    }
    if (temp == (int)temp) {
    } else {
      for (int i = 0; i < 7; i++) {
        pow_decimal++;
        temp *= 10;
        if (temp == (int)temp) {
          break;
        }
      }
    }
    dst->bits[0] = (int)temp;
    set_pow(dst, pow_decimal);
  }
  return flag;
}