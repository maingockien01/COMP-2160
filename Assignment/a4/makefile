run: $(main).c ObjectManager.h ObjectManager.c
	clang++ -Wall -c test.c -o test.o
	clang++ -Wall -c list.c -o list.o
	clang++ -Wall -c ObjectManager.c -o ObjectManager.o
	clang++ -Wall $(main).c ObjectManager.o list.o test.o -o $(main)
	./$(main)

