#include "App.hpp"

App::App() : server{PORT} {
}

App::~App() {
}

void App::networkFunction() {
	LOG("server started.");
	while (true) {
		while (enet_host_service(server.serverHost, &server.event, NET_UPDATE) > 0) {
			if (server.event.type == ENET_EVENT_TYPE_CONNECT) {
				ServerPlayer* player = new ServerPlayer(server.event.peer, server.event.peer->incomingPeerID);
				room.addPlayer(player);
				LOG("A new client connected from ", server.event.peer->address.host, 
					" port: ", server.event.peer->address.port, 
					" peerID: ", server.event.peer->incomingPeerID);
				// send back player's ID in the server
				Buffer IDBuffer;
				PlayerIDData data;
				data.id = server.event.peer->incomingPeerID;
				IDBuffer.writeToBuffer(&data, sizeof(PlayerIDData));
				server.send(IDBuffer.getBufferInfo().bufferData, IDBuffer.getBufferInfo().size, server.event.peer);
			}
			else if (server.event.type == ENET_EVENT_TYPE_RECEIVE) {
				room.inputUpdatePlayer(server.event.peer->incomingPeerID, server.event.packet->data, server.event.packet->dataLength);
				enet_packet_destroy(server.event.packet);
				BufferInfo bufferInfo = room.getSnapshot(server.event.peer->incomingPeerID);
				server.send(bufferInfo.bufferData, bufferInfo.size, server.event.peer, ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
			}
			else if (server.event.type == ENET_EVENT_TYPE_DISCONNECT) {
				LOG(server.event.peer->incomingPeerID, " disconnected.");
				server.event.peer->data = NULL;
			}
		}
	}
}

void App::run() {
	running = true;

	std::thread netThred(&App::networkFunction, this);
	netThred.detach();

	while (running) {
		//LOG(clock.getElapsedTime());
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		room.update(clock.getElapsedTime() / 1000.f);
		clock.resetTime();
	}
}


