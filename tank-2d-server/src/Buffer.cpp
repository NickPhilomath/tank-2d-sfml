#include "Buffer.hpp"

Buffer::Buffer() {
	bufferData = malloc(0);
	bufferSize = 0;
}

Buffer::~Buffer() {
	free(bufferData);
}

void Buffer::writeToBuffer(void* data, size_t size) {
	bufferData = realloc(bufferData, bufferSize + size);
	memcpy((char*)bufferData + bufferSize, data, size);
	bufferSize += size;
}

BufferInfo Buffer::getBufferInfo() {
	BufferInfo info{};
	info.bufferData = bufferData;
	info.size = bufferSize;
	return info;
}

void Buffer::cleanBuffer() {
	free(bufferData);
	bufferData = malloc(0);
	bufferSize = 0;
}
