#pragma once

#include "../../include/tinyXML2/tinyxml2.h"
#include "../facade/xmlFacade.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

namespace tXMLeng
{

    struct mapManager
    {

        using XMLReader = FVeng::xmlReader_facade<tinyxml2::XMLDocument,tinyxml2::XMLElement>;
        using XMLElem = FVeng::xmlElement_facade<tinyxml2::XMLElement>;
        #define DEFAULT_VALUE 345

        struct TileSet
        {
            int tileWidth   {DEFAULT_VALUE};
            int tileHeight  {DEFAULT_VALUE};
            int tilecount   {DEFAULT_VALUE};
            int colummns    {DEFAULT_VALUE};
        };

        struct TileMap
        {
            int width       {DEFAULT_VALUE};
            int height      {DEFAULT_VALUE};
            int tileWidth   {DEFAULT_VALUE};
            int tileHeight  {DEFAULT_VALUE};
            int numLayers   {0};
            int activeLayer {0};

            std::vector<std::vector<int>> tileMap{};

            const char* filePath{};



        };

        mapManager() = default;

        mapManager (const mapManager&) = delete;
        mapManager (mapManager&&) = delete;
        mapManager& operator=(const mapManager&)= delete;
        mapManager& operator=(mapManager&&)= delete;
        
        void loadMap(XMLElem& map);
        void obtainMapTexturePath(XMLElem& map);
        void loadTileSet(const char * filePath);
        void obtainMapInfo(XMLElem& map);
        void InitMap(const char * filePath);
        void setActiveLayer(int newLayer);
        const char * getTexturePath() const;






        private:

        TileMap map_{};
        XMLReader xmlDoc_{};

    };
}