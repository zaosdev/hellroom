#include "stateManager.hpp"


#include "states/gameState.hpp"
#include "states/storeState.hpp"
#include "states/mainMenuState.hpp"
#include "states/gameOverState.hpp"
#include "states/controlsState.hpp"
#include "states/pauseState.hpp"
#include "states/engGameState.hpp"

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

    void StateMachine::ChangeToMainMenuState(bool replace) 
    {
        AddState(std::make_unique<FVEng::mainMenuState>(getWindow(), *this), replace);
    }

    void StateMachine::ChangeToGameState(bool replace) 
    {
        AddState(std::make_unique<FVEng::gameState>(getWindow(), *this), replace);
    }

    void StateMachine::ChangeToStoreState(bool replace) 
    {
        AddState(std::make_unique<FVEng::storeState>(getWindow(), *this), replace);
    }

    void StateMachine::ChangeToGameOverState(bool replace) 
    {
        AddState(std::make_unique<FVEng::gameOverState>(getWindow(), *this), replace);
    }

    void StateMachine::ChangeToEndGameState(bool replace)
    {
        AddState(std::make_unique<FVEng::endGameState>(getWindow(), *this), replace);
    }

    void StateMachine::ChangeToControlsState(bool replace) 
    {
        AddState(std::make_unique<FVEng::controlsState>(getWindow(), *this), replace);
    }

    void StateMachine::ChangeToPauseState(bool replace) 
    {
        AddState(std::make_unique<FVEng::pauseState>(getWindow(), *this), replace);
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