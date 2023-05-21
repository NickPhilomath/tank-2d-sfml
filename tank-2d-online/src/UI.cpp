#include "UI.hpp" 

UI::UI(GameFlag* flag, bool* connectionFail) : flag{ flag }, connectionFail{connectionFail} {
    if (!font.loadFromFile("fonts/MouldyCheeseRegular.ttf"))
    {
        throw std::runtime_error("cannot load font");
    }
    // main menu
    {
        sf::Text text;
        text.setString("Username:");
        text.setPosition(0, 50);
        menuTextTitles.push_back(text);
    }
    {
        sf::Text text;
        text.setString("myname");
        text.setPosition(0, 150);
        menuTexts.push_back(text);
    }
    {
        sf::Text text;
        text.setString("Hostname:");
        text.setPosition(0, 250);
        menuTextTitles.push_back(text);
    }
    {
        sf::Text text;
        text.setString("127.0.0.1");
        text.setPosition(0, 350);
        menuTexts.push_back(text);
    }
    {
        sf::Text text;
        text.setString("<- Battle ->");
        text.setPosition(0, 450);
        menuTexts.push_back(text);
    }

    connectionFailText.setString("cannot connect to the server.");
    connectionFailText.setPosition(0, 500);
    connectionFailText.setFont(font);
    connectionFailText.setCharacterSize(25);
    connectionFailText.setFillColor(sf::Color(250, 87, 87));
    moveTo("center", connectionFailText);


    for (int i = 0; i < menuTexts.size(); i++) {
        menuTexts[i].setFont(font); 
        menuTexts[i].setCharacterSize(40);
        menuTexts[i].setFillColor(defaultColor);
        moveTo("center", menuTexts[i]);
    }
    for (int i = 0; i < menuTextTitles.size(); i++) {
        menuTextTitles[i].setFont(font);
        menuTextTitles[i].setCharacterSize(48);
        menuTextTitles[i].setFillColor(defaultColor);
        moveTo("center", menuTextTitles[i]);
    }
}

UI::~UI() {
}

void UI::update() {
    if (*flag == IN_GAME) return;

    static auto t_start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    float elapsed_time = std::chrono::duration<float, std::milli>(now - t_start).count();
    if (elapsed_time > pressAwaitTime) {
        t_start = now;
        isPressed = false;
    }

    if (!isPressed) {
        isPressed = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) currentMenuTextIndex--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) currentMenuTextIndex++;
        if (currentMenuTextIndex < 0) currentMenuTextIndex = menuTexts.size() - 1;
        if (currentMenuTextIndex > menuTexts.size() - 1) currentMenuTextIndex = 0;

        menuTexts[currentMenuTextIndex].setString(menuTexts[currentMenuTextIndex].getString() + getPressedLetter());
        moveTo("center", menuTexts[currentMenuTextIndex]);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            std::string string = menuTexts[currentMenuTextIndex].getString();
            if (string.size() > 0) string.pop_back();
            menuTexts[currentMenuTextIndex].setString(string);
        }
    }

    if (currentMenuTextIndex == menuTexts.size() - 1) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            *connectionFail = false;
            *flag = ON_CONNECT;
        }
        if (*flag == ON_MAIN_MENU) menuTexts[menuTexts.size() - 1].setString("<- Battle ->");
        if (*flag == ON_CONNECT) menuTexts[menuTexts.size() - 1].setString("Connecting...");
    }
}

void UI::render(sf::RenderWindow& window) {
    if (*flag == ON_MAIN_MENU || *flag == ON_CONNECT) {
        for (int i = 0; i < menuTextTitles.size(); i++) {
            menuTextTitles[i].setStyle(sf::Text::Bold);
            window.draw(menuTextTitles[i]);
        }
        for (int i = 0; i < menuTexts.size(); i++) {
            if (currentMenuTextIndex == i) menuTexts[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
            else menuTexts[i].setStyle(sf::Text::Bold);
            window.draw(menuTexts[i]);
        }
        if (*connectionFail) window.draw(connectionFailText);
    }
}

void UI::moveTo(std::string position, sf::Text& text) {
    if (position == "center") {
        text.setPosition(VIEW_WIDTH / 2 - text.getGlobalBounds().width / 2, text.getPosition().y);
    }
}

std::string UI::getPressedLetter() {
    std::string letter = "";

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) letter += 'a';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) letter += 'b';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) letter += 'c';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) letter += 'd';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) letter += 'e';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) letter += 'f';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) letter += 'g';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) letter += 'h';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) letter += 'i';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) letter += 'j';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) letter += 'k';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) letter += 'l';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) letter += 'm';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) letter += 'n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) letter += 'o';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) letter += 'p';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) letter += 'q';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) letter += 'r';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) letter += 's';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) letter += 't';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) letter += 'u';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) letter += 'v';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) letter += 'w';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) letter += 'x';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) letter += 'y';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) letter += 'z';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) letter += '0';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) letter += '1';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) letter += '2';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) letter += '3';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) letter += '4';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) letter += '5';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) letter += '6';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) letter += '7';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) letter += '8';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) letter += '9';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)) letter += '.';

    // yes i know ... i am dumb 

    return letter;
}
