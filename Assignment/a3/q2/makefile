test: $(set)
	clang -Wall -c test.c -o test.o
	clang -Wall main.c $(set) test.o -o main
	./main
