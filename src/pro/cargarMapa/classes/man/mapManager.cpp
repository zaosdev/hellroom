#include "mapManager.hpp"



namespace tXMLeng
{

    void mapManager::loadMap(const char* filePath)
    {
            
        t_xml_.loadFile(filePath);
        
        auto* mapElement = t_xml_.FirstChildElement("map");
        t_xml_.printError();

        int width = 345, height = 345, tileWidth = 345, tileHeight = 345;
        bool coll = false;
        if (mapElement) 
        {
            t_xml_.queryAttribute<bool*>(mapElement, "collider", &coll); 
            t_xml_.queryAttribute<int*>(mapElement,"width", &width);
            t_xml_.queryAttribute<int*>(mapElement,"height", &height);
            t_xml_.queryAttribute<int*>(mapElement,"tilewidth", &tileHeight);
            t_xml_.queryAttribute<int*>(mapElement,"tileheight", &tileWidth);

        } else {
            t_xml_.printError();
        }
    }
}

