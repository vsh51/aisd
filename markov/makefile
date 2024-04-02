mem:
	g++ Shpyrka_markov.cpp -o memcheck.out -lgtest -lgmock -pthread
	valgrind --leak-check=yes ./memcheck.out

dev:
	g++ Shpyrka_markov.cpp -o dev.out -lgtest -lgmock -pthread
	./dev.out