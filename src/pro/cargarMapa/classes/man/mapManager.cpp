#include "mapManager.hpp"



namespace tXMLeng
{

    void mapManager::InitMap(const char * filePath)
    {
        xmlDoc_.loadFile(filePath);
        
        XMLElem mapElement = xmlDoc_.FirstChildOnDocument("map");
        xmlDoc_.printError();

        if (mapElement.isEmpty()) 
        {
            obtainMapInfo(mapElement);

            obtainMapTexturePath(mapElement);

            loadMap(mapElement);
        } 
        else {
            xmlDoc_.printError();
        }
    }

    void mapManager::loadMap(XMLElem& map)
    {
            
            XMLElem layer = map.FirstChildNamed("layer");

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

    }


    void mapManager::obtainMapInfo(XMLElem& map)
    {
        map.queryAttribute<int*>("width", &map_.width);
        map.queryAttribute<int*>("height", &map_.height);
        map.queryAttribute<int*>("tilewidth", &map_.tileHeight);
        map.queryAttribute<int*>("tileheight", &map_.tileWidth);
    }


    void mapManager::obtainMapTexturePath(XMLElem& map)
    {
        XMLElem tsxElement = map.FirstChildNamed("tileset");

        tsxElement.queryAttribute<const char**>("source",&map_.filePath);
    }

    void mapManager::setActiveLayer(int newLayer)
    {
        map_.activeLayer = newLayer;
    }

    const char * mapManager::getTexturePath() const
    {
        return map_.filePath;
    }


}

