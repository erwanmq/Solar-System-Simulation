#include "Planets.h"
#include "Text.h"
#include <iostream>


Planets::Planets(sf::Color color, double size, double mass, double pos_x, double pos_y, double x_vel, double y_vel,const char* _filepath, bool sun)
    : m_color{ color }, m_size{ size }, m_mass{ mass }, m_pos_x{ pos_x }, m_pos_y{ pos_y }, m_x_vel{ x_vel }, m_y_vel{ y_vel }, m_sun{ sun }
{
    default_value = m_size * m_scale;
    m_texture.loadFromFile("Asserts/Images/light.png");

    m_bright.setTexture(&m_texture);
    m_bright.setFillColor(m_color);

    
    m_texture_planet.loadFromFile(_filepath);

}

Planets::~Planets()
{
}

void Planets::setText(sf::RenderWindow& win, float x, float y)
{
    std::string str_text = std::to_string(m_distanceToSun / AU);
    Text text{ sf::String(std::to_string(m_distanceToSun / AU)), sf::Vector2f(x + m_planet.getRadius(), y), 13};
    text.drawText(win);
}

void Planets::drawLight(sf::RenderWindow& win)
{
    // bigger is the size, bigger is the halo. We multiply it by 10 to have the good one.
    double size_bright = std::exp(m_size * m_scale) * 10; // keep the size of the halo

    /* when we zoom in a planet, the halo disappear gradually.I want to have a halo that disappear a lot at the beginning and gradually at the end.
       The exp function it a good choice for that. I kept the value by default in "default value". We divide it by the current value. At the beginning,
       the quotient is to 1. So we multiply it to 255 to have the correct alphacolor value.
       When the denominator grow, the value decrease exponentially. */
    double alphacolor_bright = std::exp(default_value) / std::exp(m_size * m_scale) * 255;

    // sf::Color take the value superior at 255 at the beginning. (256 = 1, 257 = 2), because of the Uint8 (unsigned int).
    // So when the color is superior at 255, we keep it at 255, the maximum value.
    if (alphacolor_bright > 255)
        alphacolor_bright = 255;

    m_bright.setRadius((float)size_bright);
    m_bright.setOrigin(sf::Vector2f((float)size_bright, (float)size_bright));
    m_bright.setFillColor(sf::Color(m_color.r, m_color.g, m_color.b, static_cast<sf::Uint8>(alphacolor_bright)));

    m_bright.setPosition(m_xWorldCoord, m_yWorldCoord); // put the position on the position of the current planet

    win.draw(m_bright);
}

void Planets::drawPlanet(sf::RenderWindow& win)
{
    // real position of the planet in the space times scale to convert AU to pixels. Origin to the center of window
    m_xWorldCoord = static_cast<float>(m_pos_x * m_scale + winWidth / 2.f);
    m_yWorldCoord = static_cast<float>(m_pos_y * m_scale + winHeight / 2.f);

    float size_planet = static_cast<float>(m_size * m_scale);
    m_planet.setRadius(size_planet);
    m_planet.setOrigin(sf::Vector2f(size_planet, size_planet));

    // drawing the light around the planets
    drawLight(win);

    m_planet.setPosition(sf::Vector2f(m_xWorldCoord, m_yWorldCoord));

    if (m_planet.getRadius() > 5.f)
    {
        m_planet.setFillColor(sf::Color::White);
        m_planet.setTexture(&m_texture_planet);
    }
    else
        m_planet.setTexture(&m_texture_planet);
        
    
    
    for (int i = 0; i < m_orbit.size() - 1; i++)
    {
        m_rectOrbit.setPosition(static_cast<float>(m_orbit[i].x * m_scale + winWidth / 2), static_cast<float>(m_orbit[i].y * m_scale + winHeight / 2));
        m_rectOrbit.setFillColor(sf::Color::White);
        m_rectOrbit.setSize(sf::Vector2f(2, 2));
        win.draw(m_rectOrbit);
    }
    win.draw(m_planet);

    // drawing the text for the distance to the sun
    if (!m_sun)
        setText(win, m_xWorldCoord, m_yWorldCoord);

}

std::tuple<double, double> Planets::attraction(Planets& other)
{
    // store the position of the planet to calculate
    double planet_x = other.m_pos_x;
    double planet_y = other.m_pos_y;

    // distance to this planet in X and Y
    double distance_x = planet_x - m_pos_x;
    double distance_y = planet_y - m_pos_y;

    // Pythagore's theorem for the real distance
    double distance = std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));

    if (other.m_sun)
    {
        m_distanceToSun = distance; // store the distance to the sun
    }


    double force = G * m_mass * other.m_mass / std::pow(distance, 2); // formula to calculate the gravitationnal force
    double theta = std::atan2(distance_y, distance_x); // calculate the angle of the force to the abscisse to calculate the X forces and Y forces

    double force_X = std::cos(theta) * force;
    double force_Y = std::sin(theta) * force;

    return std::make_tuple(force_X, force_Y);
}


void Planets::update_position(std::vector<Planets>& planets)
{
    double total_fx = 0; // store the total forces of all planets on one planet
    double total_fy = 0;

    for (auto& planet : planets)
    {
        if (&planet == this)
            continue; // we don't calculate their own gravitational forces


        std::tuple<double, double> tuple = attraction(planet);
        double fX = std::get<0>(tuple);  // the first value is X forces
        double fY = std::get<1>(tuple);

        total_fx += fX; // we add it to the total forces and continue with others planet
        total_fy += fY;


    }
    m_x_vel += (total_fx / m_mass) * m_timestep; // F = ma => a = F/m. We multiply by timestep to have the velocity until the timestep
    m_y_vel += (total_fy / m_mass) * m_timestep;

    m_pos_x += m_x_vel * m_timestep; // and we add it and multiply it by timestep
    m_pos_y += m_y_vel * m_timestep;

    m_orbit.push_back(sf::Vector2f(static_cast<float>(m_pos_x), static_cast<float>(m_pos_y))); // we add the coordinate of the position
    if (m_orbit.size() > 100)
    {
        m_orbit.erase(m_orbit.begin());
    }

}



const sf::Vector2f Planets::getPosition() const
{
    return sf::Vector2f(m_xWorldCoord, m_yWorldCoord);
}

void Planets::setPosition(int x, int y)
{
    m_pos_x = x;
    m_pos_y = y;
}
