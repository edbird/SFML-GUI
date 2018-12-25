
// Local headers
#include "GUIBox.hpp"
#include "GUIBoxDrag.hpp"
#include "GUIButton.hpp"


// SDL headers
#include <SFML/Graphics.hpp>


// C++ headers
#include <iostream>
#include <fstream>
#include <string>






class Functor
{

    private:

    virtual
    ~Functor()
    {
    }

    virtual
    void operator()() = 0;



};








void open(const std::string& filename)
{
    std::cout << "open: read from file -> " << filename << std::endl;
}

void Functor_open : public Functor
{

    public:

    Functor_open(const std::string& filename)
        : filename(filename)
    {
    }

    virtual
    void operator()()
    {
        open(filename)
    }

    protected:

    const std::string& filename;

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

    guiobject.emplace_back(new GUIButton(120, 20));
    dynamic_cast<GUIBox*>(guiobject.back().get())->getBackground().setFillColor(sf::Color(120, 120, 120));
    dynamic_cast<GUIBox*>(guiobject.back().get())->setPosition(400, 200);

    guiobject.emplace_back(new GUIButton(120, 20);
    dynamic_cast<GUIBox*>(guiobject.back().get()->getBackground().setFillColor(sf::Color(80, 80, 80));
    dynamic_cast<GUIBox*>(guiobject.back().get()->setPosition(500, 200);
    Functor_open functor_open("filename.txt");
    dynamic_cast<GUIBox*>(guiobject.back().get()->setCallback(functor_open));

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
