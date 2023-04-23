#include "collisionSys.hpp"
#include <iostream>

namespace game
{
    CollisionSys::CollisionSys(FVeng::GameManager& gameMan, SFMLeng::SpriteManager& spriteMan)
    : gMan_(gameMan), spriteMan_(spriteMan)
    {
    }

    CollisionSys::~CollisionSys() = default;


    // bool checkCollision(const sf::FloatRect bbox1, const sf::FloatRect bbox2){

    //     // Proyectar el rectángulo 1 en el eje X
    //     float left1 = bbox1.left;
    //     float right1 = bbox1.left + bbox1.width;

    //     // Proyectar el rectángulo 2 en el eje X
    //     float left2 = bbox2.left;
    //     float right2 = bbox2.left + bbox2.width;

    //     // Comprobar si los intervalos proyectados se solapan en el eje X
    //     if (left1 > right2 || left2 > right1) {
    //         return false;
    //     }

    //     // Proyectar el rectángulo 1 en el eje Y
    //     float top1 = bbox1.top;
    //     float bottom1 = bbox1.top + bbox1.height;

    //     // Proyectar el rectángulo 2 en el eje Y
    //     float top2 = bbox2.top;
    //     float bottom2 = bbox2.top + bbox2.height;

    //     // Comprobar si los intervalos proyectados se solapan en el eje Y
    //     if (top1 > bottom2 || top2 > bottom1) {
    //         return false;
    //     }

    //     // Si ambos intervalos se solapan en ambos ejes, entonces los bounding boxes están colisionando

    //     std::cout << "hay colision" << std::endl;

    //     return true;
    // }

    // void collisionDetect(const std::vector<sf::FloatRect>& bboxes){
        
    //     // Comprobar colisión con este bounding box
    //     // ...


    //     for (std::size_t i = 0; i < bboxes.size(); ++i) {
    //         std::cout << "hay colision??" << bboxes[i].width << "\n";
    
    //     }
        
    // }

    void CollisionSys::colliding(bool collision){
      
      if(collision){ //std::cout << "Player y Enemy estan colisionando" << std::endl;
        
      
      }
      //else std::cout << "NO HAY COLISION" << std::endl;
    }
     
    void CollisionSys::update()
    {
      
      sf::FloatRect player_bbox ;
      sf::FloatRect enemy_bbox ;
      bool checkCollision = false;

        //std::cout << "hay colision??" << std::endl;
      //collisionDetect(spriteMan_.bboxes);
     // std::cout << spriteMan_.bboxes.size() << std::endl;
    //   for (std::size_t i = 0; i < spriteMan_.bboxes.size(); ++i) {
    //         std::cout << "hay colision??" << spriteMan_.bboxes[i].height << std::endl;
    
    //     }

    //la idea es sacar del game la entidgame::Entity::TAG::Playerd usar el hasTag y con suerte obtener el bbox y asi comprobar colisiones con el intersect() y luego gestionarlas -> llamar a healthsys para que gestione temas de salud y crear una funcion que detenga el desplazamiento o permita empujar 
      auto& EM = gMan_.getEntityManager();
    

      for(auto& ent : EM){

        if(ent.hasTag(game::Entity::TAG::Player)){
          player_bbox = ent.render->Sprite.getGlobalBounds();
          //sf::FloatRect pl_bboxH = ent.render->Sprite.getGlobalBounds().height;
        }

        if(ent.hasTag(game::Entity::TAG::Enemy)){
          enemy_bbox = ent.render->Sprite.getGlobalBounds();
        }

        checkCollision = player_bbox.intersects(enemy_bbox);

        colliding(checkCollision);
      }


      // std::cout << "BBOX PLAYER WIDTH:  " << player_bbox.width << "\n" << "BBOX PLAYER HEIGHT:  " << player_bbox.height << std::endl;

      // std::cout << "BBOX ENEMY WIDTH:  " << enemy_bbox.width << "\n" << "BBOX ENEMY HEIGHT:  " << enemy_bbox.height << std::endl;

    }
}