#pragma once
#include <SFML/Graphics.hpp>
class Button
{
private:
	sf::RectangleShape m_rectangle;
	sf::Color m_color;

	sf::Vector2f m_size;
	sf::Vector2f m_position;

public:
	Button(sf::Color color, sf::Vector2f position, sf::Vector2f size);

	void drawButton(sf::RenderWindow& win);
};

class SlideButton : protected Button
{
private:
	sf::Vector2f m_sizeSlideButton;
	sf::RectangleShape m_slideButton;

public:
	SlideButton(sf::Color color, sf::Vector2f position, sf::Vector2f size, sf::Vector2f sizeSlideButton);
	void drawSlideButton(sf::RenderWindow& win);
};