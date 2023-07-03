#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//#include "../man/GameManager.hpp"

//creo un animation component para que cada entidad tenga sus valores de animacion

namespace game{

    struct animationComponent{

        //const sf::Texture* texture {}; //por si las moscas

        size_t idTex {};

        sf::Vector2u imageCount {}; //total de imagenes
        sf::Vector2u currentImage {0,0}; //imagen actual        

        sf::IntRect uvRect {}; //recortes de animacion

    
        float totalTime {0.f}; //tiempo total de animacion
        float switchTime {0.f}; //tiempo de cambio entre sprites

        int row {};
    };
}