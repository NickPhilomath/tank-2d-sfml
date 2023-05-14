#include "Player.hpp"

Player::Player(ENetPeer* peer) : 
	peer{ peer }, ID{peer->incomingPeerID} {
}

Player::~Player()
{
}
