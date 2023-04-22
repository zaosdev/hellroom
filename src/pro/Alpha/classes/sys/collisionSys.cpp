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

     
    void CollisionSys::update()
    {

        //std::cout << "hay colision??" << std::endl;
      //collisionDetect(spriteMan_.bboxes);
      std::cout << spriteMan_.bboxes.size() << std::endl;
    //   for (std::size_t i = 0; i < spriteMan_.bboxes.size(); ++i) {
    //         std::cout << "hay colision??" << spriteMan_.bboxes[i].height << std::endl;
    
    //     }

    }
}