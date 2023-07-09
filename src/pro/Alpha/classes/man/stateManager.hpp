#pragma once

#include <iostream>

#include <memory>
#include <stack>

#include "states/state.hpp"
#include <SFML/Graphics.hpp>

namespace FVEng{
    typedef std:: unique_ptr<State> StateRef;

    class StateMachine{

        public:
            StateMachine (int x, int y, std::string nameGame); 
            ~StateMachine( ) {}

            StateMachine (const StateMachine&) = delete;
            StateMachine (StateMachine&&) = delete;
            StateMachine& operator=(const StateMachine&)= delete;
            StateMachine& operator=(StateMachine&&)= delete;

            void RemoveState(  );

            void ChangeToMainMenuState(bool replace);
            void ChangeToGameState(bool replace);   
            void ChangeToStoreState(bool replace);
            void ChangeToGameOverState(bool replace);
            void ChangeToControlsState(bool replace);
            void ChangeToPauseState(bool replace);

            sf::RenderWindow& getWindow();
            void ProcessStateChanges( );
            StateRef &GetActivateState( );

        private:
            void AddState(StateRef NewState, bool isReplacing);
            std::stack<StateRef> states_;
            StateRef newState_;

            bool isRemoving_          ;
            bool isAdding_            ; 
            bool isReplacing_         ;
            sf::RenderWindow window_{}; //samewindow for all states
    };

}