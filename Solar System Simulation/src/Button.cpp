#include "Button.h"
#include <iostream>

Button::Button(sf::Color color, sf::Vector2f position, sf::Vector2f size)
	: m_color{ color }, m_position{ position }, m_size{ size }
{
	m_rectangle.setFillColor(m_color);
	m_rectangle.setPosition(m_position);
	m_rectangle.setSize(m_size);
}

void Button::drawButton(sf::RenderWindow& win)
{
	m_rectangle.setPosition(m_position);
	win.draw(m_rectangle);
}

void Button::click()
{
	m_rectangle.setFillColor(sf::Color(m_color.r + 50, m_color.g + 50, m_color.b + 50));
}

void Button::unclick()
{
	m_rectangle.setFillColor(sf::Color(m_color.r, m_color.g, m_color.b));
}

const sf::Vector2f Button::getSizeButton() const
{
	return m_size;
}



SlideButton::SlideButton(sf::Color color, sf::Vector2f position, sf::Vector2f size, sf::Vector2f sizeSlideButton)
	: Button(color, position, size), m_sizeSlideButton{ sizeSlideButton }
{
	m_slideButton.setFillColor(sf::Color(color.r, color.g, color.b, 125));
	m_positionSlideButton = sf::Vector2f(position.x, position.y - sizeSlideButton.y / 2 + m_size.y / 2);
	m_slideButton.setPosition(m_positionSlideButton);
	m_slideButton.setSize(sizeSlideButton);
}

void SlideButton::slide(float _mousePos)
{
	m_position.y = _mousePos - m_size.y / 2.f;
	
	if (m_position.y >= m_positionSlideButton.y + m_sizeSlideButton.y - m_size.y)
		m_position.y = m_positionSlideButton.y + m_sizeSlideButton.y - m_size.y;
	else if (m_position.y <= m_positionSlideButton.y)
		m_position.y = m_positionSlideButton.y;

}

void SlideButton::drawSlideButton(sf::RenderWindow& win)
{
	m_slideButton.setPosition(m_positionSlideButton);
	win.draw(m_slideButton);
	drawButton(win);
}

const sf::Vector2f SlideButton::getPosition() const
{
	sf::Vector2f return_pos = sf::Vector2f(m_position.x, m_position.y - m_sizeSlideButton.y / 2.f);
	return return_pos;
}
const sf::Vector2f SlideButton::getSize() const
{
	return m_sizeSlideButton;
}

const sf::Vector2f SlideButton::getRelativePosition() const
{
	sf::Vector2f return_pos = sf::Vector2f(0, m_position.y - m_slideButton.getPosition().y);
	return return_pos;
}

void SlideButton::setPosition(sf::Vector2f _position, sf::Vector2f _positionRelative)
{
	m_positionSlideButton = _position;
	m_position = sf::Vector2f(_position.x, _position.y + _positionRelative.y);
}


