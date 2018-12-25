#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

// Local headers
#include "GUIBox.hpp"

// SDL headers
#include <SFML/Graphics.hpp>

class GUIButton : public GUIBox //GUIBase
{

    public:

    GUIButton(const int size_x, const int size_y)
        : GUIBox(size_x, size_y)
        , text_offset_x{4}
        , text_offset_y{4}
    {
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        text.setString("button");
        text.setFont(font);
        text.setCharacterSize(11);
    }

    
    virtual
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        GUIBox::draw(target, states);
        target.draw(text);
    }
    

    virtual
    void event(sf::Event& event, sf::RenderWindow& window)
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            sf::IntRect background_rect(GUIBox::background.getGlobalBounds());
            background_rect.width += 1;
            background_rect.height += 1;
            sf::Vector2i mouse_pos_relative(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            if(background_rect.contains(mouse_pos_relative))
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "left" << std::endl;
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "right" << std::endl;
                }
            }
        }
    }

    virtual
    void setPosition(const int pos_x, const int pos_y)
    {
        GUIBox::setPosition(pos_x, pos_y);
        text.setPosition(pos_x + text_offset_x, pos_y + text_offset_y);
    }

    protected:

    sf::Text text;
    sf::Font font;
    int text_offset_x;
    int text_offset_y;

};

#endif // GUIBUTTON_HPP