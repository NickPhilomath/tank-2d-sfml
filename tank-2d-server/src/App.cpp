#include "App.hpp"

App::App() : server{PORT} {
}

App::~App() {
	for (auto player : entities) {
		delete player;
	}
}

void App::networkFunction() {
	LOG("networkFunction start.");
	while (true) {
		while (enet_host_service(server.serverHost, &server.event, 30) > 0) {
			if (server.event.type == ENET_EVENT_TYPE_CONNECT) {
				Entity* entity = new Entity(server.event.peer, server.event.peer->incomingPeerID);
				entities.push_back(entity);
				LOG("A new client connected from ", server.event.peer->address.host, 
					" port: ", server.event.peer->address.port, 
					" peerID: ", server.event.peer->incomingPeerID,".\n");
			}
			else if (server.event.type == ENET_EVENT_TYPE_RECEIVE) {
				PlayerInput inputData;
				memcpy(&inputData, server.event.packet->data, sizeof(PlayerInput));
				LOG(inputData.move, " ", inputData.rotate, " ", inputData.turrentRotate);

				// find and set data 
				for (auto entity : entities) {
					if (entity->ID == server.event.peer->incomingPeerID) {
						entity->inputUpdate(inputData);
						break;
					}
				}
				enet_packet_destroy(server.event.packet);

				// send back a data 
				for (auto entity : entities) {
					if (entity->ID == server.event.peer->incomingPeerID) {
						TransferBuffer data;
						data.position = entity->position;
						data.rotation = entity->rotation;
						data.turrentRotation = entity->turrentRotation;
						server.send(data, server.event.peer);
						break;
					}
				}
			}
			else if (server.event.type == ENET_EVENT_TYPE_DISCONNECT) {
				std::cout << server.event.peer->incomingPeerID << " disconnected. " << entities.size() << " players \n";
				// remove from peers array
				for (uint32_t i = 0; i < entities.size(); i++) {
					if (entities[i]->ID == server.event.peer->incomingPeerID) {
						entities.erase(entities.begin() + i);
					}
				}
				// std::cout << "// vector size: " << peers.size() << "\n";
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

		for (auto entity : entities) {
			entity->update(elapsed_time / 1000.f);
		}
		
	}
}


