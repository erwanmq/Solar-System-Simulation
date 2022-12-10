#include "include/Planets.h"
#include "include/Text.h"
#include "include/Button.h"

#include <iostream>

#include <Windows.h>


// structs that represent each known planet with their characteristics
struct Sun : public Planets
{
public:
    Sun() : Planets{ sf::Color::Yellow, 696700e3, 1.98892e30, 0, 0, 0, 0, true }
    {}
};

struct Earth : public Planets
{
public:
    Earth()
        : Planets{ sf::Color::Blue, 6378.137e3, 5.9742e24, 1.f * AU, 0, 0, -29.783e3 }
    {}
};

struct Mars : public Planets
{
public:
    Mars()
        : Planets{ sf::Color::Red, 3396.2e3, 6.39e23, 1.524f * AU, 0, 0, -24.077e3 }
    {}
};

struct Mercury : public Planets
{
public:
    Mercury()
        : Planets{ sf::Color(128, 64, 0), 2439.7e3, 3.30e23, 0.387f * AU, 0, 0, -47.4e3 }
    {}
};

struct Venus : public Planets
{
public:
    Venus()
        : Planets{ sf::Color(189, 180, 66), 6051.8e3, 4.8685e24, 0.723f * AU, 0, 0, -35.02e3 }
    {}
};

struct Jupiter : public Planets
{
public:
    Jupiter()
        : Planets{ sf::Color(187, 142, 102), 71492e3, 1.8982e27, 5.4570f * AU, 0, 0, -13.07e3 }
    {}
};

struct Saturn : public Planets
{
public:
    Saturn()
        : Planets{ sf::Color(255, 255, 128), 58232e3, 5.684e26, 9.536f * AU, 0, 0, -9.640e3 }
    {}
};

struct Uranus : public Planets
{
public:
    Uranus()
        : Planets{ sf::Color(191, 255, 255), 25559e3, 8.6810e25, 19.191f * AU, 0, 0, -6.80e3 }
    {}
};

struct Neptune : public Planets
{ 
public:
    Neptune()
        : Planets{ sf::Color(128, 128, 255), 24764e3, 1.024e26, 30.07f * AU, 0, 0, -5.43e3 }
    {}
};

struct Pluto : public Planets
{
public:
    Pluto()
        : Planets{ sf::Color(128, 128, 128), 1188.3e3, 1.303e22, 49.305f * AU, 0, 0, -4.743e3 }
    {}
};

void setBackground(sf::RectangleShape& _rect, sf::Texture& _texture)
{
    _texture.loadFromFile("Asserts/Images/space.jpg");
    
    _rect.setTexture(&_texture);
    _rect.setOrigin(sf::Vector2f(winWidth / 2.f, winHeight / 2.f));
    _rect.setPosition(sf::Vector2f(winWidth / 2.f, winHeight / 2.f));
    _rect.setSize(sf::Vector2f(winWidth, winHeight));
}

void zoomAndDezoom(std::vector<Planets>& _planets, float _delta)
{
    // change the scale of all planets
    if (_delta > 0.1f)
    {
        for (auto& planet : _planets)
        {
            planet.m_scale *= 1.1;
        }
    }
    else if (_delta < -0.1f)
    {
        for (auto& planet : _planets)
        {
            planet.m_scale *= 0.9;
        }
    }
}

void checkSlideButtonPressed(sf::RenderWindow& _win, SlideButton& _button, bool& _clicked, std::vector<Planets>& _planets)
{
    // store the position of the mouse and the slide bar ////////////////////////////////////////////////////////////////////
    sf::Vector2f mousePos = _win.mapPixelToCoords(sf::Mouse::getPosition(_win));
    sf::Vector2f upperLeftSlideButton = _button.getPosition();
    sf::Vector2f lowerRightSlideButton = _button.getPosition() + _button.getSize();
    if (mousePos.x > upperLeftSlideButton.x && mousePos.x < lowerRightSlideButton.x && mousePos.y < lowerRightSlideButton.y && mousePos.y > upperLeftSlideButton.y && !_clicked)
    {
        _button.click();
        _clicked = true;
    }
    // can move the button even if the cursor is not at their x and y coordinates ////////////////////////////////////////////////////////////////////
    else if (_clicked)
    {
        _button.slide(mousePos.y);
        float delta = std::abs(_button.getRelativePosition().y - _button.getSize().y + _button.getSizeButton().y);
        for (Planets& planet : _planets)
        {
            planet.m_timestep = 3600 * delta * 0.8;
        }
    }
}

int main()
{ 
    // window ////////////////////////////////////////////////////////////////////
    constexpr __int8 fps = 60;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Solar System");
    window.setFramerateLimit(fps); // 60 fps

    // view ////////////////////////////////////////////////////////////////////
    sf::View view;
    view.setSize(sf::Vector2f(winWidth, winHeight));
    short index_planet_view = 0;

    // background ////////////////////////////////////////////////////////////////////
    sf::RectangleShape background;
    sf::Texture texture_background;
    setBackground(background, texture_background);


    // time elapsed ////////////////////////////////////////////////////////////////////
    unsigned long long time_elapsed = 0;
    Text time_elapsed_text{ sf::Vector2f(winWidth - 150, 10), 15 };


    // differents planets ////////////////////////////////////////////////////////////////////
    Sun* sun = new Sun;
    Earth* earth = new Earth;
    Mars* mars = new Mars;
    Mercury* mercury = new Mercury;
    Venus* venus = new Venus;
    Jupiter* jupiter = new Jupiter;
    Saturn* saturn = new Saturn;
    Uranus* uranus = new Uranus;
    Neptune* neptune = new Neptune;
    Pluto* pluto = new Pluto;


    // vector of planets ////////////////////////////////////////////////////////////////////
    std::vector<Planets>* planets = new std::vector<Planets>;
    
    planets->push_back(*sun);
    planets->push_back(*mercury);
    planets->push_back(*venus);
    planets->push_back(*earth);
    planets->push_back(*mars);
    planets->push_back(*jupiter);
    planets->push_back(*saturn);
    planets->push_back(*uranus);
    planets->push_back(*neptune);
    planets->push_back(*pluto);
    

    // Buttons ////////////////////////////////////////////////////////////////////
    SlideButton slidebutton(sf::Color(125, 125, 125), sf::Vector2f(100, 100), sf::Vector2f(30, 30),  sf::Vector2f(30, 150));

    bool clicked = false;
    // main game loop ////////////////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // close event ////////////////////////////////////////////////////////////////////
            if (event.type == sf::Event::Closed)
                window.close();

            // zoom/dezoom event ////////////////////////////////////////////////////////////////////
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float delta = event.mouseWheelScroll.delta;
                zoomAndDezoom(*planets, delta);
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // check if the user click on the slide button ////////////////////////////////////////////////////////////////////
                checkSlideButtonPressed(window, slidebutton, clicked, *planets);
            }
            
            if (event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // focus the view on the planet with mouse button ////////////////////////////////////////////////////////////////////
                for (short i = 0; i < planets->size(); i++)
                {
                    if (mousePos.x > planets->at(i).getPosition().x - 30 && mousePos.x < planets->at(i).getPosition().x + 30 && mousePos.y > planets->at(i).getPosition().y - 30 && mousePos.y < planets->at(i).getPosition().y + 30)
                    {
                        index_planet_view = i;
                    }
                }
                // release the button ////////////////////////////////////////////////////////////////////
                if (event.mouseButton.button == sf::Mouse::Left && clicked)
                {
                    slidebutton.unclick();
                    clicked = false;
                }
            }
        }
        
        window.clear();

        // draw the background ////////////////////////////////////////////////////////////////////
        background.setPosition(planets->at(index_planet_view).getPosition());
        window.draw(background);
        

        // move and draw the planets ////////////////////////////////////////////////////////////////////
        for (Planets& planet : *planets)
        {
            planet.update_position(*planets); // calculate their movements
            planet.drawPlanet(window); // draw them
            
        }

        // add the time and draw it ////////////////////////////////////////////////////////////////////
        time_elapsed += planets->at(0).m_timestep;
        time_elapsed_text.setText(sf::String(std::to_string(time_elapsed / 86400) + " days"));
        time_elapsed_text.setPosition(window.getView().getCenter() + sf::Vector2f(winWidth / 2.f - 150, -winHeight / 2.f + 10));
        time_elapsed_text.drawText(window);

        // set the view at the center of the planet we're looking for ////////////////////////////////////////////////////////////////////
        view.setCenter(planets->at(index_planet_view).getPosition());
        window.setView(view);

        // draw buttons ////////////////////////////////////////////////////////////////////
        sf::Vector2f positionToTheWindow = window.getView().getCenter() + sf::Vector2f(-winWidth / 2.f + 100, -winHeight / 2.f + 100);
        slidebutton.setPosition(positionToTheWindow, slidebutton.getRelativePosition());
        slidebutton.drawSlideButton(window);
        

        // display window ////////////////////////////////////////////////////////////////////
        window.display();

    }

    // delete all planets ////////////////////////////////////////////////////////////////////
    delete planets;
    delete sun;
    delete earth;
    delete mars;
    delete mercury;
    delete venus;
    delete jupiter;
    delete saturn;
    delete uranus;
    delete neptune;
    delete pluto;

    return 0;
}