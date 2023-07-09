#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../cmp/entity.hpp"
#include "../man/GameManager.hpp"


//display time, player health, player bullets...
#define spacing 35

namespace game
{
    struct DialogueSys
    {
        DialogueSys(FVeng::GameManager& Gman);
        ~DialogueSys() = default;

        DialogueSys (const DialogueSys&) = delete;
        DialogueSys (DialogueSys&&) = delete;
        DialogueSys& operator=(const DialogueSys&)= delete;
        DialogueSys& operator=(DialogueSys&&)= delete;

        void loadResources();

        void update();

        void enterHasBeenPreesed();

        void showAllText(std::string& allContent);
        // FVmath::Point2Di renderHearts ();
        // void renderShield(FVmath::Point2Di lastHeartPosition);
        // void renderCoins();
        // void renderGunType();
        // void renderTimer();
        // void restartTime();
        // void setMaxTime(double newTime);
        

        private:
            FVeng::GameManager& gMan_;
            sf::RenderWindow&   window_;
            sf::Clock           clock_                   {};
            sf::Clock           enterClock_              {};
            sf::Text            text_                    {};
            sf::Text            skipText_                {};  
            sf::Font            font_                    {};
            std::map<std::string, std::string> textMap_  {}; 
            sf::RectangleShape square_                   {};
            size_t              currentIndex_            {0};
            bool                hasToRead_               {true};
            bool                enterPressed_            {false};

            //for example, 1_2 means the second text in the level, there should be triggers to activate each text when needed

            static constexpr float  timeBetweenChars {.025f}; 

            static constexpr const char* text_path_1v1 = "../media/texts/text_level_1v1.txt";
            static constexpr const char* text_path_2v1 = "../media/texts/text_level_2v1.txt";
    };
}