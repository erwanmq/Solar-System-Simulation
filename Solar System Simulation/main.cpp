#include "Planets.h"
#include "Text.h"
#include "Button.h"

#include <iostream>

#include <Windows.h>
#include <limits>


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
    Earth(float distanceFromSun = 1.f, double velocity_y = -29.783e3, double velocity_x = 0, double mass = 5.9742e24)
        : Planets{ sf::Color::Blue, 6378.137e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Mars : public Planets
{
public:
    Mars(float distanceFromSun = 1.524f, double velocity_y = -24.077e3, double velocity_x = 0, double mass = 6.39e23)
        : Planets{ sf::Color::Red, 3396.2e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Mercury : public Planets
{
public:
    Mercury(float distanceFromSun = 0.387f, double velocity_y = -47.4e3, double velocity_x = 0, double mass = 3.30e23)
        : Planets{ sf::Color(128, 64, 0), 4880e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Venus : public Planets
{
public:
    Venus(float distanceFromSun = 0.723f, double velocity_y = -35.02e3, double velocity_x = 0, double mass = 4.8685e24)
        : Planets{ sf::Color(189, 180, 66), 6051.8e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Jupiter : public Planets
{
public:
    Jupiter(float distanceFromSun = 5.4570f, double velocity_y = -13.07e3, double velocity_x = 0, double mass = 1.8982e27)
        : Planets{ sf::Color(187, 142, 102), 71492e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Saturn : public Planets
{
public:
    Saturn(float distanceFromSun = 9.536f, double velocity_y = -9.640e3, double velocity_x = 0, double mass = 5.684e26)
        : Planets{ sf::Color(255, 255, 128), 58232e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Uranus : public Planets
{
    Uranus(float distanceFromSun = 19.191f, double velocity_y = -6.80e3, double velocity_x = 0, double mass = 8.6810e25)
        : Planets{ sf::Color(191, 255, 255), 25559e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Neptune : public Planets
{
    Neptune(float distanceFromSun = 30.07f, double velocity_y = -5.43e3, double velocity_x = 0, double mass = 1.024e26)
        : Planets{ sf::Color(128, 128, 255), 24764e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

struct Pluto : public Planets
{
    Pluto(float distanceFromSun = 49.305f, double velocity_y = -4.743e3, double velocity_x = 0, double mass = 1.303e22)
        : Planets{ sf::Color(128, 128, 128), 1188.3e3, mass, distanceFromSun * AU, 0, velocity_x, velocity_y }
    {}
};

int main()
{
    // window
    const short fps = 60;
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Solar System");
    window.setFramerateLimit(fps); // 60 fps

    sf::View view;
    view.setSize(sf::Vector2f(winWidth, winHeight));

    // background
    sf::Texture texture_background;
    texture_background.loadFromFile("Asserts/Images/space.jpg");
    sf::RectangleShape background;
    background.setTexture(&texture_background);
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(winWidth, winHeight));


    // time elapsed
    long long time_elapsed = 0;
    Text time_elapsed_text{ sf::Vector2f(winWidth - 150, 10), 15 };

    // differents planets
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


    // vector of planets
    std::vector<Planets>* planets = new std::vector<Planets>;
    if (planets == NULL)
    {
        std::cout << "failed" << '\n';
        return EXIT_FAILURE;
    }
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


    SlideButton slidebutton(sf::Color(125, 125, 125), sf::Vector2f(100, 100), sf::Vector2f(30, 30), sf::Vector2f(30, 150));
    // main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float delta = event.mouseWheelScroll.delta;

                if (delta > 0.1f)
                {
                    for (auto& planet : *planets)
                    {
                        planet.m_scale *= 1.1;
                    }
                }
                else if (delta < -0.1f)
                {
                    for (auto& planet : *planets)
                    {
                        planet.m_scale *= 0.9;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (short i = 0; i < planets->size(); i++)
                {
                    if (mousePos.x > planets->at(i).getPosition().x - 30 && mousePos.x < planets->at(i).getPosition().x + 30 && mousePos.y > planets->at(i).getPosition().y - 30 && mousePos.y < planets->at(i).getPosition().y + 30)
                    {

                    }
                }
            }
        }
        time_elapsed += timestep;
        time_elapsed_text.setText(sf::String(std::to_string(time_elapsed / 86400) + " jours"));




        window.clear();
        window.draw(background);
        time_elapsed_text.drawText(window);


        for (auto& planet : *planets)
        {
            planet.update_position(*planets); // calculate their movements
            planet.drawPlanet(window); // draw them
        }

        slidebutton.drawSlideButton(window);
        view.setCenter(planets->at(0).getPosition());
        window.setView(view);

        window.display();

    }


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