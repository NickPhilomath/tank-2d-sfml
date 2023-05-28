#include "Map.hpp"

Map::Map() {
    if (!t_ground.loadFromFile("assets/ground.png")) {
        throw std::runtime_error("cannot load asset");
    }

    mapBorder.setSize(sf::Vector2f(MapLength, MapWidth));
    mapBorder.setOutlineThickness(10);
    mapBorder.setFillColor(sf::Color::Transparent);
    mapBorder.setOutlineColor(sf::Color::Red);
}

Map::~Map() {
}

void Map::update(Camera& camera) {
    grounds.clear();

    sf::Vector2f cameraSize = camera.cameraView.getSize();
    int viewWidthHalf = cameraSize.x / 2 + GROUND_L;
    int viewHeightHalf = cameraSize.y / 2 + GROUND_W;

    cameraPosition = camera.viewTarget->position * RATIO;

    sf::Vector2i start_block_index = sf::Vector2i((cameraPosition.x - viewWidthHalf) / GROUND_L, (cameraPosition.y - viewHeightHalf) / GROUND_W);
    sf::Vector2i end_block_index = sf::Vector2i((cameraPosition.x + viewWidthHalf) / GROUND_L, (cameraPosition.y + viewHeightHalf) / GROUND_W);

    for (int i = start_block_index.x; i < end_block_index.x; i++) {
        for (int j = start_block_index.y; j < end_block_index.y; j++) {
            sf::RectangleShape ground;
            ground.setTexture(&t_ground);
            ground.setTextureRect(sf::IntRect(0, 0, GROUND_L, GROUND_W));
            ground.setSize(sf::Vector2f(GROUND_L, GROUND_W));
            ground.setPosition(sf::Vector2f(i * GROUND_L, j * GROUND_W));
            grounds.push_back(ground);
        }
    }
    
}

void Map::render(sf::RenderWindow& window) {

    for (auto ground : grounds) {
        window.draw(ground);

    }
    window.draw(mapBorder);
}
