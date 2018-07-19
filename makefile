CC = clang++ -std=c++17

merge:
	$(CC) testMerge.cpp -o sort.out

hash:
	$(CC) testHash.cpp -o hash.out

tree:
	$(CC) testTree.cpp -o tree.out

deque:
	$(CC) testDeque.cpp -o deque.out

list:
	$(CC) testList.cpp -o list.out

clean:
	rm -v *.out
