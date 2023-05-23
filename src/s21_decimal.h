#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <math.h>
#include <stdio.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// typedef struct {
//   unsigned long int bits[7];
// } s21_long_decimal;

#define S21_INF 1 / 0.0
#define MAX_INT 2147483647
#define MIN_INT 2147483648U
#define MAX_LONG_INT 4294967295

// bits[0], bits[1], и bits[2] содержат младшие, средние и старшие 32 бита
// 96-разрядного целого числа соответственно.
// bits[3] содержит коэффициент масштабирования и знак, и состоит из следующих
//частей:

//Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
//Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
//указывает степень 10 для разделения целого числа.
//Биты с 24 по 30 не используются и должны быть равны нулю.
//Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.

//  0[00000000 00000000 00000000 00000000]
//  1[00000000 00000000 00000000 00000000]
//  2[00000000 00000000 00000000 00000000]
//  3[00000000      00000000        00000000 00000000]
//    |             |       |
//знак(0||1)        степень(n) (10^-n)

enum arithmetic_errors { arth_OK, arth_INF, arth_NEG_INF, arth_NAN };
enum comparison { FALSE, TRUE };
enum convertors { OK, convertation_error };

// arithmetic_functions
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// Convertors
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Other
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // S21_DECIMAL_H
