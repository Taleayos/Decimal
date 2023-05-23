#ifndef S21_SUPPORT_H
#define S21_SUPPORT_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_decimal.h"

#define MAX_POS 96
#define MAX_POW 28

typedef struct {
  unsigned bits[7];  // 0-5 - мантисса числа, 6 - знак числа
  int pow;           // степень числа
} longdec;

int get_bit(s21_decimal value, int position);
int get_pow(s21_decimal value);
int get_sign(s21_decimal value);
void set_bit(s21_decimal *value, int position, int digit);
void set_pow(s21_decimal *value, int pow);
void set_sign(s21_decimal *value, int sign);

int get_bit_long(longdec value, int position);
int get_pow_long(longdec value);
int get_sign_long(longdec value);
void set_bit_long(longdec *value, int position, int digit);
void set_pow_long(longdec *value, int pow);
void set_sign_long(longdec *value, int sign);

int add_bits(int bit_1, int bit_2, int *temp);
int sub_bits(int bit_1, int bit_2, int *temp);

// сравнение мантисс чисел типа longdec
int mantissa_is_zero(longdec value);
int mantissa_is_equal(longdec value1, longdec value2);
int mantissa_is_not_equal(longdec value1, longdec value2);
int mantissa_is_greater_long(longdec value1, longdec value2);
int mantissa_is_greater_or_equal(longdec value1, longdec value2);
int mantissa_is_less(longdec value1, longdec value2);
int mantissa_is_less_or_equal(longdec value1, longdec value2);

// арифметические операции с longdec
void add(longdec v1, longdec v2, longdec *result);
void sub(longdec v1, longdec v2, longdec *result);
void mul(longdec v1, longdec v2, longdec *result);
void mod(longdec v1, longdec v2, longdec *result);
void div_dec(longdec v1, longdec v2, longdec *result);
void div_int(longdec v1, longdec v2, longdec *result);

void init_dec(int sign, int pow, unsigned b2, unsigned b1, unsigned b0,
              s21_decimal *value);
void init_dec2(int sign, int pow, unsigned b2, unsigned long long b1b0,
               s21_decimal *value);
// вывод числа и математической операции в десятичном формате
void print_dec(s21_decimal value);
void print_longdec(longdec value);
void print_math(char operation, s21_decimal v1, s21_decimal v2);

// конвертация чисел между типами s21_decimal и longdec
void dec_to_longdec(s21_decimal value, longdec *result);
void longdec_to_dec(longdec value, s21_decimal *result);

// разное
void mantissa_shift_left_long(longdec value, longdec *result);
void normalize_long(longdec *value_1, longdec *value_2);
void copy_dec(longdec value, longdec *result);
void copy_dec21(s21_decimal *value_1, s21_decimal value_2);
void add_pow(longdec value, longdec *result);
void sub_pow(longdec value, longdec *result);
void round_dec(longdec value, longdec *result);
void round_bank(longdec value, longdec *result);

unsigned long long mantissa_to_ull(s21_decimal d);

int mantissa_is_greater(s21_decimal value_1, s21_decimal value_2);
int mantissa_shift_left(s21_decimal *value);
int normalize(s21_decimal *value_1, s21_decimal *value_2);
int change_pow(s21_decimal value, int n, s21_decimal *result);
int div_int21(s21_decimal v1, s21_decimal v2, s21_decimal *result);
void round_bank(longdec value, longdec *result);
int get_digit(longdec value);

int is_zero(s21_decimal value);
int is_too_large(s21_decimal value);
int is_too_small(s21_decimal value);
int check_dec(s21_decimal value);
int simple_fmod(s21_decimal v1, s21_decimal v2);
int simple_div(s21_decimal v1, s21_decimal v2, s21_decimal *result);

#endif  // S21_SUPPORT_H
