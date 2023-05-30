#include "Game.hpp"

Game::Game() :
    client{"127.0.0.1", 1234},
    ui{&gameFlag, &connectionFail}
{
    playerTank = new Tank(T_UNKNOWN, -1);
    playerTank->position = sf::Vector2f(0, 0);

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
        client.send(&playerTank->inputServer, sizeof(PlayerInput), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        if (client.recieve(snapshot)) {
            snapshotUpdate();
        }

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
        //LOG(playerTank->position.x - data.position.x);
        playerTank->speed = data.speed;
        playerTank->position = data.position;
        playerTank->rotation = data.rotation;
        playerTank->turrentRotation = data.turrentRotation;
        playerTank->acceleration_stage = data.accelerationStage;
        playerTank->input = data.playerInput;
    }
    else {
        bool found = false;
        for (auto tank : tanks) {
            if (tank->ID == data.ID) {
                tank->speed = data.speed;
                tank->position = data.position;
                tank->rotation = data.rotation;
                tank->turrentRotation = data.turrentRotation;
                tank->acceleration_stage = data.accelerationStage;
                tank->input = data.playerInput;
                found = true;
                break;
            }
        }
        if (!found) {
            Tank* tank = new Tank(T_FIRST, data.ID);
            tank->position = data.position;
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
        float DT = clock.getElapsedTime() / 1000.f; clock.resetTime();

        if (gameFlag == IN_GAME) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            camera.update(DT);
            gameMap.update(camera);
            playerTank->update(DT, mousePos, windowOnFocus);
            for (auto tank : tanks) {
                tank->update(DT, mousePos, windowOnFocus);
            }
            window.setView(camera.cameraView);
        }
        ui.update();

        // render
        window.clear(sf::Color(35, 89, 31));

        if (gameFlag == IN_GAME) {
            gameMap.render(window);
            playerTank->render(window);
            for (auto tank : tanks) {
                tank->render(window);
            }
        }

        ui.render(window);
        window.display();

        // delay
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

    }
}
