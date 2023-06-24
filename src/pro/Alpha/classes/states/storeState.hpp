#pragma once
#include <iostream>
#include <memory>

#include "state.hpp"
#include "../classes/man/stateManager.hpp"
#include "gameState.hpp"
#include "../utils/gameData.hpp"

#define MAX_NUMBER_OF_ITEMS 3
#define PET1_PATH "../media/pets/vitalis.png"
#define PET2_PATH "../media/pets/guardian.png"
#define PET3_PATH "../media/pets/sentinel.png"
#define COIN_PATH "../media/HUD/coin.png"
#define PET1_COST 300 //vitalis
#define PET2_COST 400 //guardian
#define PET3_COST 500 //centinela

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
                ||  !coinTexture_.loadFromFile(COIN_PATH)
                ) 
            {
                std::cout << "Error loading pet image" << std::endl;
                std::terminate();
            }

            //Set texture
            pets_[0].setTexture(pet1Texture_);
            pets_[1].setTexture(pet2Texture_);
            pets_[2].setTexture(pet3Texture_);
            coin_sp_.setTexture(coinTexture_);

            //Redimensionate to 128x128
            // FVmath::Point2Di originalSize  = {(int) pet1Texture_.getSize().x, (int) pet1Texture_.getSize().y};
            // FVmath::Point2Di objectiveSize = {128, 128}; 
            // float xScale = objectiveSize.x / originalSize.x;
            // float yScale = objectiveSize.y / originalSize.y;
            // for(auto& pet : pets_)
            // {
            //    pet.setScale(xScale, yScale)
            // }

            updateUI();

            

            //Configurate color and position of text
            configurateMenuAccordingToWindow();

            

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
                sf::Vector2f menu_position = sf::Vector2f(  window_.getSize().x / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - menu_[i].getLocalBounds().width/2.0f, 
                                                            window_.getSize().y / (4 + i%2));
                sf::Vector2f pet_position  = sf::Vector2f(  window_.getSize().x / (MAX_NUMBER_OF_ITEMS + 1) * (i + 1) - pets_[i].getLocalBounds().width/2.0f, 
                                                         (  window_.getSize().y + pets_[i].getLocalBounds().height + 80) / (4 + i%2));
                
                sf::Vector2f cost_position = sf::Vector2f(  pet_position.x, pet_position.y + pets_[i].getLocalBounds().height);
                menu_[i].setFont(font_);
                menu_[i].setFillColor(sf::Color::White);
                menu_[i].setString(pet_names_[i]);
                menu_[i].setPosition(menu_position);
                pets_[i].setPosition(pet_position);
                pets_cost_[i].setPosition(cost_position);
            }
            sf::Vector2f coins_position = sf::Vector2f  (  window_.getSize().x / 2.0f - coins_text_.getLocalBounds().width, 
                                                           window_.getSize().y * .06f);
            coins_text_.setPosition(coins_position);
            coin_sp_.setPosition(coins_position.x + coins_text_.getGlobalBounds().width + 20, coins_position.y);

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
            for(auto& cost : pets_cost_)
            {
                window_.draw(cost);
            }
            window_.draw(coins_text_);
            window_.draw(coin_sp_);

            //move the coin sprite next to the prices
            auto savedPosition = coin_sp_.getPosition();
            for(size_t i = 0; i < boughtPets_.size(); i++)
            {
                if(boughtPets_[i] == false)
                {
                    //move to the price
                    auto coinPosition = 
                        sf::Vector2f(pets_cost_[i].getPosition().x  + pets_cost_[i].getGlobalBounds().width + 10, 
                                     pets_cost_[i].getPosition().y);
                    coin_sp_.setPosition(coinPosition);
                    window_.draw(coin_sp_);
                }
            }
            coin_sp_.setPosition(savedPosition);

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
            if(upPressed_ || downPressed_ || enterPressed_ || scapePressed_)
            {
                clockMenu_.restart();
            }
            else return;

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
            if(scapePressed_)
            {
                //remove this state ( main menu is below this and not deleted)
                SM_.RemoveState();
            }
            //once handled, restart values
            upPressed_ = downPressed_ =  enterPressed_ = scapePressed_ = false;
        }


        void changeStateAccordingToSelectedIndex()
        {
            if(selectedItemIndex == 0) //Vitalis option
            {
                buyOrSelectPet(selectedItemIndex, PET1_COST);
            }
            if(selectedItemIndex == 1) //Guardian option
            {   
                buyOrSelectPet(selectedItemIndex, PET2_COST);
            }
            if(selectedItemIndex == 2) //Centinela option
            {
                buyOrSelectPet(selectedItemIndex, PET3_COST);
            }
            enterPressed_ = false;
        }

        void buyOrSelectPet(int selectedItemIndex, int cost)
        {
            std::cout << "Buying or selecting pet " << selectedItemIndex << std::endl;
            if(selectedPet_ == selectedItemIndex) return;
            if(boughtPets_[selectedItemIndex] == false)
            {
                if(available_coins_ < cost) return;
                else
                {
                    available_coins_ -= cost;
                    FVData::writeCoins(available_coins_);
                    boughtPets_[selectedItemIndex] = true;
                    FVData::writeBoughtPets(boughtPets_);
                }
            }
            else
            {
                FVData::writeSelectedPet(selectedItemIndex);
            }

            updateUI();
            
        }

        void updateUI()
        {
            available_coins_ = FVData::getCoins();
            coins_text_.setFont(font_);
            coins_text_.setFillColor(sf::Color::Black);
            coins_text_.setString(std::to_string(available_coins_));
            

            //set pets cost
            pets_cost_[0].setString(std::to_string(PET1_COST));
            pets_cost_[1].setString(std::to_string(PET2_COST));
            pets_cost_[2].setString(std::to_string(PET3_COST));
            for(auto& cost : pets_cost_)
            {
                cost.setFont(font_);
                cost.setFillColor(sf::Color::White);
            }
            
            
            //check if some pet is bought and then change the string
            boughtPets_ = FVData::getBoughtPets();
            for(size_t i = 0; i < boughtPets_.size(); i++)
            {
                if(boughtPets_[i] == true)
                {
                    pets_cost_[i].setString("Bought");
                }
            }

            
            //if some pet is selected, change the text and color
            selectedPet_ = FVData::getSelectedPet();
            if(selectedPet_ != -1)
            {
                pets_cost_[selectedPet_].setString("Selected");
                pets_cost_[selectedPet_].setFillColor(sf::Color::Magenta);
            } 
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                enterPressed_ = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                scapePressed_ = true;
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

        float               time2newKey_        {.3f};
        sf::Clock           clockMenu_          {};

        sf::RenderWindow&   window_;
        int selectedItemIndex = 0;
        sf::Font font_;
        sf::Text menu_[MAX_NUMBER_OF_ITEMS];
        
        std::vector<std::string> pet_names_ {"Vitalis", "Guardian", "Sentinel"};
        
        int  available_coins_ = 0;
        sf::Text coins_text_;
        sf::Sprite coin_sp_;
        sf::Text pets_cost_[MAX_NUMBER_OF_ITEMS];

        bool upPressed_, downPressed_, scapePressed_;
        bool enterPressed_ = false;
        
        std::vector<bool> boughtPets_;
        int selectedPet_ = -1;

        FVEng::StateMachine& SM_;
    };
}
