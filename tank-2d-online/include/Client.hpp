#pragma once

#include <iostream>
#include <stdexcept>
#include <enet/enet.h>
#include <SFML/System.hpp>

#include "clientConstants.hpp"

class Client {
public:
	Client(std::string addressName, uint32_t portNum);
	~Client();

	void connect();
	void send(const std::string& buffer);
	void send(const void* buffer, size_t size);
	void recieve(TransferBuffer* snapShot);
	void disconnect();

	bool connected = false;

private:
	std::string serverAddress;
	ENetHost* clientHost;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;
};