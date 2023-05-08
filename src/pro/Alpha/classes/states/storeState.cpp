#pragma once
#include <iostream>
#include <memory>

#include "state.hpp"
#include "../classes/man/stateManager.hpp"
#include "gameState.cpp"

#define MAX_NUMBER_OF_ITEMS 3
#define PET1_PATH "../media/pets/pet.png"
#define PET2_PATH "../media/pets/pet.png"
#define PET3_PATH "../media/pets/pet.png"
namespace FVEng{
    class storeState : public State {
    public:
        storeState(sf::RenderWindow& window, FVEng::StateMachine& SM)
        : window_ {window}, SM_ {SM}
        {
            Init();
        }

        void Init() override {
            
            //load background
            if (!backgroundTexture_.loadFromFile("../media/images/tienda_fondo.png")) 
            {
                std::cout << "Error loading background image" << std::endl;
                std::terminate();
            }
            configurateBackgroundAccordingToWindow();

            //load font
            if (!font_.loadFromFile("../media/font/Retro_Gaming.ttf")) {
            // manejar error de carga de fuente
            std::terminate();
            }

            //load all the textures and sprites of pets and coins
            if (    !pet1Texture_.loadFromFile(PET1_PATH)
                ||  !pet2Texture_.loadFromFile(PET2_PATH)
                ||  !pet3Texture_.loadFromFile(PET3_PATH)
                ) 
            {
                std::cout << "Error loading pet image" << std::endl;
                std::terminate();
            }

            pets_[0].setTexture(pet1Texture_);
            pets_[1].setTexture(pet2Texture_);
            pets_[2].setTexture(pet3Texture_);


            //Configurate color and position of text
            configurateMenuAccordingToWindow();
        }

        void executeState() override
        {
            for(int i = 0; i < 60; i++)
            {
                RegisterKeys();
                if(i % 30== 0) {HandleInput();}
                Render();
            }
        }

        void configurateMenuAccordingToWindow()
        {
            for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
            {
                menu_[i].setFont(font_);
                menu_[i].setFillColor(sf::Color::White);
                menu_[i].setString(pet_names_[i]);
                menu_[i].setPosition(sf::Vector2f(window_.getSize().x / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - menu_[i].getLocalBounds().width/2.0f, window_.getSize().y / (4 + i%2)));
                pets_[i].setPosition(sf::Vector2f(window_.getSize().x / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - pets_[i].getLocalBounds().width/2.0f, window_.getSize().y / (4 + i%2)));
            }


        }

        void configurateBackgroundAccordingToWindow()
        {
            //Redimensionate according to window width
            backgroundSprite_.setTexture(backgroundTexture_);
            float scale = (float)window_.getSize().x / backgroundTexture_.getSize().x;
            backgroundSprite_.setScale(scale, scale);

            //Set position centered y
            float yPos = (window_.getSize().y - (backgroundTexture_.getSize().y * scale)) / 2.f;
            backgroundSprite_.setPosition(0.f, yPos);
        }
        
        void Render()
        {
            window_.clear();
            window_.draw(backgroundSprite_);
            for(auto& option : menu_)
            {
                window_.draw(option);
            }
            for(auto& pet : pets_)
            {
                window_.draw(pet);
            }
            window_.display();
        }

        void HandleInput()
        {
            //act to window events
            sf::Event event;
            while (window_.pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::Closed:
                        window_.close();
                        break;
                    case sf::Event::Resized:
                    // Actualizar la vista de la ventana
                    {
                        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                        window_.setView(sf::View(visibleArea));
                        configurateMenuAccordingToWindow();
                        configurateBackgroundAccordingToWindow();
                        break;
                    }
                    default:
                        break;
                }
            }

            //act to registered key events
            if(upPressed_)
            {
                moveDown();
            }
            if(downPressed_)
            {
                moveUp();
            }

            for(auto& option : menu_)
            {
                option.setFillColor(sf::Color::White);
            }
            menu_[selectedItemIndex].setFillColor(sf::Color::Red);

            if(enterPressed_)
            {
                changeStateAccordingToSelectedIndex();
            }
            //once handled, restart values
            upPressed_ = downPressed_ = false;
        }


        void changeStateAccordingToSelectedIndex()
        {
            if(selectedItemIndex == 0) //Play option
            {
                std::cout << "Entering game mode..." << std::endl;
                SM_.AddState(std::make_unique<FVEng::gameState>(SM_.getWindow(), SM_), true);
            }
            if(selectedItemIndex == 1) //Options option
            {   
                std::cout << "Options..." << std::endl;
            }
            if(selectedItemIndex == 2) //Exit option
            {
                std::cout << "Exit..." << std::endl;
                window_.close();
            }
            enterPressed_ = false;
        }


        void RegisterKeys()
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                upPressed_ = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                downPressed_ = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                enterPressed_ = true;
            }
        }

        
        void moveUp()
        {
            if      (selectedItemIndex < MAX_NUMBER_OF_ITEMS - 1) selectedItemIndex++;
            else    selectedItemIndex = 0;
        }

        void moveDown()
        {
            if      (selectedItemIndex > 0) selectedItemIndex--;
            else    selectedItemIndex = MAX_NUMBER_OF_ITEMS-1;
        }

    

    private:
        sf::Texture         backgroundTexture_;
        sf::Sprite          backgroundSprite_;
        sf::Texture         coinTexture_;
        sf::Sprite          coinprite_;
        sf::Texture         pet1Texture_, pet2Texture_, pet3Texture_;
        sf::Sprite          pets_[MAX_NUMBER_OF_ITEMS];

        sf::RenderWindow&   window_;
        int selectedItemIndex = 0;
        sf::Font font_;
        sf::Text menu_[MAX_NUMBER_OF_ITEMS];
        sf::Text coins_;
        std::vector<std::string> pet_names_ {"Centinela", "Guardian", "Vitalis"};
        bool upPressed_, downPressed_;
        bool enterPressed_ = false;

        FVEng::StateMachine& SM_;
    };
}
