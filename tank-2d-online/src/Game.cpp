#include "Game.hpp"

Game::Game() {
    playerTank = new Tank(Tank::PLAYER);
    playerTank->setPosition(sf::Vector2f(300, 300));
    {
        Tank* tank = new Tank(Tank::ENAMY);
        tank->setPosition(sf::Vector2f(50, 50));
        tanks.push_back(tank);
    }
    {
        Tank* tank = new Tank(Tank::ALLIE);
        tank->setPosition(sf::Vector2f(250, 150));
        tanks.push_back(tank);
    }
}

Game::~Game() {
    
}

void Game::run() {
	createWindow();

    sf::Clock clock;

    sf::ConvexShape mapBorder;
    mapBorder.setPointCount(4);
    mapBorder.setPoint(0, sf::Vector2f(0, 0));
    mapBorder.setPoint(1, sf::Vector2f(1000, 0));
    mapBorder.setPoint(2, sf::Vector2f(1000, 1000));
    mapBorder.setPoint(3, sf::Vector2f(0, 1000));
    mapBorder.setOutlineThickness(2);
    mapBorder.setFillColor(sf::Color::Transparent);
    mapBorder.setOutlineColor(sf::Color::Blue);

    while (window.isOpen()) {
        // get events 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            for (auto tank : tanks) {
                //tank->onEvent(event);
            }
        }
        // update
        //for (auto tank : tanks) {
        //    tank->update(clock.restart().asSeconds());
        //}
        playerTank->update(clock.restart().asSeconds());

        sf::View view(sf::FloatRect(playerTank->getPosition().x - VIEW_WIDTH / 2, playerTank->getPosition().y - VIEW_HEIGHT / 2, VIEW_WIDTH, VIEW_HEIGHT));
        window.setView(view);

        // render
        window.clear();
        playerTank->render(window);
        for (auto tank : tanks) {
            tank->render(window);
        }
        window.draw(mapBorder);
        window.display();
    }
}

void Game::createWindow() {
	window.create(sf::VideoMode(APP_WIDTH, APP_HEIGHT), APP_TITLE, sf::Style::Close);
}
