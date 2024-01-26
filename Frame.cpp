#include "Frame.h"
VideoFrame::VideoFrame()
	: data{ nullptr },
	dataLen{ 0 }
{
}

VideoFrame::VideoFrame(unsigned char* buf, size_t length)
	: dataLen{ length }
{
	data = new unsigned char[length];
	memcpy(data, buf, length);
}

VideoFrame::VideoFrame(const VideoFrame& other)
	: dataLen{ other.dataLen }
{
	data = new unsigned char[other.dataLen];
	memcpy(data, other.data, other.dataLen);
}

VideoFrame& VideoFrame::operator=(const VideoFrame& other)
{
	if (this == &other)
		return *this;
	this->data = new unsigned char[other.dataLen];
	this->dataLen = other.dataLen;

	return *this;
}

VideoFrame& VideoFrame::operator=(VideoFrame&& other)noexcept
{
	this->data = std::move(other.data);
	this->dataLen = other.dataLen;
	return *this;
}


VideoFrame::~VideoFrame()
{	
	delete[] data;
}


Node::Node()
	:vFrame{}, next{ nullptr }{}

Node::Node(unsigned char* buf, size_t length)
	: vFrame{ buf,length }, next{ nullptr }{}
Node::~Node()
{

}
;
