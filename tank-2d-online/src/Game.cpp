#include "Game.hpp"

#ifdef _DEBUG
#include <iostream>
#include <chrono>
#endif // _DEBUG

Game::Game() :
    client{"127.0.0.1", 1234} 
{
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
    client.connected = false;

    delete playerTank;
    for (auto tank : tanks) {
        delete tank;
    }
}

void Game::createWindow() {
    window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), APP_TITLE, sf::Style::Close);
}

void Game::networkFunction() {

    client.connect();
    while (client.connected) {
        client.send(playerTank->getInput(), sizeof(PlayerInput));
        auto t_start = std::chrono::high_resolution_clock::now(); // *
        client.recieve(&snapShot);
        snapshotUpdate();

        auto t_end = std::chrono::high_resolution_clock::now(); // *
        double elapsed_time = std::chrono::duration<double, std::milli>(t_end - t_start).count(); // *
        //std::cout << elapsed_time << std::endl;
    }
    client.disconnect();
}

void Game::snapshotUpdate() {
    playerTank->setPosition(snapShot.position);
    playerTank->setRotation(snapShot.rotation);
    playerTank->setTurrentRotation(snapShot.turrentRotation);
    LOG(snapShot.rotation, ' ', snapShot.turrentRotation);
}

void Game::run() {
    std::thread netThread(&Game::networkFunction, this);
    netThread.detach();

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
            if (event.type == sf::Event::Closed) {
                window.close();
                client.connected = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(110));
            }

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
