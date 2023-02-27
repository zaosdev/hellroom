#include "inputSys.hpp"

namespace game
{
    InputSys::InputSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan)
    {
    }

    void InputSys::update()
    {
    gMan_.ent->physics->vel = {0,0};

    sf::Event event;
    while (gMan_.getWindow().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gMan_.getWindow().close();
        }

        // Almacenar cada evento del teclado en el array
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            events_.push_back(event);
        }
    }

    // Recorrer el array de eventos
    int i = 0;
    for (auto& event : events_)
    {
        // Si es un evento del tipo pulsar letra
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code) 
            {
                case sf::Keyboard::A:
                    gMan_.ent->physics->vel += {-5,0};
                    break;
                case sf::Keyboard::D:
                    gMan_.ent->physics->vel += {5,0};
                    break;
                case sf::Keyboard::S:
                    gMan_.ent->physics->vel += {0,5};
                    break;
                case sf::Keyboard::W:
                    gMan_.ent->physics->vel += {0,-5};
                    break;
                default:
                    break;
            }
            
        }
        i++;
        std::cout << "Proceso " << i << " eventos al mismo tiempo" << std::endl;
    }

    // Limpiar el vector de eventos
    events_.clear();
}

}