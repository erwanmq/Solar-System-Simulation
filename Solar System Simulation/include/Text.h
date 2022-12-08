#pragma once
#include <SFML/Graphics.hpp>

class Text
{
private:
	sf::Font m_font;
	sf::Text m_text;

	sf::Vector2f m_position;
	unsigned int m_size;

public:
	Text(); // default
	Text(sf::Vector2f position, unsigned int size);
	Text(sf::String text, sf::Vector2f position, unsigned int size);

	~Text();

	void setText(sf::String text);

	void drawText(sf::RenderWindow& win);


};