#pragma once
#include <SFML/Graphics.hpp>
class Button
{
private:
	sf::RectangleShape m_rectangle;
	sf::Color m_color;

	
protected:
	sf::Vector2f m_size;
	sf::Vector2f m_position;

public:
	Button(sf::Color color, sf::Vector2f position, sf::Vector2f size);

	void drawButton(sf::RenderWindow& win);

	void click();
	void unclick();
	const sf::Vector2f getPosition() const;
	const sf::Vector2f getSize() const;
};

class SlideButton : public Button
{
private:
	sf::Vector2f m_sizeSlideButton;
	sf::RectangleShape m_slideButton;

	sf::Vector2f m_positionSlideButton;

public:
	SlideButton(sf::Color color, sf::Vector2f position, sf::Vector2f size, sf::Vector2f sizeSlideButton);
	void slide(float _mousePos);
	void drawSlideButton(sf::RenderWindow& win);

	const sf::Vector2f getPosition() const;
	const sf::Vector2f getSize() const;

};