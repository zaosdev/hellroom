#pragma once

#include <iostream>

#include <memory>
#include <stack>

#include "State.hpp"

namespace MaquinaEstados{
    typedef std:: unique_ptr<State> StateRef;

    class StateMachine{

        public:
            StateMachine( ) {}
            ~StateMachine( ) {}

            void AddState(StateRef NewState, bool isRemplacing = true);
            void RemoveState(  );

            void ProcessStateChanges( );
            StateRef &GetActivateState( );

        private:
            std::stack<StateRef> _states;
            StateRef _newState;

            bool _isRemoving;
            bool _isAdding;
            bool _isRemplacing;
    };

}