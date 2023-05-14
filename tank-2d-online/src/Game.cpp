#include "Game.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


Game::Game() {
    TankProps globalProps{};

    playerTank = new Tank(G_PLAYER, globalProps);
    playerTank->setPosition(sf::Vector2f(300, 300));
    {
        Tank* tank = new Tank(G_ENAMY, globalProps);
        tank->setPosition(sf::Vector2f(50, 50));
        tanks.push_back(tank);
    }
    {
        Tank* tank = new Tank(Group::G_ALLIE, globalProps);
        tank->setPosition(sf::Vector2f(250, 150));
        tanks.push_back(tank);
    }
}

Game::~Game() {
    delete playerTank;
    for (auto tank : tanks) {
        delete tank;
    }
}

void Game::createWindow() {
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), APP_TITLE, sf::Style::Close);
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

    Camera camera{VIEW_WIDTH, VIEW_HEIGHT};
    camera.viewTarget = playerTank;
    //sf::View view(sf::FloatRect(playerTank->getPosition().x - VIEW_WIDTH / 2, playerTank->getPosition().y - VIEW_HEIGHT / 2, VIEW_WIDTH, VIEW_HEIGHT));

    //window.setMouseCursorVisible(false);

    while (window.isOpen()) {
        // get events 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            camera.onEvent(event);
        }

        // update
        float DT = clock.restart().asSeconds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        playerTank->update(DT, mousePos);
        
        camera.update(DT);
        window.setView(camera.cameraView);

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
