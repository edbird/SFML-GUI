#ifndef GUITEXTBOX_HPP
#define GUITEXTBOX_HPP

// Local headers
#include "GUIBox.hpp"

// SFML headers
#include <SFML/Graphics.hpp>


class GUITextbox : public GUIBox
{

    public:

    GUITextbox(const std::string& text, const int size_x, const int size_y)
        : GUIBox(size_x, size_y)
    {
        
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        this->text.setString(text);
        this->text.setFont(font);
        this->text.setCharacterSize(11);
        this->text.setColor(sf::Color::Black);

    }

    virtual
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        GUIBox::draw(target, states);
        target.draw(text);
    }

    virtual
    void setPosition(const int pos_x, const int pos_y)
    {
        GUIBox::setPosition(pos_x, pos_y);
        text.setPosition(pos_x + 4, pos_y + 4);
    }

    protected:

    // TODO: heavy
    sf::Text text;
    sf::Font font;

};

#endif // GUITEXTBOX_HPP
