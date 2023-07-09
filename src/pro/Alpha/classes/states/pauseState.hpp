#pragma once
#include <iostream>
#include <memory>

#include "state.hpp"
#include "../classes/man/stateManager.hpp"

namespace FVEng{
    class pauseState : public State {
    public:
        pauseState(sf::RenderWindow& window, FVEng::StateMachine& SM)
        : window_ {window}, SM_ {SM}
        {
           // Init();
        }


        void Init() override {
            
            if (!backgroundTexture_.loadFromFile("../media/images/mainMenu.png")) 
            {
                std::cout << "Error loading image" << std::endl;
                std::terminate();
            }

            configurateBackgroundAccordingToWindow();

            if (!font_.loadFromFile("../media/font/Retro_Gaming.ttf")) {
            // manejar error de carga de fuente
            std::terminate();
            }

            //Configurate color and position of text
            configurateMenuAccordingToWindow();

            clockMenu_.restart();
        }

        void executeState() override
        {
            for(int i = 0; i < 60; i++)
            {
                if(time2newKey_ < clockMenu_.getElapsedTime().asSeconds()) 
                {
                    RegisterKeys();
                    HandleInput();
                }
                Render();
            }
        }

        void configurateMenuAccordingToWindow()
        {
            for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
            {
                menu_[i].setFont(font_);
                menu_[i].setFillColor(sf::Color::White);
                menu_[i].setString(menu_values_[i]);
                menu_[i].setPosition(sf::Vector2f(window_.getSize().x/2, window_.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1)));
            }
            menu_[selectedItemIndex].setFillColor(sf::Color::Red);
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

            //check if any key is selected and restart the clock or return
            if(upPressed_ || downPressed_ || enterPressed_)
            {
                clockMenu_.restart();
            }
            else return;

            //act to registered key events
            if(upPressed_)
            {
                
                //colocar sonido
                // soundSys_.setLoop(false, soundSys_.soundMdown);
                // soundSys_.playSound(soundSys_.soundMdown, soundSys_.isMdown);
                moveDown();
                
            }
            if(downPressed_)
            {
                //colocar sonido
                moveUp();
            }

            for(auto& option : menu_)
            {
                option.setFillColor(sf::Color::White);
            }
            menu_[selectedItemIndex].setFillColor(sf::Color::Red);

            if(enterPressed_)
            {
                //colocar sonido
                changeStateAccordingToSelectedIndex();
            }
            
            //once handled, restart values
            upPressed_ = downPressed_ = enterPressed_ = false;
        }


        void changeStateAccordingToSelectedIndex()
        {
            if(selectedItemIndex == 0) //Resume option
            {
                //colocar sonido
                std::cout << "Entering game mode..." << std::endl;
                SM_.RemoveState();
            }
            if(selectedItemIndex == 1) //Store option
            {   
                //colocar sonido
                std::cout << "Entering store..." << std::endl;
                SM_.ChangeToStoreState(false);
            }
            if(selectedItemIndex == 2) //Controls option
            {
                std::cout << "Controls..." << std::endl;
                SM_.ChangeToControlsState(false);
            }
            if(selectedItemIndex == 3) //Desktop option
            {
                std::cout << "Exit game" << std::endl;
                window_.close();
            }
            enterPressed_ = false;
        }


        void RegisterKeys()
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                upPressed_ = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
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
        sf::RenderWindow&   window_;
        float               time2newKey_        {.3f};
        sf::Clock           clockMenu_          {};
        int selectedItemIndex = 0;
        sf::Font font_;
        static constexpr int MAX_NUMBER_OF_ITEMS = 4;
        sf::Text menu_[MAX_NUMBER_OF_ITEMS];
        std::vector<std::string> menu_values_ {"Resume", "Store", "Controls", "Go to desktop"};
        bool upPressed_, downPressed_;
        bool enterPressed_ = false;

        FVEng::StateMachine& SM_;
        
    };
}
