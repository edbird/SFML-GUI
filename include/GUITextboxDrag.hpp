#ifndef GUITEXTBOXDRAG_HPP
#define GUITEXTBOXDRAG_HPP

// Local headers
#include "GUITextbox.hpp"
#include "GUIBoxDrag.hpp"


// TODO: separate GUIDragable from GUIBoxDrag
class GUITextboxDrag : virtual public GUITextbox
{

    public:


    GUITextboxDrag(const std::string& text, const int size_x, const int size_y)
        : GUITextbox(text, size_x, size_y)
        , mouse_down{false}
    {
    }


    virtual
    void event(sf::Event& event, sf::RenderWindow& window)
    {
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                sf::IntRect background_rect(GUIBox::background.getGlobalBounds());
                background_rect.width += 1;
                background_rect.height += 1;
                sf::Vector2i mouse_pos_relative(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                if(background_rect.contains(mouse_pos_relative))
                {
                    mouse_pos_initial = sf::Mouse::getPosition(window);
                    mouse_pos_final = sf::Mouse::getPosition(window);
                    mouse_down = true;
                }
            }
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                mouse_down = false;
                //mouse_pos_final = sf::Mouse::getPosition(window);
                /*
                sf::Vector2i mouse_pos_delta(mouse_pos_final - mouse_pos_initial);
                mouse_pos_initial = mouse_pos_final;
                GUIBox::background.move(mouse_pos_delta);
                */
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            if(mouse_down == true)
            {
                sf::IntRect background_rect(GUIBox::background.getGlobalBounds());
                background_rect.width += 1;
                background_rect.height += 1;
                sf::Vector2i mouse_pos_relative(window.mapPixelToCoords(mouse_pos_initial));
                if(background_rect.contains(mouse_pos_relative))
                {
                    //sf::Vector2i mouse_pos_final{sf::Mouse::getPosition()};
                    mouse_pos_final = sf::Mouse::getPosition(window);
                    sf::Vector2i mouse_pos_delta(mouse_pos_final - mouse_pos_initial);
                    mouse_pos_initial = mouse_pos_final;
                    GUIBox::background.move(sf::Vector2f(mouse_pos_delta));
                    GUITextbox::text.move(sf::Vector2f(mouse_pos_delta));
                }
            }
            // TODO: new mouse position is different from old (when click happened)
            /*
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mouse_pos{sf::Mouse::getPosition(window)};
                sf::IntRect mouse_rect(mouse_pos.x, mouse_pos.y, 0, 0);
                sf::IntRect background_rect(GUIBox::background.getGlobalBounds());
                if(background_rect.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    
                }
                
                if(sf::Mouse::getPosition(window) - sf::Vector2i(GUIBox::background.getPosition()))
                {
                    
                }
            }
            */
        }
    }


    protected:

    sf::Vector2i mouse_pos_initial;
    sf::Vector2i mouse_pos_final;
    bool mouse_down;

};

#endif // GUITEXTBOXDRAG_HPP
