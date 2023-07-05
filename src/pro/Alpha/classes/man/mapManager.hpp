#pragma once

#include "../../include/tinyXML2/tinyxml2.h"
#include "../facade/xmlFacade.hpp"
#include "../utils/map_types.hpp"


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
        void  clearMap();


        void  GenerateObjects(XMLElem& objectsParent);
        void  GenerateRooms(XMLElem& objectsParent);

        //SHOULD USE TEMPLATE AND ONLY 1 GENERATE FUNCTION; DO IF SURPLUS TIME
        void  GenerateRoom(XMLElem& room);
        void  GenerateRoom_Trigger(XMLElem& room, room_trigger& trigger);
        void  GenerateRoom_Blockage(XMLElem& room, std::vector<room_blockage>& block);

        void  GenerateSpawners(XMLElem& spawners,std::vector<Spawner>& spawnerV);
        void  GenerateDoors(XMLElem& doors);
        void  assignSpawnInfo(Spawner& spawner,XMLElem& spawners );
        void  assignDoorInfo(DoorInfo& door,XMLElem& doors );
        //////////

        //GETTERS
        const int& getMaxBaseLayer() const;
        int   getTotalLayerCount() const;
        int   getActiveLayer() const;
        const std::string getTexturePath() const;
        const FVmath::Point2Di getMapSize() const;
        const FVmath::Point2Di getTileSize() const;
        const std::vector<int>& getCurrentLayer() const;
        const std::vector<FVmath::Point2Di>& getColliderData() const;
        std::vector<Spawner>& getSpawners() ;
        std::vector<DoorInfo>& getDoors() ;
        std::vector<Room>& getRooms() ;



        private:

        TileMap map_{};
        TileSet tile_{};
        std::vector<Spawner> SpawnersInfo_{};
        std::vector<DoorInfo> DoorsInfo_{};
        std::vector<std::vector<int>> mapRepresentation_ {};
        std::vector<Room> RoomsInfo_{};



        XMLReader xmlDoc_{};

    };
}