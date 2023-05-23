# Decimal 
Implementation of decimal.h library in the C programming language. This library add the ability to work with the "decimal" type, which is not in the language standard.

## Information

### Arithmetic Operators

| Operator name | Operators  | Function                                                                           | 
| ------ | ------ |------------------------------------------------------------------------------------|
| Addition | + | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)         |
| Subtraction | - | int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Multiplication | * | int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) | 
| Division | / | int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Modulo | Mod | int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |

The functions return the error code:
- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

*Note on the numbers that do not fit into the mantissa:*
- *When getting numbers that do not fit into the mantissa during arithmetic operations, used bank rounding (for example, 79,228,162,514,264,337,593,543,950,335 - 0.6 = 79,228,162,514,264,337,593,543,950,334)*

*Note on the mod operation:*
- *If an overflow occurred as a result, discard the fractional part (for example, 70,000,000,000,000,000,000,000,000,000 % 0.001 = 0.000)*


### Comparison Operators
| Less than | < |
| Less than or equal to | <= | 
| Greater than | > |
| Greater than or equal to | >= |
| Equal to | == |
| Not equal to | != |

Return value:
- 0 - FALSE
- 1 - TRUE

### Convertors and parsers

| Convertor/parser |
| ------ |
| From int  |
| From float  |
| To int  | 
| To float  |

Return value - code error:
- 0 - OK
- 1 - convertation error

### Another functions

| Description |
| ------ |------------------------------------------------------------------|
| Rounds a specified Decimal number to the closest integer toward negative infinity. |
| Rounds a decimal value to the nearest integer. |
| Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes. | 
| Returns the result of multiplying the specified Decimal value by negative one. 

Return value - code error:
- 0 - OK
- 1 - calculation error

## Task 1. Implementation of the decimal.h library functions

The functions of the decimal.h library described [above](#information) must be implemented:
- The library must be developed in C language of C11 standard using gcc compiler
- Make it as a static library (with the s21_decimal.h header file)
- Prepare full coverage of library functions code with unit-tests using the Check library
- Unit tests must cover at least 80% of each function (checked using gcov)    
- The gcov_report target should generate a gcov report in the form of an html page. Unit tests must be run with gcov flags to do this
- The defined type must support numbers from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.
