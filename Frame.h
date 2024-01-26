#pragma once
#include <iostream>
#include <memory>

struct VideoFrame
{
	VideoFrame();

	VideoFrame(unsigned char* buf, size_t length);

	//copy
	VideoFrame(const VideoFrame& other);

	//copy operater
	VideoFrame& operator=(const VideoFrame& other);

	//move operater
	VideoFrame& operator=(VideoFrame&& other)noexcept;

	~VideoFrame();

	unsigned char* data;   /*视频数据*/
	size_t dataLen;        /*视频数据长度*/

};

struct Node
{
	VideoFrame vFrame;

	Node*next;

	Node();
	
	Node(unsigned char* buf, size_t length);
	~Node();	
};

using PFrame = std::shared_ptr<VideoFrame>;



