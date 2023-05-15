#include "App.hpp"

App::App() : server{PORT} {
}

App::~App() {
	for (auto player : players) {
		delete player;
	}
}

void App::networkFunction() {
	std::cout << "networkFunction start." << std::endl;
	while (true) {
		while (enet_host_service(server.serverHost, &server.event, 30) > 0) {
			if (server.event.type == ENET_EVENT_TYPE_CONNECT) {
				Player* player = new Player(server.event.peer, server.event.peer->incomingPeerID);
				players.push_back(player);
				std::cout
					<< "A new client connected from " << server.event.peer->address.host
					<< " port: " << server.event.peer->address.port
					<< " peerID: " << server.event.peer->incomingPeerID
					<< ".\n";
			}
			else if (server.event.type == ENET_EVENT_TYPE_RECEIVE) {
				TransferBuffer recvData;
				memcpy(&recvData, server.event.packet->data, sizeof(TransferBuffer));
				//std::cout << recvData.position.x << " " << recvData.position.y << " " << recvData.rotation << " " << recvData.turrentRotation << std::endl;

				// find and set data 
				for (auto player : players) {
					if (player->ID == server.event.peer->incomingPeerID) {
						player->position = recvData.position;
						player->rotation = recvData.rotation;
						player->turrentRotation = recvData.turrentRotation;
						break;
					}
				}
				enet_packet_destroy(server.event.packet);

				// send back a data 
				for (auto player : players) {
					if (player->ID == server.event.peer->incomingPeerID) {
						TransferBuffer data;
						data.position = player->position;
						data.rotation = player->rotation;
						data.turrentRotation = player->turrentRotation;
						server.send(data, server.event.peer);
						break;
					}
				}
			}
			else if (server.event.type == ENET_EVENT_TYPE_DISCONNECT) {
				std::cout << server.event.peer->incomingPeerID << " disconnected. \n";
				// remove from peers array
				for (uint32_t i = 0; i < players.size(); i++) {
					if (players[i]->ID == server.event.peer->incomingPeerID) {
						players.erase(players.begin() + i);
					}
				}
				// std::cout << "// vector size: " << peers.size() << "\n";
				server.event.peer->data = NULL;
			}
		}
	}
}

void App::run() {
	std::thread netThred(&App::networkFunction, this);
	netThred.detach();
	//networkFunction();

	while(true)
		std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "run." << std::endl;
}


