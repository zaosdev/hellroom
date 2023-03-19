#include "soundSys.hpp"


//SoundSys::SoundSys() : isPlaying(false) {}

void SoundSys::loadSound(const std::string& soundfile){

    if(!sB.loadFromFile(soundfile)){
        std::cout << "SOUND FILE NOT FOUND" << std::endl;
    }
    sound.setBuffer(sB);
}

void SoundSys::playSound(){
    //if(!isPlaying){
        sound.play();
    //     isPlaying = true;
    // }
    
}

void SoundSys::stopSound(){
    //if(isPlaying){
        sound.stop();
    //    isPlaying = false;
    //}
}

// void SoundSys::setLoop(bool loop){
//     sound.setLoop(loop);
// }


//codigo basura

// std::map<sf::Keyboard::Key, SoundSys> soundMap;
// soundMap[sf::Keyboard::A] = SoundSys();
// soundMap[sf::Keyboard::A].loadSound("resources/SFX/16_human_walk_stone_1.wav");
// soundMap[sf::Keyboard::B] = SoundSys();
// soundMap[sf::Keyboard::B].loadSound("resources/SFX/16_human_walk_stone_3.wav");


// for (auto const& pair : soundMap) {
//         if (sf::Keyboard::isKeyPressed(pair.first)) {
//             pair.second.setLoop(true);
//             pair.second.playSound();
//         } else {
//             pair.second.setLoop(false);
//             pair.second.stopSound();
//         }
//     }