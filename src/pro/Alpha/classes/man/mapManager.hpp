#pragma once

#include "../../include/tinyXML2/tinyxml2.h"
#include "../facade/xmlFacade.hpp"
#include "../utils/Spawner.hpp"


#include <vector>
#include <iostream>
#include <string>


namespace tXMLeng
{

    struct mapManager
    {

        using XMLReader = FVeng::xmlReader_facade<tinyxml2::XMLDocument,tinyxml2::XMLElement>;
        using XMLElem = FVeng::xmlElement_facade<tinyxml2::XMLElement>;
        #define DEFAULT_VALUE 345
        static constexpr int MAGIC_COLL_NUMBER = 387;

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
            std::vector<FVmath::Point2Di> colliderLayer{};

            std::string filePath{};

        };



        mapManager() = default;

        mapManager (const mapManager&) = delete;
        mapManager (mapManager&&) = delete;
        mapManager& operator=(const mapManager&)= delete;
        mapManager& operator=(mapManager&&)= delete;
        
        void  loadMap(XMLElem& map);
        void  loadColliders(XMLElem& map);
        void  obtainMapTexturePath(XMLElem& map);
        void  obtainMapInfo(XMLElem& map);
        void  InitMap(const char * filePath);
        void  setActiveLayer(int newLayer);
        int   getActiveLayer() const;
        const std::string getTexturePath() const;
        const FVmath::Point2Di getMapSize() const;
        const FVmath::Point2Di getTileSize() const;
        const std::vector<int>& getCurrentLayer() const;
        const std::vector<FVmath::Point2Di>& getColliderData() const;

        const int& getMaxBaseLayer() const;
        int   getTotalLayerCount() const;
        void  GenerateSpawners(XMLElem& spawners);
        void  assignSpawnInfo(Spawner& spawner,XMLElem& spawners );
        std::vector<Spawner>& getSpawners();

        private:

        TileMap map_{};
        TileSet tile_{};
        std::vector<Spawner> SpawnerInfo_{};

        XMLReader xmlDoc_{};

    };
}