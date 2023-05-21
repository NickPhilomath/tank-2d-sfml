#pragma once

#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "clientConstants.hpp"

class UI {
public:
	UI(GameFlag* flag, bool* connectionFail);
	~UI();

	void update();
	void render(sf::RenderWindow& window);

private:
	void moveTo(std::string position, sf::Text& text);
	std::string getPressedLetter();

	bool isPressed = false;
	const float pressAwaitTime = 200.f;

	GameFlag* flag;
	bool* connectionFail;
	sf::Font font;
	sf::Color defaultColor{ 66, 135, 245 };

	// all about text -_-
	std::vector<sf::Text> menuTextTitles;
	std::vector<sf::Text> menuTexts;
	sf::Text battleText;
	sf::Text connectingText;
	sf::Text connectionFailText;
	int currentMenuTextIndex = 0;
};