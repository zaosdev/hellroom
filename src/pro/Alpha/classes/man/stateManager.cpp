#include "stateManager.hpp"


namespace FVEng{

    StateMachine::StateMachine(int x, int y, std::string nameGame)
    : window_(sf::VideoMode(x, y), nameGame)
    {
        window_.setKeyRepeatEnabled(true); // Habilitar entrada de teclado repetido
        window_.setFramerateLimit(60);
    }

    void StateMachine::AddState(StateRef newState, bool isReplacing){

        this-> isAdding_    = true;
        this-> isReplacing_ = isReplacing;

        this->newState_ = std::move(newState);
    }

    void StateMachine::RemoveState(){
        this-> isRemoving_ = true;
    }

    void StateMachine::ProcessStateChanges(){
        if( this->isRemoving_ && !this->states_.empty()){

            this->states_.pop();

            if(this->states_.empty()){

                this->states_.top()->Resume();
            }
            this-> isRemoving_ = false;
        }
        if (this->isAdding_){
            if(!this->states_.empty()){
                if(this-> isReplacing_){
                    this->states_.pop();
                }
                else{
                    this-> states_.top()->Pause(); 
                }
            }
            this-> states_.push(std::move(this->newState_));
            this-> states_.top()->Init();
            this-> isAdding_ = false;
        }
    }
    StateRef &StateMachine::GetActivateState( ){
        return this->states_.top();
    }

    sf::RenderWindow& StateMachine::getWindow()
    {
        return window_;
    }

}