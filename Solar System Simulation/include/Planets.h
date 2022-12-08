#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <tuple>
#include <cmath>
#include "Values.h"

// class that represents a planet. No characteristics by default, we have to send it
class Planets
{
private:

    sf::CircleShape m_planet;
    sf::Color m_color;

    sf::Texture m_texture;
    sf::CircleShape m_bright;


    double m_size;

    double m_mass;
    double m_pos_x;
    double m_pos_y;
    float m_xWorldCoord = 0.f;
    float m_yWorldCoord = 0.f;

    double m_distanceToSun = 0;
    //sf::Vector2f m_distanceToSunWindow = sf::Vector2f(0, 0);
    double m_x_vel = 0;
    double m_y_vel = 0;


    bool m_sun;

    double default_value;

    sf::RectangleShape m_rectOrbit;
    std::vector<sf::Vector2f> m_orbit{}; // vector that stores the trajectory to represent the orbit
    sf::Text m_text; // text for display the distance to sun

public:
    double m_scale = 250 / AU; // 250 pixels for one AU

public:


    Planets(sf::Color color, double size, double mass, double pos_x, double pos_y, double x_vel, double y_vel, bool sun = false);

    ~Planets();


    void drawPlanet(sf::RenderWindow& win);
    void setText(sf::RenderWindow& win, float x, float y);
    void drawLight(sf::RenderWindow& win);

    // function for calculate the attraction of each planet. Return the force in X and Y
    std::tuple<double, double> attraction(Planets& other);

    void update_position(std::vector<Planets>& planets);


    const sf::Vector2f getPosition() const;

};