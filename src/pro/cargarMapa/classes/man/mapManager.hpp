#pragma once

#include "../../include/tinyXML2/tinyxml2.h"
#include "../facade/xmlFacade.hpp"
#include "../utils/math.hpp"

#include <vector>
#include <iostream>

namespace tXMLeng
{

    struct mapManager
    {

        using XMLReader = FVeng::xmlReader_facade<tinyxml2::XMLDocument,tinyxml2::XMLElement>;
        using XMLElem = FVeng::xmlElement_facade<tinyxml2::XMLElement>;
        #define DEFAULT_VALUE 345

        struct TileSet
        {
            FVmath::vec2Di tileSize{DEFAULT_VALUE,DEFAULT_VALUE};
            int tilecount   {DEFAULT_VALUE};
            int colummns    {DEFAULT_VALUE};

        };

        struct TileMap
        {
            FVmath::vec2Di mapSize{DEFAULT_VALUE,DEFAULT_VALUE};
            FVmath::vec2Di tileSize{DEFAULT_VALUE,DEFAULT_VALUE};
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
        void obtainMapInfo(XMLElem& map);
        void InitMap(const char * filePath);
        void setActiveLayer(int newLayer);
        const char * getTexturePath() const;
        FVmath::vec2Di getMapSize() const;
        FVmath::vec2Di getTileSizePath() const;
        std::vector<int>& getCurrentLayer();

        private:

        TileMap map_{};
        TileSet tile_{};

        XMLReader xmlDoc_{};

    };
}