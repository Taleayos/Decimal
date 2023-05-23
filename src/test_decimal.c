#include "test_decimal.h"

START_TEST(add_sub_equal) {
  for (int i = 0; i < 50; i++) {
    srand(time(NULL));
    s21_decimal a1, b1;
    init_dec(rand() % 1, 0, rand() % MAX_INT, rand() % MAX_INT,
             rand() % MAX_INT, &a1);
    init_dec(rand() % 1, 0, rand() % MAX_INT, rand() % MAX_INT,
             rand() % MAX_INT, &b1);
    s21_decimal s, a2, b2;
    int c1, c2, c3;
    c1 = s21_add(a1, b1, &s);
    c2 = s21_sub(s, b1, &a2);
    c3 = s21_sub(s, a1, &b2);

    ck_assert_int_eq(c1, 0);
    ck_assert_int_eq(c2, 0);
    ck_assert_int_eq(c3, 0);
  }
}

END_TEST

START_TEST(add_sub_diff_sign) {
  for (int i = 0; i < 50; i++) {
    srand(time(NULL));
    s21_decimal a1, b1;
    init_dec(0, rand() % 2, rand() % MAX_INT, rand() % MAX_INT,
             rand() % MAX_INT, &a1);
    init_dec(1, rand() % 2, rand() % MAX_INT, rand() % MAX_INT,
             rand() % MAX_INT, &b1);
    s21_decimal s, a2, b2;
    int c1, c2, c3;
    c1 = s21_add(a1, b1, &s);
    c2 = s21_sub(s, b1, &a2);
    c3 = s21_sub(s, a1, &b2);

    ck_assert_int_eq(c1, 0);
    ck_assert_int_eq(c2, 0);
    ck_assert_int_eq(c3, 0);
  }
}
END_TEST

// DIV_MUL
START_TEST(div_mul_equal) {
  for (int i = 0; i < 50; i++) {
    srand(time(NULL));
    s21_decimal a1, b1;
    init_dec(rand() % 1, 0, rand() % MAX_INT, rand() % MAX_INT,
             rand() % MAX_INT, &a1);
    init_dec(rand() % 1, 0, rand() % MAX_INT, rand() % MAX_INT,
             rand() % MAX_INT, &b1);
    s21_decimal s, a2, b2;
    int c1, c2, c3;
    c1 = s21_div(a1, b1, &s);
    c2 = s21_mul(s, b1, &a2);
    c3 = s21_mul(s, a1, &b2);

    ck_assert_int_eq(c1, 0);
    ck_assert_int_eq(c2, 0);
    ck_assert_int_eq(c3, 0);
  }
}
END_TEST

START_TEST(add_inf_positiv) {
  s21_decimal a, b, res;
  int c = 0;
  init_dec(0, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 0, 0, 0, 5, &b);
  c = s21_add(a, b, &res);
  ck_assert_int_eq(c, 1);
}
END_TEST

START_TEST(add_inf_negative) {
  s21_decimal a, b, res;
  int c = 0;
  init_dec(1, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(1, 0, 0, 0, 5, &b);
  c = s21_add(a, b, &res);
  ck_assert_int_eq(c, 2);
}
END_TEST

START_TEST(mul_div_equal) {
  for (int i = 0; i < 50; i++) {
    srand(time(NULL));
    s21_decimal a1, b1;
    init_dec(rand() % 1, 0, 0, rand() % 2023, rand() % 2023, &a1);
    init_dec(rand() % 1, 0, 0, rand() % 2023, rand() % 2023, &b1);
    s21_decimal s, a2, b2;
    int c1, c2, c3;
    c1 = s21_mul(a1, b1, &s);
    c2 = s21_div(s, b1, &a2);
    c3 = s21_div(s, a1, &b2);

    ck_assert_int_eq(c1, 0);
    ck_assert_int_eq(c2, 0);
    ck_assert_int_eq(c3, 0);
  }
}
END_TEST

START_TEST(div_not_int) {
  s21_decimal a, b, res;
  init_dec(0, 0, 0, 0, 36, &a);
  init_dec(0, 0, 0, 0, 5, &b);
  s21_div(a, b, &res);
  ck_assert_int_eq(res.bits[0], 72);
}
END_TEST

START_TEST(div_for_zero) {
  s21_decimal a, b, res;
  int c = 0;
  init_dec(0, 0, 0, 0, 36, &a);
  init_dec(0, 0, 0, 0, 0, &b);
  c = s21_div(a, b, &res);
  ck_assert_int_eq(c, 3);
}
END_TEST

START_TEST(mul_inf_pozitive) {
  s21_decimal a, b, res;
  int c = 0;
  init_dec(0, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 0, 0, 0, 21, &b);
  c = s21_mul(a, b, &res);
  ck_assert_int_eq(c, 1);
}
END_TEST

START_TEST(mul_inf_negative) {
  s21_decimal a, b, res;
  int c = 0;
  init_dec(1, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 0, 0, 0, 21, &b);
  c = s21_mul(a, b, &res);
  ck_assert_int_eq(c, 2);
}
END_TEST

START_TEST(is_less_1) {
  s21_decimal left = {{0}};
  s21_decimal right = {{0}};
  ck_assert_int_eq(0, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_2) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2024, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_3) {
  s21_decimal left = {{2024, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_5) {
  s21_decimal left = {{2023, 12, 0, 0}};
  s21_decimal right = {{2023, 12, 5, 0}};
  ck_assert_int_eq(1, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal left = {{5, 0, 0, 2147483648}};  // отрицательная степень
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_7_1) {
  s21_decimal left = {{5, 0, 0, 2147483648}};
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(right, left));
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(1, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(0, s21_is_less(right, left));
}
END_TEST

START_TEST(is_less_9) {
  s21_decimal left = {{555555, 0, 0, 2147483648}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 3);
  ck_assert_int_eq(1, s21_is_less(left, right));
}
END_TEST

START_TEST(is_less_or_equal_1) {
  s21_decimal left = {{0}};
  s21_decimal right = {{0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_2) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2024, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_3) {
  s21_decimal left = {{2024, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_4) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_5) {
  s21_decimal left = {{2023, 12, 0, 0}};
  s21_decimal right = {{2023, 12, 5, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_6) {
  s21_decimal left = {{5, 0, 0, 2147483648}};  // отрицательная степень
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal left = {{5, 0, 0, 2147483648}};
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less_or_equal(right, left));
}
END_TEST

START_TEST(is_less_or_equal_7_1) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(0, s21_is_less_or_equal(right, left));
}
END_TEST

START_TEST(is_less_or_equal_9) {
  s21_decimal left = {{555555, 0, 0, 2147483648}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 3);
  ck_assert_int_eq(1, s21_is_less_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_1) {
  s21_decimal left = {{0}};
  s21_decimal right = {{0}};
  ck_assert_int_eq(0, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_2) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2024, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_3) {
  s21_decimal left = {{2024, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_4) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal left = {{2023, 12, 5, 0}};
  s21_decimal right = {{2023, 12, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_6) {
  s21_decimal left = {{5, 0, 0, 0}};
  s21_decimal right = {{5, 0, 0, 2147483648}};  // отрицательная степень
  ck_assert_int_eq(1, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_6_1) {
  s21_decimal left = {{5, 0, 0, 2147483648}};
  s21_decimal right = {{20, 0, 0, 2147483648}};  // отрицательная степень
  ck_assert_int_eq(1, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_7) {
  s21_decimal left = {{5, 0, 0, 2147483648}};
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_7_1) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(0, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(1, s21_is_greater(right, left));
}
END_TEST

START_TEST(is_greater_9) {
  s21_decimal left = {{555555, 0, 0, 2147483648}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 3);
  ck_assert_int_eq(0, s21_is_greater(left, right));
}
END_TEST

START_TEST(is_greater_10) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 2023;
  value_2.bits[0] = 20;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

START_TEST(is_greater_or_equal_1) {
  s21_decimal left = {{0}};
  s21_decimal right = {{0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2024, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  s21_decimal left = {{2024, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  s21_decimal left = {{2023, 0, 0, 0}};
  s21_decimal right = {{2023, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal left = {{2023, 12, 5, 0}};
  s21_decimal right = {{2023, 12, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal left = {{5, 0, 0, 0}};
  s21_decimal right = {{5, 0, 0, 2147483648}};  // отрицательная степень
  ck_assert_int_eq(1, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal left = {{5, 0, 0, 2147483648}};
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_7_1) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(0, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_greater_or_equal_8) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(right, left));
}
END_TEST

START_TEST(is_greater_or_equal_9) {
  s21_decimal left = {{555555, 0, 0, 2147483648}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 3);
  ck_assert_int_eq(0, s21_is_greater_or_equal(left, right));
}
END_TEST

START_TEST(is_equal_1) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  set_sign(&right, 1);
  ck_assert_int_eq(1, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_2) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_3) {
  s21_decimal left = {{5, 0, 0, 2147483648}};  // отрицательная степень
  s21_decimal right = {{5, 0, 0, 2147483648}};  // отрицательная степень
  ck_assert_int_eq(1, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_4) {
  s21_decimal left = {{5, 0, 0, 2147483648}};  // отрицательная степень
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_5) {
  s21_decimal left = {{5789, 7998987, 789658, 0}};
  s21_decimal right = {{5789, 7998987, 789658, 0}};
  ck_assert_int_eq(1, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_6) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 3);
  ck_assert_int_eq(1, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_6_1) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(0, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_equal_7) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_1) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  set_sign(&right, 1);
  ck_assert_int_eq(0, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_2) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_3) {
  s21_decimal left = {{5, 0, 0, 2147483648}};  // отрицательная степень
  s21_decimal right = {{5, 0, 0, 2147483648}};  // отрицательная степень
  ck_assert_int_eq(0, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_4) {
  s21_decimal left = {{5, 0, 0, 2147483648}};  // отрицательная степень
  s21_decimal right = {{5, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal left = {{5789, 7998987, 789658, 0}};
  s21_decimal right = {{5789, 7998987, 789658, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 3);
  ck_assert_int_eq(0, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_6_1) {
  s21_decimal left = {{555555, 0, 0, 0}};
  s21_decimal right = {{555555, 0, 0, 0}};
  set_pow(&left, 3);
  set_pow(&right, 2);
  ck_assert_int_eq(1, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(is_not_equal_7) {
  s21_decimal left = {{0, 0, 0, 0}};
  s21_decimal right = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(left, right));
}
END_TEST

START_TEST(negate_1) {
  s21_decimal value = {{2023, 0, 0, 0}};
  s21_decimal res = {{0}};
  int sign_value = get_sign(value);
  s21_negate(value, &res);
  int sign_res = get_sign(res);
  ck_assert_int_ne(sign_value, sign_res);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal value = {{2023, 0, 0, 2147483648}};
  s21_decimal res = {{0}};
  int sign_value = get_sign(value);
  s21_negate(value, &res);
  int sign_res = get_sign(res);
  ck_assert_int_ne(sign_value, sign_res);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal value = {{0}};
  s21_decimal res = {{0}};
  int sign_value = get_sign(value);
  s21_negate(value, &res);
  int sign_res = get_sign(res);
  ck_assert_int_ne(sign_value, sign_res);
}
END_TEST

// FLOOR_TEST_START

START_TEST(floor_1_pozitive) {
  s21_decimal a, result, test;
  init_dec(0, 2, 0, 0, 123, &a);
  init_dec(0, 0, 0, 0, 1, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(floor_2_pozitive) {
  s21_decimal a, result, test;
  init_dec(0, 13, MAX_INT, MAX_INT, MAX_INT, &a);
  init_dec(0, 0, 0, 922337, 873900127, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(floor_3_pozitive) {
  s21_decimal a, result, test;
  init_dec(0, 6, 0, 0, 123, &a);
  init_dec(0, 0, 0, 0, 0, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(floor_1_negative) {
  s21_decimal a, result, test;
  init_dec(1, 13, MAX_INT, MAX_INT, MAX_INT, &a);
  init_dec(1, 0, 0, 922337, 873900128, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(floor_2_negative) {
  s21_decimal a, result, test;
  init_dec(1, 2, 0, 0, 123, &a);
  init_dec(1, 0, 0, 0, 2, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(floor_3_negative) {
  s21_decimal a, result, test;
  init_dec(1, 10, 123, 123, 123, &a);
  init_dec(1, 0, 0, 52, 3556652768, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(floor_no_pow) {
  s21_decimal a, result, test;
  init_dec(1, 0, 123, 123, 123, &a);
  init_dec(1, 0, 123, 123, 123, &test);
  int res = s21_floor(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

// FLOOR_TEST_END

// ROUND_TEST_START

START_TEST(round_1_to_small) {
  s21_decimal a, result, test;
  init_dec(0, 4, 0, 0, MAX_INT, &a);
  init_dec(0, 0, 0, 0, 214748, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(round_2_to_small) {
  s21_decimal a, result, test;
  init_dec(0, 4, 3, 123456, 9991299, &a);
  init_dec(0, 0, 0, 1288502, 2295231522, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(round_3) {
  s21_decimal a, result, test;
  init_dec(0, 4, 1, 1, 9991299, &a);
  init_dec(0, 0, 0, 429496, 3134038635, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(round_4_to_great) {
  s21_decimal a, result, test;
  init_dec(0, 8, 0, 0, 355555555, &a);
  init_dec(0, 0, 0, 0, 4, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(round_5_to_great) {
  s21_decimal a, result, test;
  init_dec(1, 2, 0, 0, 355555555, &a);
  init_dec(1, 0, 0, 0, 3555556, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(round_6_to_great) {
  s21_decimal a, result, test;
  init_dec(1, 28, 0, 12345, 355555555, &a);
  init_dec(1, 0, 0, 0, 0, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(round_no_pow) {
  s21_decimal a, result, test;
  init_dec(1, 0, 385, 12345, 355555555, &a);
  init_dec(1, 0, 385, 12345, 355555555, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(round_zero) {
  s21_decimal a, result, test;
  init_dec(0, 0, 0, 0, 0, &a);
  init_dec(0, 0, 0, 0, 0, &test);
  int res = s21_round(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

// ROUND_TEST_END

// TRUNCATE_TEST_START

START_TEST(truncate_positive) {
  s21_decimal a, result, test;
  for (int i = 0; i < 28; i++) {
    init_dec(0, i, 0, 0, MAX_INT, &a);
    init_dec(0, 0, 0, 0, (MAX_INT / (pow(10, i))), &test);
    int res = s21_truncate(a, &result);
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(s21_is_equal(result, test), 1);
    ck_assert_int_eq(get_sign(result), 0);
  }
}
END_TEST

START_TEST(truncate_negative) {
  s21_decimal a, result, test;
  for (int i = 1; i < 10; i++) {
    init_dec(1, i, 0, 0, MAX_INT, &a);
    init_dec(1, 0, 0, 0, (MAX_INT / (pow(10, i))), &test);
    int res = s21_truncate(a, &result);
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(s21_is_equal(result, test), 1);
    ck_assert_int_eq(get_sign(result), 1);
  }
}
END_TEST

START_TEST(truncate_no_pow) {
  s21_decimal a, result, test;
  init_dec(0, 0, 123, 123, 123, &a);
  init_dec(0, 0, 123, 123, 123, &test);
  int res = s21_truncate(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(truncate_long) {
  s21_decimal a, result, test;
  init_dec(1, 12, 100, 100, 100, &a);
  init_dec(1, 0, 0, 0, 1844674407, &test);
  int res = s21_truncate(a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(from_int_to_decimal_1) {
  s21_decimal value = {{0}};
  s21_decimal test = {{0}};
  int new = 0;
  s21_from_int_to_decimal(new, &value);
  ck_assert_int_eq(value.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(value), 0);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal value = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 555555555;
  s21_from_int_to_decimal(tmp, &value);
  s21_from_decimal_to_int(value, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal value = {{0}};
  s21_decimal test = {{2023, 0, 0, 0}};
  int new = 2023;
  s21_from_int_to_decimal(new, &value);
  ck_assert_int_eq(value.bits[0], test.bits[0]);
}
END_TEST

START_TEST(from_int_to_decimal_4) {
  s21_decimal value = {{0}};
  s21_decimal test = {{2023, 0, 0, 2147483648}};
  int new = -2023;
  s21_from_int_to_decimal(new, &value);
  ck_assert_int_eq(value.bits[0], test.bits[0]);
  ck_assert_int_eq(value.bits[3], test.bits[3]);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal value = {{0}};
  int new = 0;
  value.bits[0] = 2023;
  int result = s21_from_decimal_to_int(value, &new);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal value = {{0}};
  value.bits[0] = 2147483648;
  int new = 0;
  set_sign(&value, 1);
  int result = s21_from_decimal_to_int(value, &new);
  ck_assert_int_eq(result, convertation_error);
}
END_TEST

START_TEST(from_decimal_to_int_3) {
  s21_decimal value_1 = {0};
  int a = 0;
  value_1.bits[0] = 2023;
  set_pow(&value_1, 20);
  s21_from_decimal_to_int(value_1, &a);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal value = {{0}};
  int new = 0;
  value.bits[0] = 2023;
  set_sign(&value, 1);
  int result = s21_from_decimal_to_int(value, &new);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 2147483648;
  int new = 0;
  set_sign(&value_1, 1);
  int res = s21_from_decimal_to_int(value_1, &new);
  ck_assert_int_eq(res, convertation_error);
}
END_TEST

START_TEST(from_decimal_to_int_6) {
  s21_decimal value_2 = {0};
  int *new = NULL;
  int res = s21_from_decimal_to_int(value_2, new);
  ck_assert_int_eq(res, convertation_error);
}
END_TEST

START_TEST(mod_1) {
  s21_decimal a, b, result, test;
  init_dec(0, 0, 123, 123, 123, &a);
  init_dec(0, 0, 123, 123, 123, &b);
  init_dec(0, 0, 0, 0, 0, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(mod_2) {
  s21_decimal a, b, result, test;
  init_dec(1, 9, 0, 0, 1, &a);
  init_dec(0, 0, 0, 0, 10, &b);
  init_dec(1, 9, 0, 0, 1, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(mod_3_zero) {
  s21_decimal a, b, result, test;
  init_dec(0, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 8, 0, 0, 1, &b);
  init_dec(0, 0, 0, 0, 0, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 3);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(mod_4_div_zero) {
  s21_decimal a, b, result, test;
  init_dec(0, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 0, 0, 0, 0, &b);
  init_dec(0, 0, 0, 0, 0, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(mod_5) {
  s21_decimal a, b, result, test;
  init_dec(0, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 0, 0, 0, 2, &b);
  init_dec(0, 0, 0, 0, 1, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(mod_6_pow) {
  s21_decimal a, b, result, test;
  init_dec(0, 0, 0, 0, MAX_LONG_INT, &a);
  init_dec(0, 4, 0, 0, 523467, &b);
  init_dec(0, 4, 0, 0, 222906, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(mod_7_pow_sign) {
  s21_decimal a, b, result, test;
  init_dec(1, 0, MAX_LONG_INT, MAX_LONG_INT, MAX_LONG_INT, &a);
  init_dec(0, 1, 0, 0, 523467, &b);
  init_dec(1, 1, 0, 0, 343215, &test);
  int res = s21_mod(a, b, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(s21_is_equal(result, test), 1);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal value = {{0}};
  float new = 0;
  value.bits[0] = 4294967295;
  int result = s21_from_decimal_to_float(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal value = {{0}};
  value.bits[1] = 1;
  float new = 0;
  set_sign(&value, 1);
  int result = s21_from_decimal_to_float(value, &new);
  ck_assert_float_eq(result, convertation_error);
}
END_TEST

START_TEST(from_decimal_to_float_3) {
  s21_decimal value_1 = {0};
  float new = 0;
  value_1.bits[0] = 0;
  set_pow(&value_1, 28);
  s21_from_decimal_to_float(value_1, &new);
  ck_assert_float_eq(new, 0);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  s21_decimal value = {{0}};
  float new = 0;
  value.bits[0] = 1;
  set_sign(&value, 1);
  int result = s21_from_decimal_to_float(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_5) {
  s21_decimal value = {{0}};
  float new = 0;
  value.bits[0] = 1;
  set_sign(&value, 0);
  int result = s21_from_decimal_to_float(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  s21_decimal new = {{0}};
  float value = 1;
  int result = s21_from_float_to_decimal(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal new = {{0}};
  float value = 1;
  int result = s21_from_float_to_decimal(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal new = {{0}};
  float value = -1;
  int result = s21_from_float_to_decimal(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  s21_decimal new = {{0}};
  float value = 7.922816252e+29;
  int result = s21_from_float_to_decimal(value, &new);
  ck_assert_float_eq(result, 1);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  s21_decimal new = {{0}};
  float value = 2.3;
  int result = s21_from_float_to_decimal(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  s21_decimal new = {{0}};
  float value = 2.000000003;
  int result = s21_from_float_to_decimal(value, &new);
  ck_assert_float_eq(result, 0);
}
END_TEST

START_TEST(from_decimal_to_float_7) {
  s21_decimal value = {0};
  float *a = NULL;
  int res = s21_from_decimal_to_float(value, a);
  ck_assert_uint_eq(res, convertation_error);
}
END_TEST

Suite *test_decimal(void) {
  Suite *s = suite_create("s21_decimal");
  TCase *tc = tcase_create("case_decimal");

  tcase_add_test(tc, add_sub_diff_sign);
  tcase_add_test(tc, add_inf_positiv);
  tcase_add_test(tc, add_inf_negative);
  tcase_add_test(tc, div_not_int);
  tcase_add_test(tc, div_for_zero);
  tcase_add_test(tc, mul_inf_pozitive);
  tcase_add_test(tc, mul_inf_negative);
  tcase_add_test(tc, is_less_1);
  tcase_add_test(tc, is_less_2);
  tcase_add_test(tc, is_less_3);
  tcase_add_test(tc, is_less_4);
  tcase_add_test(tc, is_less_5);
  tcase_add_test(tc, is_less_6);
  tcase_add_test(tc, is_less_7);
  tcase_add_test(tc, is_less_7_1);
  tcase_add_test(tc, is_less_8);
  tcase_add_test(tc, is_less_9);
  tcase_add_test(tc, is_less_or_equal_1);
  tcase_add_test(tc, is_less_or_equal_2);
  tcase_add_test(tc, is_less_or_equal_3);
  tcase_add_test(tc, is_less_or_equal_4);
  tcase_add_test(tc, is_less_or_equal_5);
  tcase_add_test(tc, is_less_or_equal_6);
  tcase_add_test(tc, is_less_or_equal_7);
  tcase_add_test(tc, is_less_or_equal_7_1);
  tcase_add_test(tc, is_less_or_equal_8);
  tcase_add_test(tc, is_less_or_equal_9);
  tcase_add_test(tc, is_greater_1);
  tcase_add_test(tc, is_greater_2);
  tcase_add_test(tc, is_greater_3);
  tcase_add_test(tc, is_greater_4);
  tcase_add_test(tc, is_greater_5);
  tcase_add_test(tc, is_greater_6);
  tcase_add_test(tc, is_greater_6_1);
  tcase_add_test(tc, is_greater_7);
  tcase_add_test(tc, is_greater_7_1);
  tcase_add_test(tc, is_greater_8);
  tcase_add_test(tc, is_greater_9);
  tcase_add_test(tc, is_greater_10);
  tcase_add_test(tc, is_greater_or_equal_1);
  tcase_add_test(tc, is_greater_or_equal_2);
  tcase_add_test(tc, is_greater_or_equal_3);
  tcase_add_test(tc, is_greater_or_equal_4);
  tcase_add_test(tc, is_greater_or_equal_5);
  tcase_add_test(tc, is_greater_or_equal_6);
  tcase_add_test(tc, is_greater_or_equal_7);
  tcase_add_test(tc, is_greater_or_equal_7_1);
  tcase_add_test(tc, is_greater_or_equal_8);
  tcase_add_test(tc, is_greater_or_equal_9);
  tcase_add_test(tc, is_equal_1);
  tcase_add_test(tc, is_equal_2);
  tcase_add_test(tc, is_equal_3);
  tcase_add_test(tc, is_equal_4);
  tcase_add_test(tc, is_equal_5);
  tcase_add_test(tc, is_equal_6);
  tcase_add_test(tc, is_equal_7);
  tcase_add_test(tc, is_equal_6_1);
  tcase_add_test(tc, is_not_equal_1);
  tcase_add_test(tc, is_not_equal_2);
  tcase_add_test(tc, is_not_equal_3);
  tcase_add_test(tc, is_not_equal_4);
  tcase_add_test(tc, is_not_equal_5);
  tcase_add_test(tc, is_not_equal_6);
  tcase_add_test(tc, is_not_equal_6_1);
  tcase_add_test(tc, is_not_equal_7);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, floor_1_pozitive);
  tcase_add_test(tc, floor_2_pozitive);
  tcase_add_test(tc, floor_3_pozitive);
  tcase_add_test(tc, floor_1_negative);
  tcase_add_test(tc, floor_2_negative);
  tcase_add_test(tc, floor_3_negative);
  tcase_add_test(tc, floor_no_pow);
  tcase_add_test(tc, round_1_to_small);
  tcase_add_test(tc, round_2_to_small);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4_to_great);
  tcase_add_test(tc, round_5_to_great);
  tcase_add_test(tc, round_6_to_great);
  tcase_add_test(tc, round_no_pow);
  tcase_add_test(tc, round_zero);
  tcase_add_test(tc, truncate_positive);
  tcase_add_test(tc, truncate_negative);
  tcase_add_test(tc, truncate_no_pow);
  tcase_add_test(tc, truncate_long);
  tcase_add_test(tc, from_int_to_decimal_1);
  tcase_add_test(tc, from_int_to_decimal_2);
  tcase_add_test(tc, from_int_to_decimal_3);
  tcase_add_test(tc, from_int_to_decimal_4);
  tcase_add_test(tc, from_decimal_to_int_1);
  tcase_add_test(tc, from_decimal_to_int_2);
  tcase_add_test(tc, from_decimal_to_int_3);
  tcase_add_test(tc, from_decimal_to_int_4);
  tcase_add_test(tc, from_decimal_to_int_5);
  tcase_add_test(tc, from_decimal_to_int_6);
  tcase_add_test(tc, mod_1);
  tcase_add_test(tc, mod_2);
  tcase_add_test(tc, mod_3_zero);
  tcase_add_test(tc, mod_4_div_zero);
  tcase_add_test(tc, mod_5);
  tcase_add_test(tc, mod_6_pow);
  tcase_add_test(tc, mod_7_pow_sign);
  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, from_decimal_to_float_2);
  tcase_add_test(tc, from_decimal_to_float_3);
  tcase_add_test(tc, from_decimal_to_float_4);
  tcase_add_test(tc, from_decimal_to_float_5);
  tcase_add_test(tc, from_float_to_decimal_1);
  tcase_add_test(tc, from_float_to_decimal_2);
  tcase_add_test(tc, from_float_to_decimal_3);
  tcase_add_test(tc, from_float_to_decimal_4);
  tcase_add_test(tc, from_float_to_decimal_5);
  tcase_add_test(tc, from_float_to_decimal_6);
  tcase_add_test(tc, div_mul_equal);
  tcase_add_test(tc, mul_div_equal);
  tcase_add_test(tc, add_sub_equal);
  tcase_add_test(tc, from_decimal_to_float_7);

  suite_add_tcase(s, tc);
  return s;
}
