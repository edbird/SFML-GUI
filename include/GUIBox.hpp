#ifndef GUIBOX_HPP
#define GUIBOX_HPP

// Local headers
#include "GUIBase.hpp"

// SFML headers
#include <SFML/Graphics.hpp>

// C++ headers
#include <iostream>


class GUIBox : public GUIBase
{

    public:

    GUIBox(const int size_x, const int size_y)
        : background(sf::Vector2f(size_x, size_y))
    {
    }


    virtual
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(background);
    }

    virtual
    void event(sf::Event& event, sf::RenderWindow& window)
    {
        std::cout << "event" << std::endl;
    }

    virtual
    void setPosition(const int pos_x, const int pos_y)
    {
        background.setPosition(pos_x, pos_y);
    }

    virtual
    sf::Vector2f getPosition() const
    {
        return background.getPosition();
    }

    virtual
    void setSize(const int width, const int height)
    {
        background.setSize(sf::Vector2f(width, height));
    }

    sf::RectangleShape& getBackground()
    {
        return background;
    }

    protected:

    //sf::intRect background;
    sf::RectangleShape background;
    // background holds background position and background size variables
    // positions of sub objects are relative to the background position

};

#endif // GUIBOX_HPP
