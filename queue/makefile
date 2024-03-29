test:
	g++ queue_tests.cpp Shpyrka_queue.cpp -o q_tests -lgtest -lgmock -pthread
	./Queue

dev:
	g++ Shpyrka_queue.cpp -o Queue -lgtest -lgmock -pthread
	./Queue

mem-check:
	g++ queue_tests.cpp Shpyrka_queue.cpp -o Queue.out -lgtest -lgmock -pthread
	valgrind --leak-check=yes ./Queue.out