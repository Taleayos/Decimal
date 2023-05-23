#include "s21_support.h"

#include <string.h>

int get_bit(s21_decimal value, int position) {
  return (value.bits[position / 32] >> (position % 32)) & 1U;
}

void set_bit(s21_decimal *value, int position, int digit) {
  int mask = 1U << (position % 32);
  if (digit == 1)
    value->bits[position / 32] |= mask;
  else
    value->bits[position / 32] &= ~mask;
}

//  Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
//  указывает степень 10 для разделения целого числа.
int get_pow(s21_decimal value) {
  /* twilawal (другой способ)
  int res = (value.bits[3] >> 16);  // сдвинуть в младшую часть
  res -= get_sign(value) * (1U << 16);  // убрать знак
*/
  int power = 0;
  int res = 0;
  for (int i = 7; i >= 0; i--) {
    int temp = get_bit(value, 96 + 16 + i);
    power = temp * pow(2, i);
    res += power;
  }
  return res;
}

void set_pow(s21_decimal *value, int pow) {
  if (pow >= 0 && pow <= MAX_POW) {
    int sign = get_sign(*value);
    value->bits[3] = pow << 16;
    set_sign(value, sign);
  }
}

int get_sign(s21_decimal value) { return get_bit(value, 127); }

void set_sign(s21_decimal *value, int sign) {
  /* twilawal (другой способ)
  value->bits[3] |= sign * (1U << 31);  // добавить знак
  */
  int mask = 1U << 31;
  if (sign == 1)
    value->bits[3] |= mask;
  else
    value->bits[3] &= ~mask;
}
int get_bit_long(longdec value, int position) {
  return (value.bits[position / 32] >> (position % 32)) & 1U;
}

void set_bit_long(longdec *value, int position, int digit) {
  int mask = 1U << (position % 32);
  if (digit == 1)
    value->bits[position / 32] |= mask;
  else
    value->bits[position / 32] &= ~mask;
}

int get_pow_long(longdec value) { return value.pow; }

void set_pow_long(longdec *value, int pow) { value->pow = pow; }

int get_sign_long(longdec value) { return get_bit_long(value, 192); }

void set_sign_long(longdec *value, int sign) { set_bit_long(value, 192, sign); }

// twilawal
/* правила сложения битов */
int add_bits(int bit_1, int bit_2, int *temp) {
  int bit_3;
  switch (bit_1 + bit_2 + *temp) {
    case 3:
      bit_3 = 1;
      *temp = 1;
      break;
    case 2:
      bit_3 = 0;
      *temp = 1;
      break;
    case 1:
      bit_3 = 1;
      *temp = 0;
      break;
    case 0:
      bit_3 = 0;
      *temp = 0;
      break;
  }
  return bit_3;
}

// twilawal
/* правила вычитания битов */
int sub_bits(int bit_1, int bit_2, int *temp) {
  if (*temp) bit_1 = !bit_1;
  if (*temp && !bit_1) *temp = 0;
  if (bit_1 - bit_2 < 0) *temp = 1;
  return abs(bit_1 - bit_2);
}

// twilawal
/* определение десятичной цифры в нулевом разряде числа с переполненной
мантиссой (для банк. округления) */
int get_digit(longdec value) {
  int digit;
  int sum = 0;
  for (int i = 0; i <= MAX_POS; i++) {
    if (i % 4 == 1) digit = 2;
    if (i % 4 == 2) digit = 4;
    if (i % 4 == 3) digit = 8;
    if (i % 4 == 0) digit = 6;
    if (i == 0) digit = 1;
    sum += get_bit_long(value, i) * digit;
  }
  return sum % 10;
}

// twilawal
/* инициализация числа тремя int-ами (отдельными значениями старшей, средней
 и младшей частей) (для отладки) */
void init_dec(int sign, int pow, unsigned b2, unsigned b1, unsigned b0,
              s21_decimal *value) {
  value->bits[3] = 0;
  value->bits[2] = b2;
  value->bits[1] = b1;
  value->bits[0] = b0;
  set_sign(value, sign);
  set_pow(value, pow);
}

// twilawal
/* инициализация числа одним int-ом и одним long-long-int-ом
(старшей и объедиенной средней и младшей частью) (для отладки) */
void init_dec2(int sign, int pow, unsigned b2, unsigned long long b1b0,
               s21_decimal *value) {
  value->bits[3] = 0;
  value->bits[2] = b2;
  value->bits[1] = (b1b0 >> 32);
  value->bits[0] = b1b0;
  set_sign(value, sign);
  set_pow(value, pow);
}

// twilawal
/* инициализация числа всеми int-ами другого числа */
void copy_dec(longdec value, longdec *result) {
  for (int i = 0; i < 7; i++) result->bits[i] = value.bits[i];
  result->pow = value.pow;
}

/* вывод числа (для отладки) */
void print_dec(s21_decimal value) {
  longdec v;
  dec_to_longdec(value, &v);
  // вывести десятичные цифры числа со знаком и степенью
  if (get_bit(value, 96))
    printf("%47s", (get_sign(value) ? "-INFINITY" : "+INFINITY"));
  else
    print_longdec(v);
  // вывести старшие, средние и младшие 32 бита
  for (int i = 2; i >= 0; i--) {
    printf(" ");  // вывести разделитель между 32-битными частями
    // вывести 32-битную часть побитово в двоичном виде
    for (int j = 31; j >= 0; j--) printf("%u", get_bit(value, i * 32 + j));
  }
  puts("");
}
void copy_dec21(s21_decimal *value_1, s21_decimal value_2) {
  for (int i = 0; i <= 3; i++) value_1->bits[i] = value_2.bits[i];
}

/* вывод числа longdec в виде строки десятичных цифр (для отладки) */
void print_longdec(longdec value) {
  char str[100] = {'\0'};
  longdec diff = {0}, ten = {{10, 0, 0, 0, 0, 0, 0}, 0};
  while (!mantissa_is_zero(value)) {
    mod(value, ten, &diff);  /// найти цифру числа
    // вставить разделитель между разрядами
    if (strlen(str) % 4 == 0) {
      for (int i = strlen(str); i > 0; i--) str[i] = str[i - 1];
      str[0] = ' ';
    }
    // добавить в строку десятичную цифру числа
    for (int i = strlen(str); i > 0; i--) str[i] = str[i - 1];
    str[0] = diff.bits[0] + 48;
    // вычислить делимое для следующей цифры
    div_int(value, ten, &value);
  }
  // добавить в строку знак числа
  if (strlen(str) == 0) strcat(str, "0 ");
  for (int i = strlen(str); i > 0; i--) str[i] = str[i - 1];
  str[0] = (get_sign_long(value) ? '-' : '+');
  // вывести мантиссу вместе со знаком и показателем степени
  printf("%43se-%02d", str, get_pow_long(value));
}

/* вывод математической операции с операндами и результатом (для отладки) */
void print_math(char operation, s21_decimal v1, s21_decimal v2) {
  s21_decimal v3;
  print_dec(v1);
  print_dec(v2);
  printf("<%c>", operation);
  for (int i = 1; i < 144; i++) printf("-");
  if (operation == '+') s21_add(v1, v2, &v3);
  if (operation == '-') s21_sub(v1, v2, &v3);
  if (operation == '*') s21_mul(v1, v2, &v3);
  if (operation == '/') s21_div(v1, v2, &v3);
  if (operation == '%') s21_mod(v1, v2, &v3);
  puts("");
  print_dec(v3);
}

// twilawal
// (для отладки)
unsigned long long mantissa_to_ull(s21_decimal d) {
  unsigned long long value = 1.0 / 0.0;  // INFINITY
  if (d.bits[2] == 0) {
    value = d.bits[1];
    value <<= 32;
    value += d.bits[0];
  }
  return value;
}

// twilawal
/* сравнение мантисс двух чисел на "больше" */
int mantissa_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  for (int i = MAX_POS; i >= 0; i--)
    if (get_bit(value_1, i) != get_bit(value_2, i)) {
      res = get_bit(value_1, i);
      break;
    }
  return res;
}

// twilawal
/* сдвиг мантиссы числа на один знак влево */
int mantissa_shift_left(s21_decimal *value) {
  s21_decimal temp;
  copy_dec21(&temp, *value);
  for (int i = MAX_POS; i > 0; i--) set_bit(&temp, i, get_bit(temp, i - 1));
  set_bit(&temp, 0, 0);
  int res = check_dec(temp);
  if (res == 0) copy_dec21(value, temp);
  // round_bank(*value, value);
  return res;
}
/* сдвиг мантиссы числа на один знак влево */
void mantissa_shift_left_long(longdec value, longdec *result) {
  longdec temp;
  copy_dec(value, &temp);
  for (int i = 191; i > 0; i--)
    set_bit_long(&temp, i, get_bit_long(temp, i - 1));
  set_bit_long(&temp, 0, 0);
  copy_dec(temp, result);
}
/* увеличение степени числа на единицу (добавление в мантиссу нуля справа) */
void add_pow(longdec value, longdec *result) {
  longdec temp, ten = {{10, 0, 0, 0, 0, 0, 0}, 0};
  mul(value, ten, &temp);
  set_pow_long(&temp, get_pow_long(value) + 1);
  copy_dec(temp, result);
}

/* уменьшение степени числа на единицу (удаление из мантиссы одной цифры справа
   и добавление в мантиссу нуля слева) */
void sub_pow(longdec value, longdec *result) {
  // longdec max_dec = {{UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0, 0}, 0};
  longdec temp, ten = {{10, 0, 0, 0, 0, 0, 0}, 0};
  div_int(value, ten, &temp);
  set_pow_long(&temp, get_pow_long(value) - 1);
  copy_dec(temp, result);
}
// twilawal
/* увеличение степени числа на n (>0) (добавление в мантиссу n нулей справа);
   уменьшение степени числа на n (<0) (удаление из мантиссы n цифр справа
   и добавление в мантиссу n нулей слева) */
int change_pow(s21_decimal value, int n, s21_decimal *result) {
  int res = 0;
  if (n == 0)
    copy_dec21(result, value);
  else {
    s21_decimal pow10n, temp;
    init_dec(0, 0, 0, 0, pow(10, abs(n)), &pow10n);
    if (n > 0) res = s21_mul(value, pow10n, &temp);
    if (n < 0) res = div_int21(value, pow10n, &temp);
    set_pow(&temp, get_pow(value) + n);
    res = (get_pow(temp) != get_pow(value) + n);
    if (res == 0) copy_dec21(result, temp);
  }
  return res;
}

// twilawal
/* нормализация двух чисел */
int normalize(s21_decimal *v1, s21_decimal *v2) {
  int res = 0;
  int n = get_pow(*v2) - get_pow(*v1);
  if (n != 0) {
    s21_decimal temp, *v = (n > 0 ? v1 : v2);
    res = change_pow(*v, abs(n), &temp);
    if (res == 0) copy_dec21(v, temp);
  }
  return res;
}

// twilawal
/* сравнение числа с нулем */
int is_zero(s21_decimal value) {
  int res = 1;
  for (int i = 0; i <= MAX_POS; i++)
    if (get_bit(value, i)) {
      res = 0;
      break;
    }
  return res;  // вернуть 1 или 0
}

/* проверка числа на слишком большое значение или равенство бесконечности */
int is_too_large(s21_decimal value) {
  s21_decimal max_dec;
  init_dec(0, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, &max_dec);
  return s21_is_greater(value, max_dec);  // вернуть 1 или 0
}

/* проверка числа на допустимые значения */
int check_dec(s21_decimal value) {
  return (is_too_small(value) ? 2 : is_too_large(value) ? 1 : 0);
}

/* проверка числа на слишком маленькое значение
или равенство отрицательной бесконечности */
int is_too_small(s21_decimal value) {
  s21_decimal min_minus, min_plus, max_minus;
  init_dec(1, 0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, &max_minus);
  init_dec(0, 28, 0, 0, 1, &min_plus);
  init_dec(1, 28, 0, 0, 1, &min_minus);
  return s21_is_less(value, max_minus);  // вернуть 1 или 0
                                         //|| (s21_is_greater(value, min_minus)
                                         //&& s21_is_less(value, min_plus));
}

// twilawal
/* целочисленное деление */
int div_int21(s21_decimal v1, s21_decimal v2, s21_decimal *result) {
  if (is_zero(v2)) return 3;
  s21_decimal quotient, diff;  // частное и разность
  init_dec(get_sign(v2), get_pow(v2), 0, 0, 0, &diff);
  //  произвести деление мантисс "столбиком"
  int res = 0;
  for (int i = MAX_POS; i >= 0; i--) {  // перебрать все биты делимого
    res = mantissa_shift_left(&diff);
    if (res) break;
    set_bit(&diff, 0, get_bit(v1, i));
    set_bit(&quotient, i, s21_is_greater_or_equal(diff, v2));
    if (s21_is_greater_or_equal(diff, v2)) res = s21_sub(diff, v2, &diff);
    if (res) break;
  }
  // установить знак и степень частного
  set_sign(&quotient, !!(get_sign(v1) - get_sign(v2)));
  set_pow(&quotient, get_pow(v1) - get_pow(v2));
  if (res == 0 && get_pow(quotient) < 0)
    res = change_pow(quotient, -get_pow(quotient), &quotient);
  // сделать анализ частного и сформировать результат
  if (res == 0) res = check_dec(quotient);
  if (res == 0) copy_dec21(result, quotient);
  return res;
}

/* банковское округление числа */
void round_bank(longdec value, longdec *result) {
  longdec ten = {{10, 0, 0, 0, 0, 0, 0}, 0};
  longdec one = {{1, 0, 0, 0, 0, 0, 0}, 0};
  longdec temp, digit_0, digit_1;
  mod(value, ten, &digit_0);
  div_int(value, ten, &temp);
  mod(temp, ten, &digit_1);
  if ((digit_0.bits[0] == 5 && digit_1.bits[0] % 2) || digit_0.bits[0] > 5)
    add(temp, one, &temp);
  set_pow_long(&temp, get_pow_long(value) - 1);
  copy_dec(temp, result);
}

int simple_fmod(s21_decimal v1, s21_decimal v2) {
  int mod = 0;
  s21_decimal diff = {0};
  s21_decimal value;
  for (int i = 95; i >= 0; i--) {
    mantissa_shift_left(&diff);
    set_bit(&diff, 0, get_bit(v1, i));
    set_bit(&value, i, !mantissa_is_greater(v2, diff));
    if (!mantissa_is_greater(v2, diff)) {
      s21_sub(diff, v2, &diff);
    }
  }
  mod = diff.bits[0];
  return mod;
}

int simple_div(s21_decimal v1, s21_decimal v2, s21_decimal *result) {
  s21_decimal value, diff;
  init_dec(get_sign(v2), get_pow(v2), 0, 0, 0, &diff);
  set_sign(&diff, get_sign(v2));
  set_pow(&diff, get_pow(v2));
  for (int i = 95; i >= 0; i--) {
    mantissa_shift_left(&diff);
    set_bit(&diff, 0, get_bit(v1, i));
    set_bit(&value, i, !mantissa_is_greater(v2, diff));
    if (!mantissa_is_greater(v2, diff)) {
      s21_sub(diff, v2, &diff);
    }
  }
  set_sign(&value, !!(get_sign(v1) - get_sign(v2)));
  set_pow(&value, get_pow(v1) - get_pow(v2));

  copy_dec21(result, value);

  return 0;
}

/* нормализация двух чисел */
void normalize_long(longdec *v1, longdec *v2) {
  longdec temp, max_dec = {{UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0, 0}, 0};
  int n = get_pow_long(*v2) - get_pow_long(*v1);
  if (n != 0) {  // увеличить степень числа с меньшей степенью
    longdec *v = (n > 0 ? v1 : v2);
    int pow = get_pow_long(n > 0 ? *v2 : *v1);
    copy_dec(*v, &temp);
    while (get_pow_long(*v) < pow && mantissa_is_less_or_equal(temp, max_dec)) {
      add_pow(temp, v);
      add_pow(temp, &temp);
    }
    n = get_pow_long(*v2) - get_pow_long(*v1);
    if (n != 0) {  // уменьшить степень числа с большей степенью
      longdec *v = (n > 0 ? v2 : v1);
      int pow = get_pow_long(n > 0 ? *v1 : *v2);
      copy_dec(*v, &temp);
      while (get_pow_long(*v) > pow) {
        if (mantissa_is_greater_long(temp, max_dec))
          round_bank(temp, v);
        else
          round_dec(temp, v);
        sub_pow(temp, &temp);
      }
    }
  }
}

// преобразование числа s21_decimal в longdec
void dec_to_longdec(s21_decimal value, longdec *result) {
  for (int i = 0; i < 7; i++) result->bits[i] = 0;
  set_sign_long(result, get_sign(value));
  set_pow_long(result, get_pow(value));
  set_bit_long(result, 96, get_bit(value, 96));  // признак INF
  result->bits[2] = value.bits[2];
  result->bits[1] = value.bits[1];
  result->bits[0] = value.bits[0];
}

// преобразование числа longdec в s21_decimal
void longdec_to_dec(longdec value, s21_decimal *result) {
  longdec temp, max_dec = {{UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0, 0}, 0};
  // подогнать мантиссу числа longdec под размеры мантиссы s21_decimal
  copy_dec(value, &temp);
  while (mantissa_is_greater_long(value, max_dec)) {
    if (get_pow_long(temp) == 0) break;
    round_bank(temp, &value);
    sub_pow(temp, &temp);
  }
  // подогнать степень числа longdec под допустимые значения s21_decimal
  copy_dec(value, &temp);
  while (get_pow_long(value) > 28) {
    round_dec(temp, &value);
    sub_pow(temp, &temp);
  }
  copy_dec(value, &temp);
  while (get_pow_long(value) < 0 && mantissa_is_less_or_equal(temp, max_dec)) {
    add_pow(temp, &value);
    add_pow(temp, &temp);
  }
  set_sign(result, get_sign_long(value));
  // сфрормировать слишком большое/маленькое число (бесконечность)
  if (get_pow_long(value) < 0 ||
      (get_pow_long(value) == 0 && mantissa_is_greater_long(value, max_dec))) {
    set_pow(result, 0);
    set_bit(result, 96, 1);  // признак INF
    result->bits[2] = UINT_MAX;
    result->bits[1] = UINT_MAX;
    result->bits[0] = UINT_MAX;
  } else {  // сформировать корректное число s21_decimal
    set_pow(result, get_pow_long(value));
    result->bits[2] = value.bits[2];
    result->bits[1] = value.bits[1];
    result->bits[0] = value.bits[0];
  }
}
int mantissa_is_zero(longdec value) {
  int flag = 1;
  for (int i = 0; i < 192; i++)
    if (get_bit_long(value, i)) {
      flag = 0;
      break;
    }
  return flag;
}

int mantissa_is_equal(longdec value1, longdec value2) {
  int flag = 1;
  for (int i = 0; i < 192; i++) {
    if (get_bit_long(value1, i) != get_bit_long(value2, i)) {
      flag = 0;
      break;
    }
  }
  return flag;
}

int mantissa_is_not_equal(longdec value1, longdec value2) {
  return !mantissa_is_equal(value1, value2);
}

int mantissa_is_greater_long(longdec value1, longdec value2) {
  int flag = 0;
  for (int i = 191; i >= 0; i--)
    if (get_bit_long(value1, i) != get_bit_long(value2, i)) {
      flag = get_bit_long(value1, i);
      break;
    }
  return flag;
}

int mantissa_is_greater_or_equal(longdec value1, longdec value2) {
  return mantissa_is_greater_long(value1, value2) ||
         mantissa_is_equal(value1, value2);
}

int mantissa_is_less(longdec value1, longdec value2) {
  return mantissa_is_greater_long(value2, value1);
}
int mantissa_is_less_or_equal(longdec value1, longdec value2) {
  return mantissa_is_less(value1, value2) || mantissa_is_equal(value1, value2);
}

void div_dec(longdec v1, longdec v2, longdec *result) {
  longdec temp = {0}, diff = {0},
          max_dec = {{UINT_MAX, UINT_MAX, UINT_MAX, 0, 0, 0, 0}, 0};
  // делить, пока мантисса частного не подтянется к максимально значению
  while (mantissa_is_less_or_equal(temp, max_dec)) {
    div_int(v1, v2, &temp);
    mod(v1, v2, &diff);
    if (mantissa_is_zero(diff)) break;
    add_pow(v1, &v1);
  }
  copy_dec(temp, result);
}
/* обычное округление числа */
void round_dec(longdec value, longdec *result) {
  longdec ten = {{10, 0, 0, 0, 0, 0, 0}, 0};
  longdec one = {{1, 0, 0, 0, 0, 0, 0}, 0};
  longdec temp, digit_0;
  mod(value, ten, &digit_0);
  div_int(value, ten, &temp);
  if (digit_0.bits[0] >= 5) add(temp, one, &temp);
  set_pow_long(&temp, get_pow_long(value) - 1);
  copy_dec(temp, result);
}
/* целочисленное деление мантисс*/
void div_int(longdec v1, longdec v2, longdec *result) {
  longdec quotient = {0}, diff = {0};  // частное и разность
  set_sign_long(&diff, get_sign_long(v2));
  set_pow_long(&diff, get_pow_long(v2));
  //  произвести деление мантисс "столбиком"
  for (int i = 95; i >= 0; i--) {  // перебрать все биты делимого
    mantissa_shift_left_long(diff, &diff);
    mantissa_shift_left_long(quotient, &quotient);
    set_bit_long(&diff, 0, get_bit_long(v1, i));
    set_bit_long(&quotient, 0, mantissa_is_greater_or_equal(diff, v2));
    if (mantissa_is_greater_or_equal(diff, v2)) sub(diff, v2, &diff);
  }
  // установить знак и степень частного
  set_sign_long(&quotient, !!(get_sign_long(v1) - get_sign_long(v2)));
  set_pow_long(&quotient, get_pow_long(v1) - get_pow_long(v2));
  // установить нулевую степень и признак бесконечности при делении на ноль
  if (mantissa_is_zero(v2)) {
    set_pow_long(&quotient, 0);
    set_bit_long(&quotient, 96, 1);  // признак INF
  }
  copy_dec(quotient, result);
}

void add(longdec v1, longdec v2, longdec *result) {
  // заменить сложение вычитанием, если знаки у аргументов разные
  if (get_sign_long(v1) != get_sign_long(v2)) {
    set_sign_long(&v2, get_sign_long(v1));
    return sub(v1, v2, result);
  }
  // установить знак и степень суммы
  longdec sum = {0};
  set_sign_long(&sum, get_sign_long(v1));
  set_pow_long(&sum, get_pow_long(v1));
  // произвести сложение мантисс "столбиком"
  int temp = 0;
  for (int i = 0; i < 192; i++) {
    int b1 = get_bit_long(v1, i);
    int b2 = get_bit_long(v2, i);
    int b3 = add_bits(b1, b2, &temp);
    set_bit_long(&sum, i, b3);
  }
  copy_dec(sum, result);
}

void mod(longdec v1, longdec v2, longdec *result) {
  longdec quotient = {0}, diff = {0};  // частное и разность
  set_sign_long(&diff, get_sign_long(v2));
  set_pow_long(&diff, get_pow_long(v2));
  //  произвести деление мантисс "столбиком"
  for (int i = 95; i >= 0; i--) {  // перебрать все биты делимого
                                   // if (i == 5)
                                   //  puts("");

    mantissa_shift_left_long(diff, &diff);
    mantissa_shift_left_long(quotient, &quotient);
    set_bit_long(&diff, 0, get_bit_long(v1, i));
    set_bit_long(&quotient, 0, mantissa_is_greater_or_equal(diff, v2));
    if (mantissa_is_greater_or_equal(diff, v2)) sub(diff, v2, &diff);
  }
  // установить нулевую степень и признак бесконечности при делении на ноль
  if (mantissa_is_zero(v2)) {
    set_pow_long(&diff, 0);
    set_bit_long(&diff, 96, 1);  // признак INF
    diff.bits[2] = UINT_MAX;
    diff.bits[1] = UINT_MAX;
    diff.bits[0] = UINT_MAX;
  }
  set_sign_long(&diff, get_sign_long(v1));

  copy_dec(diff, result);
}

void mul(longdec v1, longdec v2, longdec *result) {
  // установить знак и степень произведения
  longdec sum = {0};
  set_sign_long(&sum, get_sign_long(v1));
  set_pow_long(&sum, get_pow_long(v1));
  // умножить мантиссы "столбиком" (value_1 "сверху", value_2 "снизу")
  for (int i = 0; i < 96; i++) {
    int b2 = get_bit_long(v2, i);
    if (b2) add(sum, v1, &sum);
    mantissa_shift_left_long(v1, &v1);
  }
  // установить знак и степень произведения
  set_sign_long(&sum, !!(get_sign_long(v1) - get_sign_long(v2)));
  set_pow_long(&sum, get_pow_long(v1) + get_pow_long(v2));
  copy_dec(sum, result);
}
void sub(longdec v1, longdec v2, longdec *result) {
  // заменить вычитание сложением, если знаки у аргументов разные
  if (get_sign_long(v1) != get_sign_long(v2)) {
    set_sign_long(&v2, get_sign_long(v1));
    return add(v1, v2, result);
  }
  // установить знак и степень разности
  longdec diff = {0};
  set_sign_long(&diff, get_sign_long(v1));
  set_pow_long(&diff, get_pow_long(v1));
  //  поменять местами уменьшаемое и вычитаемое и знак разности
  if (mantissa_is_greater_long(v2, v1)) {
    int temp = get_pow_long(v1);
    set_pow_long(&v1, get_pow_long(v2));
    set_pow_long(&v2, temp);
    for (int i = 0; i < 7; i++) {
      temp = v1.bits[i];
      v1.bits[i] = v2.bits[i];
      v2.bits[i] = temp;
    }
    set_sign_long(&diff, !get_sign_long(v1));
  }
  // произвести вычитание мантисс "столбиком"
  int temp = 0;
  for (int i = 0; i < 192; i++) {
    int b1 = get_bit_long(v1, i);
    int b2 = get_bit_long(v2, i);
    int b3 = sub_bits(b1, b2, &temp);
    set_bit_long(&diff, i, b3);
  }
  copy_dec(diff, result);
}