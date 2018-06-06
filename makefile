CC = g++ -std=c++17

deque:
	$(CC) testDeque.cpp -o deque.out

list:
	$(CC) testList.cpp -o list.out
