#pragma once

#include <stdint.h>
#include <stdexcept>
#include <enet/enet.h>

#include "constants.hpp"

class Server {
public:
	Server(uint32_t port);
	~Server();

	void send(const std::string& buffer, ENetPeer* peer);
	void send(const TransferBuffer& buffer, ENetPeer* peer);
	void send(const void* buffer, uint32_t size, ENetPeer* peer);
	void disconnect(ENetPeer* peer);

	ENetHost* serverHost;
	ENetEvent event;
	ENetAddress address;

private:
};