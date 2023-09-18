C = gcc -std=c11 -Wall -Werror -Wextra
GCOVFLAGS =  -fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
    F_LIB_CHECK = -lcheck -pthread -lrt -lm -lsubunit
else
    F_LIB_CHECK = -lcheck 
endif

all: clean matrix.a 

matrix.a: clean
	$(C) -c *.c $(F_LIB_CHECK)
	ar rc ../lib/libmatrix.a *.o
	# ranlib libmatrix.a
	cp ../lib/libmatrix.a ../lib/matrix.a
	$(C) -shared -o ../lib/libmatrix.so *.o

test: matrix.a
	$(C) ../lib/libmatrix.a ../tests/*.c  $(F_LIB_CHECK) -o test -L../lib/ -lmatrix
	./test

clang: test matrix.a
	clang-format -n *.c *.h
	clang-format -n tests/*.c
	clang-format -i *.c *.h
	clang-format -i tests/*.c

gcov_report: clean matrix.a
	$(C) $(GCOVFLAGS) ../tests/*.c *.c $(F_LIB_CHECK) -o test -L../lib -lmatrix
	./test
	gcov tests/*.c
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda 
	open ./report/index.html


leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind:
	$(C) ../lib/libmatrix.a tests/*.c  $(F_LIB_CHECK) -o test -L../lib -lmatrix -ggdb
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
	
valgrind_full:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf *.o test *.info *.a  *.dSYM *.out report *.txt