#ifndef ERROR_HPP
#define ERROR_HPP


class Error
{


    Error(std::ostream& sink)
        : sink(sink)
    {

    }

    ~Error()
    {

    }

    void Message(const std::string& message)
    {
        sink << message << std::endl;
    }

    protected:

    std::ostream& sink;

};


/*
class SDLError : public Error
{


    void SDLMessage()
    {
        sink << SDL_GetError() << std::endl;
    }

    void SDLMessage(const std::string& message)
    {
        sink << message << ": " << SDL_GetError() << std::endl;
    }

    protected:

}
*/


#endif // ERROR_HPP
