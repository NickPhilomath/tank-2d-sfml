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

void Buffer::readFromBuffer(void* destination, void* source, size_t size) {
	memcpy(destination, source, size);
}

void Buffer::startReading() {
	offset = 0;
}

void Buffer::autoReadHeader(int* header) {
	memcpy(header, offset + (char*)bufferData, sizeof(int));
}

void Buffer::autoReadFromBuffer(void* destination, size_t size) {
	if (offset + size > bufferSize) throw std::runtime_error("attemt to read outside of buffer");
	memcpy(destination, offset + (char*)bufferData, size);
	offset += size;
}

bool Buffer::autoReadIsDone() {
	return offset == bufferSize;
}