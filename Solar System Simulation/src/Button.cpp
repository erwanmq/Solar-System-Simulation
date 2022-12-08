#include "Button.h"

Button::Button(sf::Color color, sf::Vector2f position, sf::Vector2f size)
	: m_color{ color }, m_position{ position }, m_size{ size }
{
	m_rectangle.setFillColor(m_color);
	m_rectangle.setPosition(m_position);
	m_rectangle.setSize(m_size);
}

void Button::drawButton(sf::RenderWindow& win)
{
	win.draw(m_rectangle);
}

SlideButton::SlideButton(sf::Color color, sf::Vector2f position, sf::Vector2f size, sf::Vector2f sizeSlideButton)
	: Button(color, position, size), m_sizeSlideButton{ sizeSlideButton }
{
	m_slideButton.setFillColor(sf::Color(color.r, color.g, color.b, 125));
	m_slideButton.setPosition(position.x, sizeSlideButton.y / 2 - position.y / 2 + size.y / 2);
	m_slideButton.setSize(sizeSlideButton);
}

void SlideButton::drawSlideButton(sf::RenderWindow& win)
{
	win.draw(m_slideButton);
	drawButton(win);
}