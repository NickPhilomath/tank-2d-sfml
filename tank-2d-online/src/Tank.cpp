#include "Tank.hpp"

Tank::Tank(uint8_t group) :
    acceleration{ 10.f }, maxSpeed{ 100.f }, rotationSpeed{ 40.f }, group{ group } {
    // creating shape 
    body.setPointCount(4);
    body.setPoint(0, sf::Vector2f(30.f, 20.f));
    body.setPoint(1, sf::Vector2f(30.f, -20.f));
    body.setPoint(2, sf::Vector2f(-30.f, -20.f));
    body.setPoint(3, sf::Vector2f(-30.f, 20.f));
    body.setFillColor(sf::Color(0, 0, 0, 0));
    body.setOutlineThickness(2);
    turrent.setRadius(15.f);
    turrent.setOutlineThickness(2);
    turrent.setFillColor(sf::Color(0, 0, 0, 0));
    turrent.setOrigin(15, 15);
    gun.setSize(sf::Vector2f(50, 4));
    gun.setOrigin(sf::Vector2f(-13, 2));

    if (group == Tank::ALLIE) {
        body.setOutlineColor(sf::Color::Green);
        turrent.setOutlineColor(sf::Color::Green);
        gun.setFillColor(sf::Color::Green);
    }
    else if (group == Tank::ENAMY) {
        body.setOutlineColor(sf::Color::Red);
        turrent.setOutlineColor(sf::Color::Red);
        gun.setFillColor(sf::Color::Red);
    }
    else {
        body.setOutlineColor(sf::Color::White);
        turrent.setOutlineColor(sf::Color::White);
        gun.setFillColor(sf::Color::White);
    }

}

Tank::~Tank() {
}

void Tank::update(float deltaTime) {
    int move = 0, rotate = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotate = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotate = -1;

    setPosition(sf::Vector2f(position.x + rotate, position.y + move));
}

void Tank::render(sf::RenderWindow& target) {
    target.draw(body);
    target.draw(turrent);
    target.draw(gun);
}

//void Tank::onEvent(const sf::Event& event) {
//}

void Tank::setPosition(sf::Vector2f pos) {
    position = pos;
    body.setPosition(pos);
    turrent.setPosition(pos);
    gun.setPosition(pos);
}

sf::Vector2f Tank::getPosition() const {
    return position;
}
