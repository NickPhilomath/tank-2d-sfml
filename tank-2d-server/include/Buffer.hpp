#pragma once

#include "constants.hpp"

class Buffer {
public:
	Buffer();
	~Buffer();

	void writeToBuffer(void* data, size_t size);
	BufferInfo getBufferInfo();
	void cleanBuffer();

private:
	void* bufferData;
	size_t bufferSize;
};