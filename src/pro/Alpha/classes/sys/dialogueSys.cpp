#include "dialogueSys.hpp"
#include <string>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "../define.h"

#define FONT_PATH "../media/font/Retro_Gaming.ttf"

//#include "../utils/math.hpp"
//#include <cmath>
namespace game
{
    static constexpr int lifeHeart = 100.f;

    DialogueSys::DialogueSys(FVeng::GameManager& Gman)
    : gMan_   (Gman),
     window_  (gMan_.getWindow())
    {
        loadResources();
        //restartTime();
    }

    void DialogueSys::enterHasBeenPreesed()
    {
        //if passed at least 0.3 seconds, admit new enter
        if(enterClock_.getElapsedTime().asSeconds() > 0.3f)
        {
            enterPressed_ = true;
            enterClock_.restart();
        }
        
    }

    void DialogueSys::loadResources()
    {
        if (!font_.loadFromFile(FONT_PATH)) 
        {
            // manejar error de carga de fuente
            std::terminate();
        }

        //Configurate text
        text_.setFillColor(sf::Color::White);
        text_.setFont(font_);
        //text_.setCharacterSize(40);
        text_.setPosition({static_cast<float>(window_.getSize().x - 85), 0});

        //Configurate skip text
        skipText_ = sf::Text("Press Enter to Skip or Exit", font_, 18);
        skipText_.setFillColor(sf::Color::White);

        //Creamos un square_ para el texto
        // Obtener el tamaño de la ventana
        sf::Vector2u windowSize = gMan_.getWindow().getSize();

        // Calcular el tamaño y la posición del cuadrado
        sf::Vector2f squareSize(static_cast<float>(windowSize.x - 40), windowSize.y / 3);
        sf::Vector2f squarePosition((windowSize.x - squareSize.x) / 2, windowSize.y - squareSize.y - 20);

        square_.setSize(squareSize);
        square_.setPosition(squarePosition);
        square_.setOutlineThickness(3);
        square_.setOutlineColor(sf::Color::Blue);
        square_.setFillColor(sf::Color(20, 20, 70));

        //Create the map for all the texts in the game
        textMap_.insert(std::make_pair("1.1", text_path_1v1));
        textMap_.insert(std::make_pair("2.1", text_path_2v1));
    }

    void DialogueSys::showAllText(std::string& allContent)
    {
        text_.setString(allContent);
        currentIndex_ = allContent.size();
    }


    void DialogueSys::update()
    {   
        if(not hasToRead_) return;

        

        //Read the text archive
        std::ifstream ifstream(textMap_.at("1.1"));
        if(!ifstream) 
        {
            std::cout << textMap_.at("1.1") << std::endl;
            std::terminate();
        }
        else 
        {
            std::cout << "Archivo leido correctamente" << std::endl;
        }

        std::string content {};
        std::string linea   {};
        while (std::getline(ifstream, linea)) 
        {
            content += linea + "\n";
        }
        auto textFinished = [&content](size_t currentIndex_) 
        {return !(currentIndex_ >= 0 && currentIndex_ < content.size());};

        bool skip = false; //para saber si se lee el texto de una o letra a letra


        // Create new view for the text
        sf::View uiView(sf::FloatRect(0, 0, window_.getSize().x, window_.getSize().y));

        // Activate the new view
        window_.setView(uiView);

        sf::Vector2u windowSize = window_.getSize();

        if(not textFinished(currentIndex_))
        {
            // Calcular la posición del cuadrado
            float squareX = (windowSize.x - square_.getSize().x) / 2;
            float squareY = windowSize.y - square_.getSize().y - 20;
            // Actualizar la posición del cuadrado
            square_.setPosition(squareX, squareY);

            // Set the text position
            text_.setPosition(square_.getPosition().x + 10, square_.getPosition().y + 10);

            // Obtener la posición y las dimensiones del cuadrado
            sf::Vector2f squarePosition = square_.getPosition();
            sf::Vector2f squareSize = square_.getSize();
            // Establecer la posición del texto "Press Enter to Skip" alineado con el cuadrado
            sf::FloatRect textBounds = skipText_.getLocalBounds();
            float textX = squarePosition.x + (squareSize.x - textBounds.width) / 2;
            float textY = squarePosition.y + squareSize.y - 30.f;
            skipText_.setPosition(textX, textY);

            if(enterPressed_) showAllText(content);
            else
            {
                //Fill the text char by char if skip not active
                if(clock_.getElapsedTime().asSeconds() > timeBetweenChars
                && not textFinished(currentIndex_))
                {
                    clock_.restart();
                    char nextChar {content[currentIndex_]};
                    text_.setString(text_.getString() + nextChar);
                    currentIndex_ ++;
                }
            }
        }
        else if(enterPressed_)
        {

            hasToRead_ = false;
        }

        
        
        
        




        // Dibujar el texto en la vista de la interfaz de usuario
        window_.draw(square_);
        window_.draw(text_);
        window_.draw(skipText_);
        
       


        enterPressed_ = false;
    }

}

