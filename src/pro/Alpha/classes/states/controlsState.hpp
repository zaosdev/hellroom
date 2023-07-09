#pragma once
#include <iostream>
#include <memory>

#include "state.hpp"
#include "../classes/man/stateManager.hpp"
#include "../utils/gameData.hpp"



namespace FVEng{
    class controlsState : public State {
    public:
        controlsState(sf::RenderWindow& window, FVEng::StateMachine& SM)
        : window_ {window}, SM_ {SM}
        {
        }

        void Init() override {
            
        
            if (!backgroundTexture_.loadFromFile("../media/images/controles_fv_2.png")) 
            {
                std::cout << "Error loading background image" << std::endl;
                std::terminate();
            }
            configurateBackgroundAccordingToWindow();
            
            
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
                        configurateBackgroundAccordingToWindow();
                        break;
                    }
                    default:
                        break;
                }
            }

            //act to registered key events
            if(scapePressed_)
            {
                //end game
                // SM_.RemoveState();
                SM_.ChangeToMainMenuState(false);
            }
            //once handled, restart values
            scapePressed_ = false;
        }


        void RegisterKeys()
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                scapePressed_ = true;
            }
        }

    

    private:
        sf::Texture         backgroundTexture_   {};
        sf::Sprite          backgroundSprite_    {};
        float               time2newKey_         {};
        sf::Clock           clockMenu_           {};

        sf::RenderWindow&   window_;

        bool scapePressed_ = false;

        FVEng::StateMachine& SM_;
       
       
    };
}