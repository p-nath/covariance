all: covariance_main

covariance_main: covariance_main.o matrix.o
	gcc -o covariance_main covariance_main.o matrix.o

matrix.o: matrix.c
	gcc -c -Wall matrix.c

matrix.c: matrix.h

covariance_main.o: covariance_main.c
	gcc -c -Wall covariance_main.c



