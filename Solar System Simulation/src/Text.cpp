#include "Text.h"

Text::Text()
	: m_position{ sf::Vector2f(0, 0) }, m_size{ 0 }
{
	m_font.loadFromFile("Asserts/Fonts/DejaVuSansMono.ttf");
	m_text.setFont(m_font);
}

Text::Text(sf::Vector2f position, unsigned int size)
	:m_position{ position }, m_size{ size }
{
	m_font.loadFromFile("Asserts/Fonts/DejaVuSansMono.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(size);
}

Text::Text(sf::String text, sf::Vector2f position, unsigned int size)
	:m_position{ position }, m_size{ size }
{
	m_font.loadFromFile("Asserts/Fonts/DejaVuSansMono.ttf");
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setCharacterSize(size);
}

Text::~Text()
{
}

void Text::setText(sf::String text)
{
	m_text.setString(text);
}

void Text::drawText(sf::RenderWindow& win)
{
	m_text.setPosition(m_position);
	win.draw(m_text);
}