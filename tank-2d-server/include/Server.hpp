#pragma once

#include <stdint.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <enet/enet.h>

#include "Player.hpp"

struct TransferData {
	sf::Vector2f position;
};

class Server {
public:
	Server(uint32_t port);
	~Server();

	void run();

private:
	//void Initialize();

	void listen();
	void send(const std::string& buffer, ENetPeer* peer);
	void disconnect(ENetPeer* peer);

	ENetAddress address;
	ENetHost* serverHost;
	ENetEvent event;
	std::vector<Player*> players;
};