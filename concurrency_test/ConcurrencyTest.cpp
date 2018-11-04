#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>

#include "CircularWSDeque.h"

// single deque with 64 elements
CircularWSDeque<int> DEQUE(6);

void call_from_thread(int my_index, int double_sleep) {
	auto work_item = DEQUE.steal();
	std::cout << work_item << std::endl;
	while (work_item) {
		std::cout << "THREAD INDEX: " << my_index << " PROCESSED ITEM " << work_item << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100 + 100*double_sleep));
		work_item = DEQUE.steal();
	}
}

int main() {
	std::vector<std::thread> threads;

	for (int i = 0; i < 2; ++i) {
		for (int j = 1; j < 25; ++j)
			DEQUE.push_bottom(1 + (j % 2));
		threads.push_back(std::thread(call_from_thread, i, i));
	}

	for (int i = 0; i < 2; ++i) {
		threads[i].join();
	}

	return 0;
}
