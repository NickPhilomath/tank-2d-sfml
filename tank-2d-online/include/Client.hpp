#pragma once

#include <iostream>
#include <stdexcept>
#include <enet/enet.h>
#include <SFML/System.hpp>

#include "constants.hpp"

struct TransferBuffer {
	Group group;
	sf::Vector2f position;
	float speed;
	float rotation;
	float turrentRotation;
};

class Client {
public:
	Client(std::string addressName, uint32_t portNum);
	~Client();

	void connect();
	void send(const std::string& buffer);
	void send(const TransferBuffer& buffer);
	void recieve();
	void disconnect();

	bool connected = false;

private:
	std::string serverAddress;
	ENetHost* clientHost;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;
};