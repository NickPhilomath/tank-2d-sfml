#include "Server.hpp"

Server::Server(uint32_t port) {
	address.host = ENET_HOST_ANY;
	address.port = port;

	if (enet_initialize() != 0) {
		throw std::runtime_error("cannot initialize enet");
	}

	serverHost = enet_host_create(&address,
		32,   //number of clients
		2,    //number of channels
		0,    // assume any amount of incoming bandwidth 
		0     // assume any amount of outgoing bandwidth
	);

}

Server::~Server() {
	for (auto player : players) {
		delete player;
	}

	enet_host_destroy(serverHost);
	enet_deinitialize();
}

void Server::run() {

	if (serverHost == NULL)
	{
		throw std::runtime_error("An error occurred while trying to create an ENet server host");
	}

	while (true) {
		listen();
	}
}

void Server::listen() {
	while (enet_host_service(serverHost, &event, 30) > 0) {
		switch (event.type) {
		case ENET_EVENT_TYPE_CONNECT:
			{
				Player* player = new Player(event.peer);
				players.push_back(player);
			}
			std::cout
				<< "A new client connected from " << event.peer->address.host
				<< " port: " << event.peer->address.port
				<< " peerID: " << event.peer->incomingPeerID
				<< ".\n";
			break;

		case ENET_EVENT_TYPE_RECEIVE:
			{
				TransferData recvData;
				memcpy(&recvData, event.packet->data, sizeof(TransferData));
				std::cout << recvData.position.x << " " << recvData.position.y << "." << std::endl;
			}

			enet_packet_destroy(event.packet);
			// send back a data 
			send("recived!", event.peer);
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << event.peer->incomingPeerID << " disconnected. \n";
			// remove from peers array
			for (uint32_t i = 0; i < players.size(); i++) {
				if (players[i]->ID == event.peer->incomingPeerID) {
					players.erase(players.begin() + i);
				}
			}
			// std::cout << "// vector size: " << peers.size() << "\n";
			event.peer->data = NULL;
		}
	}
}

void Server::send(const std::string& buffer, ENetPeer* peer) {
	ENetPacket* packet = enet_packet_create(buffer.c_str(), buffer.size() + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

void Server::disconnect(ENetPeer* peer) {
}

