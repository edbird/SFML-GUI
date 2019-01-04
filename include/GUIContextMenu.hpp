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

        text.setString("context menu item");
        text.setFont(font);
        text.setCharacterSize(11);
    }

    // set size auto
    GUIContextMenuItem(const std::string& text)
        : GUIBox(0, 0)
    {
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        GUIBox::background.setFillColor(sf::Color::Red);

        this->text.setFont(font);
        this->text.setCharacterSize(11);

        this->text.setString(text);
        
        sf::FloatRect bounds(this->text.getLocalBounds());
        //GUIBox::background.setSize(sf::Vector2f((int)bounds.width, (int)bounds.height));
        GUIBox::background.setSize(sf::Vector2f((int)bounds.width, (int)this->text.getCharacterSize()));
    }

    GUIContextMenuItem(const std::string& text, const int size_x, const int size_y)
        : GUIBox(size_x, size_y)
    {
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        GUIBox::background.setFillColor(sf::Color::Red);

        this->text.setFont(font);
        this->text.setCharacterSize(11);

        this->text.setString(text);
    }

    // return text bounds
    // TODO: not the same as size
    sf::FloatRect getTextBounds() const
    {
        return this->text.getLocalBounds();
    }

    // return size of text
    sf::Vector2f getSize() const
    {
        sf::FloatRect bounds(this->text.getLocalBounds());
        //return sf::Vector2f((int)bounds.width, (int)bounds.height);
        return sf::Vector2f((int)bounds.width, (int)text.getCharacterSize());
    }

    // return width of text
    int getWidth() const
    {
        sf::FloatRect bounds(this->text.getLocalBounds());
        return (int)bounds.width; 
    }

    // return height of text
    int getHeight() const
    {
        //sf::FloatRect bounds(this->text.getLocalBounds());
        //return (int)bounds.height;
        (int)text.getCharacterSize();
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




    virtual
    void setPosition(const int pos_x, const int pos_y)
    {
        GUIBox::setPosition(pos_x, pos_y);

        sf::Vector2f background_pos(GUIBox::background.getPosition());
        sf::Vector2f text_pos(background_pos);
        //text_pos.x += offset_x + text_offset_x;
        //text_pos.y += offset_y + text_offset_y;
        //text_pos.y -= 3;
        text_pos.y -= text.getLocalBounds().top - 1;
        text.setPosition(text_pos);
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
        //, title_text_offset_x{0}
        //, title_text_offset_y{0}
        //, pad_x{0}
        , pad_y{7}
    {
        // the position should be relative to the zero-offset position
        //sf::IntRect bounds1(0, 30, 40, 20);
        //sf::IntRect bounds2(0, 60, 40, 20);
        //sf::IntRect bounds3(0, 90, 40, 20);
        //sf::IntRect bounds4(0, 120, 40, 20);
        //item.emplace_back(new GUIContextMenuItem("item 1", bounds1.width, bounds1.height));
        //item.emplace_back(new GUIContextMenuItem("item 2", bounds2.width, bounds2.height));
        //item.emplace_back(new GUIContextMenuItem("item 3", bounds3.width, bounds3.height));
        //item.emplace_back(new GUIContextMenuItem("item 4", bounds4.width, bounds4.height));
        //GUIBox::background.setSize(sf::Vector2f(120, 150)); // TODO
        //GUIBox::background.setFillColor(sf::Color::Blue);
 
        font.loadFromFile("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf");

        title_text.setFont(font);
        title_text.setCharacterSize(11);
        title_text.setString("context menu");

        setSize((int)title_text.getLocalBounds().width + 2 * offset_x, (int)title_text.getLocalBounds().height + 2 * offset_y);
    }

    protected:

    void setPosSizeHelper()
    {

        // iterate and find largest text width
        int size_x{(int)title_text.getLocalBounds().width};
        //int size_y{(int)title_text.getLocalBounds().height};
        int size_y{(int)title_text.getCharacterSize()};
        int max_width{(int)title_text.getLocalBounds().width};
        int count{0};
        size_x += 2 * offset_x;
        size_y += 2 * offset_y + pad_y;
        std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        for(; it != item.cend(); ++ it)
        {
            sf::Vector2f bounds((*it)->getSize());
            if(bounds.x > max_width) max_width = bounds.x;
            size_y += bounds.y + pad_y + 2; // 2 for 1 pixel above and below text
            //size_y += (*it)->getCharacterSize() + pad_y;
            ++ count;
        }
        

        // set size
        setSize(max_width + 2 * offset_x, size_y);


        // set item sizes and positions

        int pos_x{(int)getPosition().x};
        int pos_y{(int)getPosition().y};

        pos_x += offset_x;
        pos_y += offset_y;

        // set title text position
        title_text.setPosition(pos_x, pos_y);

        // add title size
        //pos_y += title_text.getLocalBounds().height;
        pos_y += title_text.getCharacterSize();
        
        // add title pad
        pos_y += pad_y;


        //std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        it = item.cbegin();
        for(; it != item.cend(); ++ it)
        {
            pos_y += 1;

            // set item position
            (*it)->setPosition(pos_x, pos_y);

            // add size of each ContextMenuItem
            sf::Vector2f bounds((*it)->getSize());
    
            // set item size
            (*it)->setSize(max_width, bounds.y + 2);

            pos_y += bounds.y;
            pos_y += pad_y;
            pos_y += 1;
            //++ count;

            //sf::FloatRect localbounds((*it)->getBounds());
            //std::cout << "[ " << localbounds.left << ", " << localbounds.top << ", " << localbounds.width << ", " << localbounds.height << " ]" << std::endl;
        }
        // add size of spacing between items
        //pos_y += count * pad_y;

        // add border size
        //pos_x += offset_x;
        //pos_y += offset_y;


        //std::cin.get();
    }

    /*
    void setSizeHelper()
    {
        // auto set size
        int size_x{0};
        int size_y{0};
        // add title size
        size_x += title_text.getLocalBounds().width;
        size_y += title_text.getLocalBounds().height;
        size_y += pad_y;
        // add size of each ContextMenuItem
        int count{0};
        std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        for(; it != item.cend(); ++ it)
        {
            sf::Vector2f bounds((*it)->getSize());
            if(bounds.x > size_x) size_x = bounds.x;
            size_y += bounds.y;
            ++ count;
        }
        // add size of spacing between items
        size_y += count * pad_y;
        // add border size
        size_x += 2 * offset_x;
        size_y += 2 * offset_y;

        setSize(size_x, size_y);
    }
    */

    /*
    void setItemPositionHelper()
    {

        // set position
        int pos_x{(int)getPosition().x};
        int pos_y{(int)getPosition().y};

        pos_x += offset_x;
        pos_y += offset_y;

        // set title text position
        title_text.setPosition(pos_x, pos_y);

        // add title size
        pos_y += title_text.getLocalBounds().height;
        
        // add title pad
        pos_y += pad_y;

        int item_width(); // TODO set this

        // iterate over items
        //int count{0};
        std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        for(; it != item.cend(); ++ it)
        {
            // set item position
            (*it)->setPosition(pos_x, pos_y);


            // add size of each ContextMenuItem
            sf::Vector2f bounds((*it)->getSize());

    
            // set item size
            (*it)->setSize(item_width, bounds.y);

            pos_y += bounds.y;
            pos_y += pad_y;
            //++ count;
        }
        // add size of spacing between items
        //pos_y += count * pad_y;

        // add border size
        //pos_x += offset_x;
        pos_y += offset_y;
    
    
        //item.back()->setPosition(pos_x, pos_y);
    }
    */

    public:
    virtual
    void addItem(const std::string& text)
    {

        /*
        // set position
        int pos_x{(int)getPosition().x};
        int pos_y{(int)getPosition().y};

        // add title size
        pos_y += title_text.getLocalBounds().height;
        // add size of each ContextMenuItem
        int count{0};
        std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        for(; it != item.cend(); ++ it)
        {
            sf::Vector2f bounds((*it)->getSize());
            pos_y += bounds.y;
            ++ count;
        }
        // add size of spacing between items
        pos_y += count * pad_y;
        // add border size
        pos_x += offset_x;
        pos_y += offset_y;
        */

        item.emplace_back(new GUIContextMenuItem(text));
        //item.back()->setPosition(pos_x, pos_y);
        /*
        sf::Vector2f size(item.back()->getSize());
        if(size.x > GUIBox::background.getSize().x)
        {
            setSize(size.x, GUIBox::background.getSize().y); // TODO:increase y with new item
        }
        */

        //setSizeHelper();
        //setItemPositionHelper();
        setPosSizeHelper();
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

    virtual
    void setPosition(const int pos_x, const int pos_y)
    {
        GUIBox::setPosition(pos_x, pos_y);
        /*
        sf::Vector2f background_pos(GUIBox::background.getPosition());
        sf::Vector2f title_text_pos(background_pos);
        title_text_pos.x += offset_x;// + title_text_offset_x;
        title_text_pos.y += offset_y;// + title_text_offset_y;
        title_text.setPosition(title_text_pos);

        std::list<std::unique_ptr<GUIContextMenuItem>>::const_iterator it{item.cbegin()};
        int item_offset_y{0};
        for(; it != item.cend(); ++ it)
        {
            item_offset_y += 30;
            (*it)->setPosition(pos_x + offset_x, pos_y + offset_y + item_offset_y);
        }
        */

        setPosSizeHelper();
    }

    // TODO: can call this function from the base class but should not be able to!
    /*
    virtual
    void setSize(const int width, const int height)
    {
        GUIBox::setSize(width, height);
        // TODO
    }
    */
    
    void setTitle(const std::string& title)
    {
        title_text.setString(title);

        //setSizeHelper();
        setPosSizeHelper();
    }

    protected:

    sf::Text title_text; // TODO: make a subobject
    sf::Font font; // TODO: heavy resource
    int offset_x; // general offset
    int offset_y;
    //int title_text_offset_x; // title text offset
    //int title_text_offset_y; // TODO readd
    //int pad_x; // component padding
    int pad_y; 

    int pos_x;
    int pos_y;

    std::list<std::unique_ptr<GUIContextMenuItem>> item;

};


#endif // GUICONTEXTMENU_HPP
