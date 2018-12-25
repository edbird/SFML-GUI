#ifndef GUIBASE_HPP
#define GUIBASE_HPP

// SDL headers
#include <SFML/Graphics.hpp>

class GUIBase : public sf::Drawable
{

    public:

    GUIBase()
    {
    }

    virtual
    ~GUIBase() = 0;

    /*
    virtual
    void Draw(sf::RenderWindow& window) const
    {
        window.Draw(background);
    };
    */

    virtual
    void event(sf::Event& event, sf::RenderWindow& window) = 0;

    /*
    virtual
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(background);
    }
    */

    protected:




};

#endif // GUIBASE_HPP