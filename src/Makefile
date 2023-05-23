FLAGS = -Wall -Werror -Wextra -std=c11

all: s21_decimal.a

s21_decimal.a:
	gcc -c $(FLAGS) s21_*.c
	ar rc s21_decimal.a s21_*.o
	ranlib s21_decimal.a

test: s21_decimal.a
	gcc -c $(FLAGS) test_decimal.c
	gcc -c $(FLAGS) main.c
	gcc -lcheck -fprofile-arcs -ftest-coverage s21_*.c s21_decimal.a test_decimal.o main.o -o tests
	./tests 

gcov_report:	test
	gcov -i s21_*.gcda	
	lcov -t "decimal1" -o decimal1.info -c -d .
	genhtml -o report decimal1.info
	cd report/ && open index.html
	# gcovr --html-details -o report.html
	# open report.html

clean:
	rm -rf *.o *.a *.gcno  *.gcda *.gcov *.css *.html *.dSYM report *.info *.gz
	rm -rf tests