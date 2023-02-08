#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "classes/sys/renderSys.hpp"
#include "classes/man/GameManager.hpp"
#include "classes/man/SpriteManager.hpp"



#define kVel 5

int main() {


  //Create render system
  FVeng::GameManager man{640, 480,"P0. Fundamentos de los Videojuegos. DCCIA"};

  SFMLeng::SpriteManager SPman{};

  game::RenderSys renSys{man};

  //Creamos una ventana
  SPman.loadTexture(man.ent->render->tex,"");
  //Y creo el spritesheet a partir de la imagen anterior
  SPman.assignTexture(man.ent->render->Sprite,man.ent->render->tex);
  //Le pongo el centroide donde corresponde
  SPman.modifySpriteOrigin(man.ent->render->Sprite,{75 / 2, 75 / 2});
  //Cojo el sprite que me interesa por defecto del sheet
  SPman.modifyTextureRect(man.ent->render->Sprite,sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // Lo dispongo en el centro de la pantalla
  man.ent->physics->pos = {320, 240};
  man.ent->physics->vel = {kVel,kVel};


  //Bucle del juego
  while (window.isOpen()) {
    //Bucle de obtención de eventos

    window.clear();
    window.draw(sprite);
    window.display();
  }

  return 0;
}