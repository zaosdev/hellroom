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

            void AddState(StateRef NewState, bool isReplacing);
            void RemoveState(  );

            void ProcessStateChanges( );
            StateRef &GetActivateState( );

            sf::RenderWindow& getWindow();

        private:
            std::stack<StateRef> states_;
            StateRef newState_;

            bool isRemoving_          ;
            bool isAdding_            ; 
            bool isReplacing_         ;
            sf::RenderWindow window_{}; //samewindow for all states
    };

}