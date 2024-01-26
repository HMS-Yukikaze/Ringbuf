#include "CircularBuffer.h"
using namespace std::chrono_literals;

CircularBuffer::CircularBuffer(size_t _size)
	:cap{ _size },
	nodeCount{ 0 },
	totalSize{ 0 },
	tail{ 0 },
	head{ 0 }
{
	buffer = new unsigned char[_size];
}


CircularBuffer::~CircularBuffer()
{
	delete[] buffer;
}

size_t CircularBuffer::GetCapacity()
{
	return cap;
}

size_t CircularBuffer::GetSize()
{
	return nodeCount == 0;
}

bool CircularBuffer::isFull()
{
	return totalSize == cap;
}

bool CircularBuffer::isEmpty()
{
	return nodeCount == 0;
}

size_t CircularBuffer::Size()
{
	return nodeCount;
}

void CircularBuffer::push(unsigned char* src, int length)
{
	if (length > cap) {
		throw std::runtime_error("input data over set capacity");
	}
	std::unique_lock<std::mutex>lk(mt);
	//1.未满,链表为空
	//2.正好满
	//3,未满，但是容量不足以放下此length
	if (isFull()||(totalSize+length)>cap) {
		Node* temp = head;
		head = head->next;		
		tail->next = head;
		totalSize -= head->vFrame.dataLen;
		delete temp;
		nodeCount--;
	}
	Node* newNode = new Node(src, length);
	if (isEmpty()) {
		head = tail = newNode;
		tail->next = head; 
	}
	else {
		tail->next = newNode;
		tail = newNode;
		tail->next = head;
	}

	nodeCount++;
	totalSize += length;
	lk.unlock();
}



void CircularBuffer::movebuffer()
{
	std::this_thread::sleep_for(10s);

	std::unique_lock<std::mutex>lk(mt);
	if (head == nullptr) {
		std::cout << "CircularBuffer is empty!." << std::endl;
		return;
	}

	Node* current = head;
	size_t pos = 0;
	memset(buffer, 0, cap);
	do {
		std::memcpy(buffer + pos, current->vFrame.data, current->vFrame.dataLen);
		pos += current->vFrame.dataLen;
		current = current->next;
	} while (current != head);
	lk.unlock();
	std::printf("Buffer:%s\n", buffer);

}

//void CircularBuffer::set()
//{	
//	while (true)
//	{
//		push((unsigned char*)"123",3);
//		std::cout << "set value~" << std::endl;
//		std::this_thread::sleep_for(2s);
//	}
//}
