#ifndef GUICONTEXTMENU_HPP
#define GUICONTEXTMENU_HPP

// Local headers
#include "GUIBox.hpp"

// SFML headers
#include <SFML/Graphics.hpp>

// C++ headers
#include <iostream>
#include <list>


// TODO: relative positions
// at the moment all drawing is done using absolute positions,
// whereas a parent->child relationship should be used to draw
// using relative positions

class GUIContextMenuItem : public GUIBox
{

    public:

    GUIContextMenuItem(const int size_x, const int size_y)
        : GUIBox(size_x, size_y)
    {
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        GUIBox::background.setFillColor(sf::Color::Red);

        text.setString("context menu");
        text.setFont(font);
        text.setCharacterSize(11);
    }

    // set size auto
    //GUIContextMenuItem(const GUIContextMenu&

    GUIContextMenuItem(const std::string& text, const int size_x, const int size_y)
        : GUIBox(size_x, size_y)
    {
    }

    void setText(const std::string& text)
    {
        this->text.setString(text);
    }


    virtual
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        GUIBox::draw(target, states);
        target.draw(text);
    }


    protected:

    sf::Text text;
    sf::Font font; // TODO: heavy
    //sf::IntRect bounds;
};

class GUIContextMenu : public GUIBox
{


    public:

    GUIContextMenu()
        : GUIBox(120, 24)
        , offset_x{4}
        , offset_y{4}
        , title_text_offset_x{0}
        , title_text_offset_y{0}
        , pad_x{3}
        , pad_y{3}
    {
        // the position should be relative to the zero-offset position
        sf::IntRect bounds1(0, 30, 120, 50);
        sf::IntRect bounds2(0, 60, 120, 80);
        sf::IntRect bounds3(0, 90, 120, 110);
        sf::IntRect bounds4(0, 120, 120, 1400);
        item.emplace_back(new GUIContextMenuItem("item 1", bounds1.width, bounds1.height));
        item.emplace_back(new GUIContextMenuItem("item 2", bounds2.width, bounds2.height));
        item.emplace_back(new GUIContextMenuItem("item 3", bounds3.width, bounds3.height));
        item.emplace_back(new GUIContextMenuItem("item 4", bounds4.width, bounds4.height));
        GUIBox::background.setSize(sf::Vector2f(120, 150)); // TODO
        //GUIBox::background.setFillColor(sf::Color::Blue);

        
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        title_text.setString("context menu");
        title_text.setFont(font);
        title_text.setCharacterSize(11);
    }

    virtual
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        GUIBox::draw(target, states);
        target.draw(title_text);

        std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        for(; it != item.cend(); ++ it)
        {
            (*it)->draw(target, states);
        }
    }

    virtual
    void event(sf::Event& event, sf::RenderWindow& window)
    {
        if( (
                event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Right
             ) || (
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left
            ) )
        {
            sf::IntRect background_rect(GUIBox::background.getGlobalBounds());
            background_rect.width += 1;
            background_rect.height += 1;
            sf::Vector2i mouse_pos_relative(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            if(background_rect.contains(mouse_pos_relative))
            {
                // release right is same as left click
                std::cout << "ContextMenu: event" << std::endl;
            }
        }
    }
    
    void setTitle(const std::string& title)
    {
        title_text.setString(title);
    }

    protected:

    sf::Text title_text;
    sf::Font font; // TODO: heavy resource
    int offset_x; // general offset
    int offset_y;
    int title_text_offset_x; // title text offset
    int title_text_offset_y;
    int pad_x; // component padding
    int pad_y; 

    int pos_x;
    int pos_y;

    std::list<std::unique_ptr<GUIContextMenuItem>> item;

};


#endif // GUICONTEXTMENU_HPP
