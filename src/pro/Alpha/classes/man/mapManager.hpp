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
            FVmath::Point2Di tileSize{DEFAULT_VALUE,DEFAULT_VALUE};
            int tilecount   {DEFAULT_VALUE};
            int colummns    {DEFAULT_VALUE};

        };

        struct TileMap
        {
            FVmath::Point2Di mapSize{DEFAULT_VALUE,DEFAULT_VALUE};
            FVmath::Point2Di tileSize{DEFAULT_VALUE,DEFAULT_VALUE};
            int numLayers   {0};
            int activeLayer {0};
            int maxBaseLayer{0};

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
        int  getActiveLayer() const;
        const char * getTexturePath() const;
        const FVmath::Point2Di getMapSize() const;
        const FVmath::Point2Di getTileSizePath() const;
        const std::vector<int>& getCurrentLayer() const;
        const int& getMaxBaseLayer() const;
        int getTotalLayerCount() const;


        private:

        TileMap map_{};
        TileSet tile_{};

        XMLReader xmlDoc_{};

    };
}