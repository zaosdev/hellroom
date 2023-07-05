#include "animationSys.hpp"

namespace game{
    animationSys::animationSys(FVeng::GameManager& gameMan)
    : gMan_(gameMan){

        // this->imageCount = imageCount;
        // this->switchTime = switchTime;

        // totalTime = 0.0f;

        // currentImage.x = 0;

        // uvRect.width = texture->getSize().x / float(imageCount.x);
        // uvRect.height = texture->getSize().y / float(imageCount.y);

    }

    void animationSys::setTexureID(size_t id){
        texId_ = id;
    }

    void animationSys::update(float deltaTime){

        auto& EM = gMan_.getEntityManager();

        auto it = std::find_if(EM.begin(),EM.end(),[&](auto& e){ return e.id()==texId_;});
        auto& tex = *it.base(); //devuelve la textura, comprobar si devuelve sprite

        auto texX = tex.render->Sprite.getTexture()->getSize().x;
        auto texY = tex.render->Sprite.getTexture()->getSize().y;


        for(auto& ent : EM){
            if(ent.anim && ent.render)
            {
                //recuperar textura en vez de guardar AQUI
    
                auto& anim = ent.anim;

                //std::cout << "CURRENT IMAGE X" << anim->currentImage.x << "CURRENT IMAGE Y" << anim->currentImage.y << std::endl;


                anim->uvRect.width = texX/float(anim->imageCount.x);
                anim->uvRect.height = texY/float(anim->imageCount.y);

                anim->currentImage.y = anim->row;
                anim->totalTime += deltaTime;

                if(anim->totalTime >= anim->switchTime){
                    anim->totalTime -= anim->switchTime; 
                    anim->currentImage.x++;

                    if(anim->currentImage.x >= anim->imageCount.x){
                        anim->currentImage.x = 0;
                    }
                }

                anim->uvRect.left = anim->currentImage.x * anim->uvRect.width;
                anim->uvRect.top = anim->currentImage.y * anim->uvRect.height;

               //cambia el area de visualizacion de la textura
                ent.render->Sprite.setTextureRect(ent.anim->uvRect);
            }
            }

        

           
           
           
           
           
           
           
           
           
            // currentImage.y = row;
            // totalTime += deltaTime;

            // if(totalTime >= switchTime){
            //     totalTime = deltaTime; 
            //     currentImage.x++;

            //     if(currentImage.x > imageCount.x){
            //         currentImage.x = 0;
            //     }
            // }

            // uvRect.left = currentImage.x * uvRect.width;
            // uvRect.top = currentImage.y * uvRect.height;
    }
}