#include "Player.hpp"

Player::Player(ENetPeer* peer, uint32_t id) :
	peer{ peer }, ID{id} {
}

Player::~Player() {
}
