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
        while (gMan_.getWindow().pollEvent(event)) {

            switch (event.type) {

            //Si se recibe el evento de cerrar la ventana la cierro
            case sf::Event::Closed:
                gMan_.getWindow().close();
                break;

            //Se pulsó una tecla, imprimo su codigo
            case sf::Event::KeyPressed:

                //Verifico si se pulsa alguna tecla de movimiento
                switch (event.key.code) {

                //Mapeo del cursor
                case sf::Keyboard::Right:
                    gMan_.ent->physics->vel = {5,0};

                break;

                case sf::Keyboard::Left:
                    gMan_.ent->physics->vel = {-5,0};

                break;

                case sf::Keyboard::Up:
                    gMan_.ent->physics->vel = {0,-5};

                break;

                case sf::Keyboard::Down:
                    gMan_.ent->physics->vel = {0,5};

                break;

                //Tecla ESC para salir
                case sf::Keyboard::Escape:
                    gMan_.getWindow().close();
                break;

                //Cualquier tecla desconocida se imprime por pantalla su código
                default:
                std::cout << event.key.code << std::endl;
                break;
                }
            default:
                std::cout << "Evento resize o otro no importante" << std::endl;
            }
        }
    }
}