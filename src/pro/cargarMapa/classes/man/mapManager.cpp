#include "mapManager.hpp"



namespace tXMLeng
{

    void mapManager::loadMap(const char* filePath)
    {
            
        xmlDoc_.loadFile(filePath);
        
        XMLElem mapElement = xmlDoc_.FirstChildOnDocument("map");
        xmlDoc_.printError();

        if (mapElement.isEmpty()) 
        {

            mapElement.queryAttribute<int*>("width", &map_.width);
            mapElement.queryAttribute<int*>("height", &map_.height);
            mapElement.queryAttribute<int*>("tilewidth", &map_.tileHeight);
            mapElement.queryAttribute<int*>("tileheight", &map_.tileWidth);

            XMLElem tsxElement = mapElement.FirstChildNamed("tileset");

            tsxElement.queryAttribute<const char**>("source",&map_.filePath);

            XMLElem layer = mapElement.FirstChildNamed("layer");

            while(layer.isEmpty())
            {
                map_.tileMap.emplace_back();
                map_.tileMap[map_.numLayers].reserve(map_.height*map_.width);
                
                auto currentTile = layer.FirstChildNamed("data").FirstChildNamed("tile") ; 
                for(int y{0}; y<map_.height; y++)
                {
                    for(int x{0}; x<map_.width; x++)
                    {
                        int& gid = map_.tileMap[map_.numLayers].emplace_back();
                        currentTile.queryAttribute<int*>("gid",&gid);
                        // std::cout << gid << "|";
                        currentTile = currentTile.NextSiblingNamed("tile");
                    }
                    //std::cout << "" << std::endl;
                }
                map_.numLayers++;
                layer = layer.NextSiblingNamed("layer");
            }


        } else {
            xmlDoc_.printError();
        }
    }
}

