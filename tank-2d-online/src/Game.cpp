#include "Game.hpp"

Game::Game() :
    client{"127.0.0.1", 1234},
    ui{&gameFlag, &connectionFail}
{
    playerTank = new Tank(T_UNKNOWN, -1);
    playerTank->setPosition(sf::Vector2f(300, 300));

    mapBorder.setPointCount(4);
    mapBorder.setPoint(0, sf::Vector2f(0, 0));
    mapBorder.setPoint(1, sf::Vector2f(1000, 0));
    mapBorder.setPoint(2, sf::Vector2f(1000, 1000));
    mapBorder.setPoint(3, sf::Vector2f(0, 1000));
    mapBorder.setOutlineThickness(2);
    mapBorder.setFillColor(sf::Color::Transparent);
    mapBorder.setOutlineColor(sf::Color::Blue);

    createWindow();
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
    net_fun_start:
    while(gameFlag == ON_MAIN_MENU)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    client.connect();
    if (client.connected) { gameFlag = IN_GAME; }
    else { gameFlag = ON_MAIN_MENU; connectionFail = true; goto net_fun_start; }
    // get player's ID in the server room
    client.recieve(snapshot);
    snapshotUpdate();

    while (client.connected) {
        client.send(playerTank->getInput(), sizeof(PlayerInput), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        client.recieve(snapshot);
        snapshotUpdate();
    }
    client.disconnect();
}

void Game::snapshotUpdate() {
    int header;
    snapshot.startReading();

    while (!snapshot.autoReadIsDone()) {
        snapshot.autoReadHeader(&header);
        // we must handle all type of data
        if (header == H_PLAYER_ID) {
            PlayerIDData data;
            snapshot.autoReadFromBuffer(&data, sizeof(PlayerIDData));
            playerTank->ID = data.id;
            //LOG("player ID: ", data.id);
        }
        else if (header == H_GAME_STAGE) {
            GameStageData data;
            snapshot.autoReadFromBuffer(&data, sizeof(GameStageData));
        }
        else if (header == H_PLAYER_UPDATE) {
            PlayerUpdateData data;
            snapshot.autoReadFromBuffer(&data, sizeof(PlayerUpdateData));

            updatePlayer(data);
        }
    }
}

void Game::updatePlayer(PlayerUpdateData& data) {
    if (data.ID == playerTank->ID) {
        playerTank->setPosition(data.position * RATIO);
        playerTank->setRotation(data.rotation);
        playerTank->setTurrentRotation(data.turrentRotation);
    }
    else {
        bool found = false;
        for (auto tank : tanks) {
            if (tank->ID == data.ID) {
                tank->setPosition(data.position * RATIO);
                tank->setRotation(data.rotation);
                tank->setTurrentRotation(data.turrentRotation);
                found = true;
                break;
            }
        }
        if (!found) {
            Tank* tank = new Tank(T_FIRST, data.ID);
            tank->setPosition(data.position * RATIO);
            tanks.push_back(tank);
        }
    }
}

void Game::run() {
    std::thread netThread(&Game::networkFunction, this);
    netThread.detach();

    camera.viewTarget = playerTank;
    //window.setMouseCursorVisible(false);

    while (window.isOpen()) {
        Timer timer;

        // get events 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                client.connected = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(110));
            }
            if (event.type == sf::Event::GainedFocus) windowOnFocus = true;
            if (event.type == sf::Event::LostFocus) windowOnFocus = false;

            camera.onEvent(event);
        }

        // update
        float DT = clock.restart().asSeconds();
        if (gameFlag == IN_GAME && windowOnFocus) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            playerTank->update(DT, mousePos);
        
            camera.update(DT);
            window.setView(camera.cameraView);
        }
        ui.update();

        // render
        if (gameFlag == IN_GAME) {
            window.clear(sf::Color(12, 173, 0));
        }
        else {
            window.clear(sf::Color(35, 89, 31));
        }

        if (gameFlag == IN_GAME) {
            playerTank->render(window);
            for (auto tank : tanks) {
                tank->render(window);
            }
            window.draw(mapBorder);
        }

        ui.render(window);
        window.display();

        // delay
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

        //LOG(timer.getElapsedTime());
    }
}
