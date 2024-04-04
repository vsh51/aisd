mem:
	g++ tests.cpp -o memcheck.out -lgtest -lgmock -pthread
	valgrind --leak-check=yes ./memcheck.out

dev:
	g++ Shpyrka_markov.cpp -o dev.out -lgtest -lgmock -pthread
	./dev.out

test:
	g++ tests.cpp Shpyrka_markov.cpp -o test.out -lgtest -lgmock -pthread
	./test.out