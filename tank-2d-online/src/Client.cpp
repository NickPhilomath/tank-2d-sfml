#include "Client.hpp"


Client::Client(std::string addressName, uint32_t portNum)
	: serverAddress{ addressName } {
	address.port = portNum;

	if (enet_initialize() != 0) {
		throw std::runtime_error("cannot initialize enet");
	}

	clientHost = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);
	if (clientHost == NULL) {
		throw std::runtime_error("An error occurred while trying to create an ENet client host.");
	}

	enet_address_set_host(&address, serverAddress.c_str());
}

Client::~Client() {
	enet_host_destroy(clientHost);
	enet_deinitialize();
}

void Client::connect() {
	/* Initiate the connection, allocating the two channels 0 and 1. */
	peer = enet_host_connect(clientHost, &address, 2, 0);
	if (peer == NULL) {
		throw std::runtime_error("No available peers for initiating an ENet connection");
	}

	if (enet_host_service(clientHost, &event, 3000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection succeeded." << std::endl;
		connected = true;
	}
	else {
		enet_peer_reset(peer);
		std::cout << "Connection failed." << std::endl;
	}
}

void Client::send(const std::string& buffer) {
	ENetPacket* packet = enet_packet_create(buffer.c_str(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

void Client::send(const void* buffer, size_t size) {
	ENetPacket* packet = enet_packet_create(buffer, size, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

void Client::send(const void* buffer, size_t size, _ENetPacketFlag flag) {
	ENetPacket* packet = enet_packet_create(buffer, size, flag);
	enet_peer_send(peer, 0, packet);
}

void Client::recieve(Buffer& buffer) {
	while (enet_host_service(clientHost, &event, 30) > 0) {
		if (event.type == ENET_EVENT_TYPE_RECEIVE) {
			buffer.cleanBuffer();
			buffer.writeToBuffer(event.packet->data, event.packet->dataLength - 1);
			enet_packet_destroy(event.packet);
		}
		else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
			connected = false;
			event.peer->data = NULL;
		}
	}
}

void Client::disconnect() {
	bool disconnected = false;
	enet_peer_disconnect(peer, 0);
	while (enet_host_service(clientHost, &event, 100) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << "Disconnection succeeded. \n";
			disconnected = true;
		}
	}
	/* We've arrived here, so the disconnect attempt didn't */
	/* succeed yet.  Force the connection down.             */
	if(!disconnected) enet_peer_reset(peer);
}
