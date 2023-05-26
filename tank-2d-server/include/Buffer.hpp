#pragma once

#include "constants.hpp"

class Buffer {
public:
	Buffer();
	~Buffer();

	void writeToBuffer(void* data, size_t size);
	BufferInfo getBufferInfo();
	void cleanBuffer();
	void readFromBuffer(void* destination, void* source, size_t size);
	// auto ready from buffer
	void startReading();
	void autoReadHeader(int* header);
	void autoReadFromBuffer(void* destination, size_t size);
	bool autoReadIsDone();

private:
	void* bufferData;
	size_t bufferSize;

	int header;
	size_t offset;
};
