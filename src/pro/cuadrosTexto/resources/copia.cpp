// #include <SFML/Graphics.hpp>
// #include <iostream>

// #include <fstream>
// #include <string>

// #include "include/config.h"


// int main() {

//   //Creamos una ventana
//   sf::RenderWindow window(sf::VideoMode(640, 480), "P2 Cuadros de texto");

//   //para que salga el texto en pantalla necesito un obj texto
//   sf::Font fuente;
//   fuente.loadFromFile("resources/Minecraft.ttf"); //fuente con la que se vera el texto

//   sf::Text texto("", fuente, 16);
//   texto.setFillColor(sf::Color::Yellow);
//   texto.setPosition(10,10);

//   //  // Cargamos el sprite de cuadro de texto
//   // sf::Texture texture;
//   // texture.loadFromFile("resources/cuadro_texto.png");
//   // sf::Sprite cuadro(texture);

//   //Creamos un cuadro para el texto
//   sf::RectangleShape cuadro(sf::Vector2f((window.getSize().x - 20), 100));
//   cuadro.setPosition(5,5);
//   cuadro.setOutlineThickness(3);
//   cuadro.setOutlineColor(sf::Color::Blue);
//   cuadro.setFillColor(sf::Color::Transparent);
  
//   std::ifstream leer("resources/texto.txt");
//   std::string linea;

//   while (window.isOpen())
//   {
//     //Bucle de obtención de eventos
//     sf::Event event;
//     while (window.pollEvent(event))
//     {
//       if (event.type == sf::Event::Closed)
//       {
//         window.close();
//       }
//     }

//     //Leemos el archivo de texto
//     if (std::getline(leer, linea))
//     {
//       for (std::size_t i = 0; i < linea.size(); i++)
//       {
//         texto.setString(texto.getString() + linea[i]);

//         window.clear();
//         window.draw(cuadro);
//         window.draw(texto);
//         window.display();

//         sf::sleep(sf::milliseconds(100));
//       }
//       texto.setString(texto.getString() + "\n");
//     }
//     else
//     {
//       // Si hemos llegado al final del archivo, lo cerramos y reiniciamos
//       leer.close();
//     }

//     // Esperamos un poco antes de la siguiente iteración
//     sf::sleep(sf::milliseconds(10));
//   }

//   return 0;
// }
