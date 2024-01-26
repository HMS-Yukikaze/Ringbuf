#include <iostream>
#include <memory>
#include <mutex>
#include <algorithm>
#include "Frame.h"
#include "CircularBuffer.h"

int main() {

	CircularBuffer cb(10);
	/*std::thread([&cb]() {
		cb.movebuffer();
		}).detach();
	std::thread([&cb]() {
		cb.set();
		}).join();*/

		

	return 0;
}

