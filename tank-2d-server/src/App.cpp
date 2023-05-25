#include "App.hpp"

App::App() : server{PORT} {
}

App::~App() {
}

void App::networkFunction() {
	LOG("networkFunction start.");
	while (true) {
		while (enet_host_service(server.serverHost, &server.event, 30) > 0) {
			if (server.event.type == ENET_EVENT_TYPE_CONNECT) {
				Player* player = new Player(server.event.peer, server.event.peer->incomingPeerID);
				room.addPlayer(player);
				LOG("A new client connected from ", server.event.peer->address.host, 
					" port: ", server.event.peer->address.port, 
					" peerID: ", server.event.peer->incomingPeerID,".\n");
				// send back player's ID in the server
				Buffer IDBuffer;
				PlayerIDData data;
				data.id = server.event.peer->incomingPeerID;
				IDBuffer.writeToBuffer(&data, sizeof(PlayerIDData));
				BufferInfo info = IDBuffer.getBufferInfo();
				server.send(info.bufferData, info.size, server.event.peer);
			}
			else if (server.event.type == ENET_EVENT_TYPE_RECEIVE) {
				room.inputUpdatePlayer(server.event.peer->incomingPeerID, server.event.packet->data);
				enet_packet_destroy(server.event.packet);
				BufferInfo bufferInfo = room.getSnapshot(server.event.peer->incomingPeerID);
				server.send(bufferInfo.bufferData, bufferInfo.size, server.event.peer);
				// server.send((static_cast<void *>(snapshot.data())), snapshot.size(), server.event.peer);
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
	//networkFunction();

	while (running) {
		static auto t_start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		auto t_end = std::chrono::high_resolution_clock::now();
		float elapsed_time = std::chrono::duration<float, std::milli>(t_end - t_start).count();
		t_start = t_end;

		room.update(elapsed_time / 1000.f);
	}
}


