#include <SFML/Graphics.hpp>






// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding A*");

//     sf::RectangleShape tile(sf::Vector2f(50.f, 50.f));
//     tile.setOutlineThickness(1.f);
//     tile.setOutlineColor(sf::Color::Black);

//     sf::Vector2i start(0, 0);
//     sf::Vector2i goal(8, 8);

//     std::vector<std::vector<int>> map = {
//         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//         {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
//         {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
//         {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//         {1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     };

//     std::vector<PathNode*> path = findPathAStar(start, goal, map);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();

//         for (int i = 0; i < map.size(); ++i)
//         {
//             for (int j = 0; j < map[i].size(); ++j)
//             {
//                 tile.setPosition(i * 50.f, j * 50.f);
//                 if (i == start.x && j == start.y)
//                 {
//                     tile.setFillColor(sf::Color::Green);
//                 }
//                 else if (i == goal.x && j == goal.y)
//                 {
//                     tile.setFillColor(sf::Color::Red);
//                 }
//                 else if (map[i][j] == 1)
//                 {
//                     tile.setFillColor(sf::Color::Black);
//                 }
//                 else if (std::find_if(path.begin(), path.end(), [&](PathNode* node) { return node->x == i && node->y == j; }) != path.end())
//                 {
//                     tile.setFillColor(sf::Color::Blue);
//                 }
//                 else
//                 {
//                     tile.setFillColor(sf::Color::White);
//                 }
//                 window.draw(tile);
//             }
//         }

//         window.display();
//     }

//     for (auto& node : path)
//     {
//         delete node;
//     }

//     return 0;
// }
