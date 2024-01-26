#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "Frame.h"

struct CircularBuffer
{
	CircularBuffer(size_t _size);

	//copy constructor
	CircularBuffer(const CircularBuffer& other) = delete;
	//copy operater
	CircularBuffer& operator=(const CircularBuffer& other) = delete;
	//move operater
	CircularBuffer& operator=(CircularBuffer&& other)noexcept = delete;

	~CircularBuffer();	

	size_t GetCapacity();

	size_t GetSize();

	bool isFull();

	bool isEmpty();

	/**
	 * 队列中有效数据个数.
	 *
	 * \return
	 */
	size_t Size();

	void push(unsigned char* src, int length);

	void movebuffer();

	//for test
	//void set();

	size_t cap;                  /*最大容量*/
	size_t nodeCount;            /*数据的个数*/
	size_t totalSize;            /*所有节点数据域总大小*/
	Node* head;
	Node* tail;
	std::mutex mt;
	std::condition_variable cv;
	unsigned char* buffer;
};
