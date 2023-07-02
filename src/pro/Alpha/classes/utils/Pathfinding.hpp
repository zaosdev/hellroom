#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

struct Node
{
    int x;                  //x position
    int y;                  //y position
    float g;                //distance from the start node
    float h;                //distance from the end node
    float f;                //g + h
    Node* parent;           //reference to the parent node

    Node(int x_, int y_, float g_, float h_, Node* parent_)
        : x(x_), y(y_), g(g_), h(h_), f(g_ + h_), parent(parent_)
    {}
};

//compare the f cost of both nodes
struct CompareNodes
{
    bool operator()(const Node* node1, const Node* node2) //call operator, the function used on the queue
    {
        return node1->f > node2->f;
    }
};

std::vector<Node*> findPathAStar(sf::Vector2i start, sf::Vector2i goal, const std::vector<std::vector<int>>& map)
{
    const int mapWidth = map.size();
    const int mapHeight = map[0].size();

    const std::vector<sf::Vector2i> directions = {
        {0, -1},  // Up
        {0, 1},   // Down
        {-1, 0},  // Left
        {1, 0},   // Right
        // {-1, -1}, // Diagonal top left
        // {-1, 1},  // Diagonal bottom left
        // {1, -1},  // Diagonal top right
        // {1, 1}    // Diagonal bottom right
    };

    //Sort the nodes accoding to compareElements function (the less value, the first)
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList; //nodes to explore
    std::vector<Node*> closedList;                                         //explored nodes

    Node* startNode = new Node(start.x, start.y, 0.f, 0.f, nullptr);
    openList.push(startNode);                                              //add the start node to the open list

    while (!openList.empty())                                              //will theres a possible path
    {
        Node* currentNode = openList.top();                                //node to check is the first (ordered in priority queue)
        openList.pop();                                                    //eliminate the current element from the openlist             

        if (currentNode->x == goal.x && currentNode->y == goal.y)          //if the end node is found, return the path
        {
            std::vector<Node*> path;
            Node* pathNode = currentNode;
            while (pathNode != nullptr)                                    //whiles theres parents of the node, add to the path
            {
                path.push_back(pathNode);
                pathNode = pathNode->parent;
            }
            return path;
        }

        closedList.push_back(currentNode);                                //add the current node to the closed list

        for (const auto& direction : directions)                          //check on every direction
        {
            int nextX = currentNode->x + direction.x;
            int nextY = currentNode->y + direction.y;

            if 
            (     
                  nextX >= 0                    //valid in x       
            &&    nextX < mapWidth              //
            &&    nextY >= 0                    //valid in y
            &&    nextY < mapHeight             //
            &&    map[nextX][nextY] == 0        //can pass through ( valid node )
            )
            {
                //diagonal movements would cost 15, normal movements (WASD) cost 10
                float g = currentNode->g + std::sqrt(static_cast<float>(direction.x * direction.x + direction.y * direction.y))    * 10; 
                float h = std::sqrt(static_cast<float>((nextX - goal.x) * (nextX - goal.x) + (nextY - goal.y) * (nextY - goal.y))) * 10; 

                Node* nextNode = new Node(nextX, nextY, g, h, currentNode);

                bool skipNode = false;
                for (const auto& node : closedList) //check if the node is on the closed list to skip it
                {
                    if (node->x == nextNode->x && node->y == nextNode->y)
                    {
                        skipNode = true;
                        break;
                    }
                }

                if (!skipNode)  //if the node is not skipped, add to the open list
                {
                    openList.push(nextNode);
                }
            }
        }
    }

    return std::vector<Node*>(); //if theres no nodes left to check, return an empty path
}

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

//     std::vector<Node*> path = findPathAStar(start, goal, map);

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
//                 else if (std::find_if(path.begin(), path.end(), [&](Node* node) { return node->x == i && node->y == j; }) != path.end())
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
