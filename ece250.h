#ifndef ECE250
#define ECE250

#include <cstdlib>
#include <iostream>
/* #include <sstream> */
#include "Exception.h"
#include <cmath>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <string>

/****************************************************************************
 * **************************************************************************
 * * You don't have to use the Tester classes to use this to manage your
 * * memory.  All you must do is include this file and then, if you ever
 * * want to test if you have memory which is currently unallocated,
 * * you may use ece250::allocation_table.summary();
 * *
 * * You must simply indicate that you want to start recording by
 * * using ece250::alocation_table.summary();
 * *
 * **************************************************************************
 ****************************************************************************/

/****************************************************************************
 * ece250
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-13 by Douglas Wilhelm Harder and Vajih Montaghami.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *
 * This file is broken into two parts:
 *
 *   1. The first namespace ece250 is associated with tools used by the
 *      second part.
 *   2. The second has globally overloaded new, delete, new[], and delete[].
 *
 * This tracks everything that deals with memory allocation (new and new[])
 * and memory deallocation (delete and delete[]).
 *
 * Each time 'new' or 'new[]' is called, an appropriate entry is
 * set in a hash table 'allocation_table'.  The hash function of any address
 * is the last log[2](array_size) bits.
 *
 * Each time that 'delete' or 'delete[]' is called, it is checked whether:
 *   1. the memory was actually allocated,
 *   2. the appropriate form of delete versus delete[] is being called, and
 *   3. delete/delete[] has been called multiple times.
 *
 * The class also stores how much memory was allocated and how much was
 * deallocated.  The summary() function prints a summary indicating the
 * difference.  When this is called at the end of a test, the result must
 * be zero (0).
 *
 * If there is a problem with either allocation or deallocation, two events
 * occur:  a warning is printed and an exception is thrown.
 *
 * Each throw is associated with a warning sent to the student through cout.
 ****************************************************************************/

namespace ece250 {
int memory_alloc_store;

const size_t PAD = 16;

class overflow {};
class invalid_deletion {};
class invalid_input {};

// Each time a student calls either new or new[], the
// information about the memory allocation is stored in
// an instance of this class

class Stopwatch {
private:
	clock_t start_time;
	float duration;

public:
	Stopwatch() {
		duration = 0;
	}

	void start() {
		start_time = std::clock();
	}

	void stop() {
		clock_t end_time = std::clock();
		//this supposed to be milisecond
		duration = ((float)end_time - start_time) / CLOCKS_PER_SEC;
	}

	float get_last_duration() const {
		return duration;
	}
};

class Allocation {
public:
	void *address;
	size_t size;
	bool is_array;
	bool deleted;

	Allocation() : address(0),
		       size(0),
		       is_array(false),
		       deleted(false) {
		// Empty constructor
	}

	Allocation(void *a, size_t s, bool i) : address(a),
						size(s),
						is_array(i),
						deleted(false) {
		// Empty constructor
	}
};

int to_int(int *ptr) {
	int result = *ptr;

	if (result < 0) {
		result = result + (1 << (sizeof(int) - 1));
	}

	return result >> 3;
}

// All instances of an allocation are stored in this chained hash table

class HashTable {
private:
	int array_size;
	Allocation *allocated;
	int total_memory_alloc;
	int total_memory_deleted;
	bool record;

public:
	// Initialize all of the addresses to 0

	HashTable(int as) : array_size(as),
			    total_memory_alloc(0),
			    total_memory_deleted(0),
			    record(false) {
		allocated = new Allocation[array_size];
	}

	void reserve(int N) {
		// N must be a power of 2

		if ((N & ((~N) + 1)) != N) {
			throw illegal_argument();
		}

		delete[] allocated;
		array_size = N;
		allocated = new Allocation[array_size];
	}

	int memory_alloc() const {
		return total_memory_alloc - total_memory_deleted;
	}

	void memory_store() const {
		memory_alloc_store = total_memory_alloc - total_memory_deleted;
	}

	void memory_change(int n) const {
		int memory_alloc_diff = total_memory_alloc - total_memory_deleted - memory_alloc_store;

		if (memory_alloc_diff != n) {
			std::cout << "WARNING: expecting a change in memory allocation of "
				  << n << " bytes, but the change was " << memory_alloc_diff
				  << std::endl;
		}
	}

	// Insert uses the last log[2]( array_size ) bits of the address as the hash function
	// It finds an unallocated entry in the array and stores the information
	// about the memory allocation in that entry, including:
	//      The amount of memory allocated,
	//      Whether new or new[] was used for the allocation, and
	//      The address of the allocated memory.

	void insert(void *ptr, size_t size, bool is_array) {
		if (!record) {
			return;
		}

		// the hash function is the last log[2]( array_size ) bits
		int hash = to_int(reinterpret_cast<int *>(&ptr)) & (array_size - 1);

		for (int i = 0; i < array_size; ++i) {
			// It may be possible that we are allocated the same memory
			// location twice (if there are numerous allocations and
			// deallocations of memory.  Thus, the second check is necessary,
			// otherwise it may introduce session dependant errors.

			if (allocated[hash].address == 0 || allocated[hash].address == ptr) {
				// Store the address, the amount of memory allocated,
				// whether or not new[] was used, and set 'deleted' to false.

				allocated[hash] = Allocation(ptr, size, is_array);

				// Add the memory allocated to the total memory allocated.
				total_memory_alloc += size;

				return;
			}

			hash = (hash + 1) & (array_size - 1);
		}

		std::cout << "WARNING: allocating more memory than is allowed for this project" << std::endl;
		throw overflow();
	}

	// Remove checks:
	//     If the given memory location was allocated in the first place, and
	//     If the appropriate form of delete was used, i.e., delete versus delete[], and
	//     If delete has already been called on this object

	size_t remove(void *ptr, bool is_array) {
		if (!record || ptr == 0) {
			return 0;
		}

		// the hash function is the last log[2]( array_size ) bits
		int hash = to_int(reinterpret_cast<int *>(&ptr)) & (array_size - 1);

		// Continue searching until we've checked all bins
		// or we find an empty bin.

		for (int i = 0; i < array_size && allocated[hash].address != 0; ++i) {
			if (allocated[hash].address == ptr) {
				// First check if:
				//    1. If the wrong delete was called (e.g., delete[] when new was
				//       used or delete when new[] was used).
				//    2. If the memory has already been deallocated previously.
				//
				// If the deletion is successful, then:
				//    1. Set the 'deleted' flag to 'true', and
				//    2. Add the memory deallocated ot the total memory deallocated.

				if (allocated[hash].is_array != is_array) {
					if (allocated[hash].is_array) {
						std::cout << "WARNING: use 'delete [] ptr;' to free memory allocated with 'ptr = new Class[array_size];'" << std::endl;
					} else {
						std::cout << "WARNING: use 'delete ptr;' to free memory allocated with 'ptr = new Class(...);'" << std::endl;
					}

					throw invalid_deletion();
				} else if (allocated[hash].deleted) {
					std::cout << "WARNING: calling delete twice on the same memory location: " << ptr << std::endl;
					throw invalid_deletion();
				}

				allocated[hash].deleted = true;
				total_memory_deleted += allocated[hash].size;

				// zero the memory before it is deallocated

				char *cptr = static_cast<char *>(ptr);

				for (size_t j = 0; j < allocated[hash].size; ++j) {
					cptr[j] = 0;
				}

				return allocated[hash].size;
			}

			hash = (hash + 1) & (array_size - 1);
		}

		// If we've gotten this far, this means that the address was
		// never allocated, and therefore we are calling delete on
		// something which should be deleted.

		std::cout << "WARNING: deleting a pointer to which memory was never allocated: " << ptr << std::endl;
		throw invalid_deletion();
	}

	// Print a difference between the memory allocated and the memory deallocated

	void summary() {
		std::cout << "Memory allocated minus memory deallocated: "
			  << total_memory_alloc - total_memory_deleted << std::endl;
	}

	// Print the difference between total memory allocated and total memory deallocated.

	void details() {
		std::cout << "SUMMARY OF MEMORY ALLOCATION:" << std::endl;

		std::cout << "  Memory allocated:   " << total_memory_alloc << std::endl;
		std::cout << "  Memory deallocated: " << total_memory_deleted << std::endl
			  << std::endl;

		std::cout << "INDIVIDUAL REPORT OF MEMORY ALLOCATION:" << std::endl;
		std::cout << "  Address  Using  Deleted  Bytes   " << std::endl;

		for (int i = 0; i < array_size; ++i) {
			if (allocated[i].address != 0) {
				std::cout << "  " << allocated[i].address
					  << (allocated[i].is_array ? "  new[]     " : "  new       ")
					  << (allocated[i].deleted ? "Y    " : "N    ")
					  << std::setw(6)
					  << allocated[i].size << std::endl;
			}
		}
	}

	// Start recording memory allocations

	void start_recording() {
		record = true;
	}

	// Stop recording memory allocations

	void stop_recording() {
		record = false;
	}

	bool is_recording() {
		return record;
	}
};

bool asymptotic_tester(double *array, int N, int k, bool ln) {
	double *ratios = new double[N];
	double *differences = new double[N - 1];

	int M = 2;

	for (int i = 0; i < N; ++i) {
		ratios[i] = array[i] / (M * (ln ? std::log(static_cast<double>(M)) : 1.0));

		M = M * (1 << k);
	}

	for (int i = 0; i < N - 1; ++i) {
		differences[i] = ratios[i + 1] - ratios[i];
		// std::cout << differences[i] << std::endl;
	}

	for (int i = 1; i < N - 1; ++i) {
		if (!(differences[i] < 0)) {
			if (differences[i] > differences[i - 1]) {
				delete[] ratios;
				delete[] differences;

				return false;
			}
		}
	}

	delete[] ratios;
	delete[] differences;

	return true;
}

HashTable allocation_table(8192);

std::string history[1000];
int count = 0;

// Set the contents of the allocated memory to alternating 0s and 1s
// 'U' = 0b01010101
// Four bytes are therefore 0x55555555 or 1431655765
//
// Sixteen bytes before and after the requested memory are also allocated and initialized.
//    ________________                                            ________________
//    UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU

void initialize_array_bounds(char *ptr, size_t size) {
	std::memset(ptr, 'U', size);
}

// When the user returns memory, we must check that the padding is unchaged.
//    ________________                                            ________________
//    UUUUUUUUUUUUUUUUxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxUUUUUUUUUUUUUUUU
// We also check that the memory has been used--if allocated memory is left untouched,
// there was an unnecessary allocation of memory.
//
// Finally, we reset all the entries to 'U' to ensure that if the user attempts to
// access this memory again, an error will occur.
//    ________________                                            ________________
//    UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU

void check_array_bounds(char *ptr, size_t size) {
	for (size_t i = 0; i < PAD; ++i) {
		if (ptr[i] != 'U') {
			std::cout << "Memory before the array located at adderss "
				  << static_cast<void *>(ptr + PAD) << " was overwritten" << std::endl;
			throw out_of_range();
		}

		if (ptr[size - 1 - i] != 'U') {
			std::cout << "Memory after the array located at adderss "
				  << static_cast<void *>(ptr + PAD) << " was overwritten" << std::endl;

			throw out_of_range();
		}
	}

	bool used = false;

	for (size_t i = 0; i < size - 2 * PAD; ++i) {
		if (ptr[PAD + i] != 'U') {
			used = true;
			break;
		}
	}

	if (!used) {
		std::cout << "The memory allocated at adderss "
			  << static_cast<void *>(ptr + PAD) << " was not used" << std::endl;
	}

	std::memset(ptr, 'U', size);
}

/*	// Type input<Type>()
	//
	// Attempt to parse the input as if it is of the given Type
	//  - If it fails, it prints an error message and throws an exception

	template <typename Type>
	Type input() {
		std::string s;

		std::cin >> s;

		std::stringstream ss( s );

		Type n;
		ss >> n;

		if ( ss.fail() ) {
			std::cerr << "Not expecting the input \"" << s << "\"" << std::endl;
			throw invalid_input();
		}

		return n;
	}

	// bool input<bool>()
	//
	// This is a specialization of the input function for Boolean values
	//  - It will accept the strings 'true' and 'false' as well as 1 and 0
	//  - If it fails, it prints an error message and throws an exception

	template <>
	bool input<bool>() {
		std::string s;

		std::cin >> s;

		std::stringstream ss( s );

		if ( s == "true" ) {
			return 1;
		} else if ( s == "false" ) {
			return 0;
		} else {
			bool n;
			ss >> n;

			if ( ss.fail() ) {
				std::cerr << "Not expecting the input \"" << s << "\"" << std::endl;
				throw invalid_input();
			}

			return n;
		}
	} */
} // namespace ece250

/****************************************************************************
 * new
 * Author:  Douglas Wilhelm Harder
 * Overloads the global operator new
 *
 * Use malloc to perform the allocation.
 * Insert the pointer returned by malloc into the hash table.
 *
 * The argument 'false' indicates that this is a call
 * to new (versus a call to new[]).
 *
 * Return the pointer to the user.
 ****************************************************************************/

void *operator new(size_t size) throw(std::bad_alloc) {
	void *ptr = malloc(size);
	ece250::allocation_table.insert(ptr, size, false);
	return static_cast<void *>(ptr);
}

/****************************************************************************
 * delete
 * Author:  Douglas Wilhelm Harder
 * Overloads the global operator delete
 *
 * Remove the pointer from the hash table (the entry is not truly removed,
 * simply marked as removed).
 *
 * The argument 'false' indicates that this is a call
 * to delete (versus a call to delete[]).
 *
 * Use free to perform the deallocation.
 ****************************************************************************/

void operator delete(void *ptr) throw() {
	ece250::allocation_table.remove(ptr, false);
	free(ptr);
}

/****************************************************************************
 * new[]
 * Author:  Douglas Wilhelm Harder
 * Overloads the global operator new[]
 *
 * Use malloc to perform the allocation.
 * Insert the pointer returned by malloc into the hash table.
 *
 * The argument 'true' indicates that this is a call
 * to new[] (versus a call to new).
 *
 * Return the pointer to the user.
 ****************************************************************************/

void *operator new[](size_t size) throw(std::bad_alloc) {
	char *ptr = static_cast<char *>(malloc(size + 2 * ece250::PAD));
	ece250::allocation_table.insert(static_cast<void *>(ptr + ece250::PAD), size, true);
	ece250::initialize_array_bounds(ptr, size + 2 * ece250::PAD);
	return static_cast<void *>(ptr + ece250::PAD);
}

/****************************************************************************
 * delete[]
 * Author:  Douglas Wilhelm Harder
 * Overloads the global operator delete[]
 *
 * Remove the pointer from the hash table (the entry is not truly removed,
 * simply marked as removed).
 *
 * The argument 'true' indicates that this is a call
 * to delete[] (versus a call to delete).
 *
 * Use free to perform the deallocation.
 ****************************************************************************/

void operator delete[](void *ptr) throw() {
	size_t size = ece250::allocation_table.remove(ptr, true);

	if (ece250::allocation_table.is_recording()) {
		ece250::check_array_bounds(static_cast<char *>(ptr) - ece250::PAD, size + 2 * ece250::PAD);
	}

	free(static_cast<char *>(ptr) - ece250::PAD);
}

#endif
