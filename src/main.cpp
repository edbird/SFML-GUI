


// SDL headers
#include <SFML/Graphics.hpp>


// C++ headers
#include <iostream>
#include <fstream>
#include <string>


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

GUIBase::~GUIBase() {}


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

    sf::RectangleShape& getBackground()
    {
        return background;
    }

    protected:

    //sf::intRect background;
    sf::RectangleShape background;

};


class GUIBoxDrag : public GUIBox
{


    public:

    GUIBoxDrag(const int size_x, const int size_y)
        : GUIBox(size_x, size_y)
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


int main()
{


    ////////////////////////////////////////////////////////////////////////////
    // LOAD SFML
    ////////////////////////////////////////////////////////////////////////////

    // init SFML

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML GUI");

    // container of GUI objects
    std::vector<std::unique_ptr<GUIBase>> guiobject;
    typedef std::vector<std::unique_ptr<GUIBase>>::iterator guiobject_iterator;

    guiobject.emplace_back(new GUIBoxDrag(100, 100));
    dynamic_cast<GUIBox*>(guiobject.at(0).get())->getBackground().setFillColor(sf::Color::Black);
    dynamic_cast<GUIBox*>(guiobject.at(0).get())->getBackground().setPosition(200, 200);

    // program main loop
    while(window.isOpen())
    {

        // event loop
        sf::Event event;
        while(window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {

                for(guiobject_iterator it{guiobject.begin()}; it != guiobject.end(); ++ it)
                {
                    (*it)->event(event, window);
                }
            }

        }


        window.clear(sf::Color::White);

        sf::CircleShape shape(100.0);
        shape.setFillColor(sf::Color::Green);

        GUIBox box(40, 10);
        box.getBackground().setFillColor(sf::Color::Blue);
        //box.Draw(window);
        window.draw(box);

        window.draw(shape);


        for(guiobject_iterator it{guiobject.begin()}; it != guiobject.end(); ++ it)
        {
            window.draw(**it); //->draw(event, window);
        }

        window.display();

    }



    return 0;

}
