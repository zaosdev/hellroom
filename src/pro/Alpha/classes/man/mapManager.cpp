#include "mapManager.hpp"
#include <cassert>


namespace tXMLeng
{

    void mapManager::InitMap(const char * filePath)
    {
        xmlDoc_.loadFile(filePath);
        
        XMLElem mapElement = xmlDoc_.FirstChildOnDocument("map");

        xmlDoc_.printError();

        if (!mapElement.isEmpty()) 
        {
            obtainMapInfo(mapElement);

            obtainMapTexturePath(mapElement);

            loadMap(mapElement);

            loadColliders(mapElement);

            GenerateObjects(mapElement);

            GenerateRooms(mapElement);

        } 
        else 
        {
            xmlDoc_.printError();
        }
    }

    void mapManager::GenerateObjects(XMLElem& map)
    {
        XMLElem spawners = map.FindFirstChildwithName("objectgroup","spawner");
        assert(not spawners.isEmpty() && "There must be an spawner object group even if empty");
        GenerateSpawners(spawners, SpawnersInfo_);
		
        XMLElem doors = map.FindFirstChildwithName("objectgroup","door");
        assert(not doors.isEmpty() && "There must be a door object group even if empty");
        GenerateDoors(doors);
    }

    void mapManager::GenerateRooms(XMLElem& map)
    {
        auto rooms = map.FindFirstChildwithName("group","rooms");

        auto currentRoom = rooms.FirstChildNamed("group");

        while (!currentRoom.isEmpty())
        {
            GenerateRoom(currentRoom);

            currentRoom = currentRoom.NextSiblingNamed("group");
        }
        
    }

    void mapManager::GenerateRoom(XMLElem& room)
    {
        auto& roomInfo = RoomsInfo_.emplace_back();

        XMLElem trigger = room.FindFirstChildwithName("objectgroup","room_trigger");
        assert(not trigger.isEmpty() && "There must be a rooom trigger object group even if empty");
        GenerateRoom_Trigger(trigger, roomInfo.trigger);

        XMLElem blocks = room.FindFirstChildwithName("objectgroup","wall");
        assert(not blocks.isEmpty() && "There must be a wall object group even if empty");
        GenerateRoom_Blockage(blocks, roomInfo.blocks);


        XMLElem spawners = room.FindFirstChildwithName("objectgroup","spawner");
        assert(not spawners.isEmpty() && "There must be an spawner object group even if empty");
        GenerateSpawners(spawners, roomInfo.spawners);

    }

    void  mapManager::GenerateRoom_Trigger(XMLElem& room, room_trigger& trigger)
    {
       auto triggerElem = room.FirstChildNamed("object");

       triggerElem.queryAttribute<int*>("x", &trigger.pos.x);
       triggerElem.queryAttribute<int*>("y", &trigger.pos.y);
       triggerElem.queryAttribute<int*>("width", &trigger.size.x);
       triggerElem.queryAttribute<int*>("height", &trigger.size.y);
    }

    void  mapManager::GenerateRoom_Blockage(XMLElem& room, std::vector<room_blockage>& blocks)
    {
		auto wall = room.FirstChildNamed("object");

		while (!wall.isEmpty())
		{
			auto& wallInfo = blocks.emplace_back(); 

			wall.queryAttribute<int*>("x", &wallInfo.pos.x);
       		wall.queryAttribute<int*>("y", &wallInfo.pos.y);
       		wall.queryAttribute<int*>("width", &wallInfo.size.x);
       		wall.queryAttribute<int*>("height", &wallInfo.size.y);

			wall = wall.NextSiblingNamed("object");
		}
		


    }

    void mapManager::GenerateSpawners(XMLElem& spawners, std::vector<Spawner>& spawnerV)
    {
        XMLElem spawner = spawners.FirstChildNamed("object");

        while(!spawner.isEmpty())
        {
            Spawner& spawnerInfo = spawnerV.emplace_back();

            assignSpawnInfo(spawnerInfo,spawner);

            spawner = spawner.NextSiblingNamed("object");
        }
    }

    void mapManager::assignSpawnInfo(Spawner& spawner,XMLElem& spawners )
    {

        spawners.queryAttribute<int*>("x", &spawner.SpawnOrigin.x);
        spawners.queryAttribute<int*>("y", &spawner.SpawnOrigin.y);
        spawners.queryAttribute<int*>("width", &spawner.SpawnRange.x);
        spawners.queryAttribute<int*>("height", &spawner.SpawnRange.y);

        int tempType{};
        
        auto spawner_properties = spawners.FirstChildNamed("properties");
        
        auto spawner_type = spawner_properties.FindFirstChildwithName("property","type"); 

        spawner_type.queryAttribute<int*>("value", &tempType);
        spawner.type = tXMLeng::object_type(1 << tempType);

        if(spawner.type & tXMLeng::object_type::ENEMY)
        {
            
            auto enemy_type = spawner_properties.FindFirstChildwithName("property","enemy"); 
        
            enemy_type.queryAttribute<int*>("value", &tempType);
            spawner.enemy_spawned = game::enemy_type(1 << tempType);
        }

    }

    void mapManager::GenerateDoors(XMLElem& doors)
    {
        XMLElem door = doors.FirstChildNamed("object");

        while(!door.isEmpty())
        {
            DoorInfo& doorInfo = DoorsInfo_.emplace_back();

            assignDoorInfo(doorInfo,door);

            door= door.NextSiblingNamed("object");
        }
    }

    void mapManager::assignDoorInfo(DoorInfo& door,XMLElem& doors )
    {

       doors.queryAttribute<int*>("x", &door.pos.x);
       doors.queryAttribute<int*>("y", &door.pos.y);
       doors.queryAttribute<int*>("width", &door.size.x);
       doors.queryAttribute<int*>("height", &door.size.y);

        const char* temp_next_level{};
        
        auto door_properties =doors.FirstChildNamed("properties");
        
        auto next_level = door_properties.FirstChildNamed("property"); 

        next_level.queryAttribute<const char**>("value", &temp_next_level);
        door.next_level_path = temp_next_level;
    }

    void mapManager::loadMap(XMLElem& map)
    {
            
            XMLElem layer = map.FirstChildNamed("group").FirstChildNamed("layer");

            while(!layer.isEmpty())
            {
                map_.tileMap.emplace_back();
                map_.tileMap[map_.numLayers].reserve(map_.mapSize.y*map_.mapSize.x);
                
                auto currentTile = layer.FirstChildNamed("data").FirstChildNamed("tile") ; 
                for(int y{0}; y<map_.mapSize.y; y++)
                {
                    for(int x{0}; x<map_.mapSize.x; x++)
                    {
                        int& gid = map_.tileMap[map_.numLayers].emplace_back();
                        currentTile.queryAttribute<int*>("gid",&gid);
                        gid-=1;

                        currentTile = currentTile.NextSiblingNamed("tile");
                    }
                }
                map_.numLayers++;
                layer = layer.NextSiblingNamed("layer");
            }

    }

   void imprimirMapa(const std::vector<std::vector<int>>& mapRepresentation) 
   {
        const size_t numRows = mapRepresentation.size();
        const size_t numCols = mapRepresentation[0].size();

        for (size_t j = 0; j < numCols; ++j) {
            for (size_t i = 0; i < numRows; ++i) {
                std::cout << mapRepresentation[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }


    std::vector<std::vector<int>>& mapManager::getMapGridRepresentation()
    {
        return mapRepresentation_;
    }

    void mapManager::loadColliders(XMLElem& map)
    {
        auto filas = map_.mapSize.y;
        auto columnas = map_.mapSize.x;
        mapRepresentation_.resize(filas, std::vector<int>(columnas, 0));    
        // XMLElem groups = map.FirstChildNamed("group");
        // XMLElem colliderData = groups.NextSiblingNamed("group").FirstChildNamed("layer");

        XMLElem colliderData = map.FindFirstChildwithName("group","collData").FirstChildNamed("layer");
        map_.colliderLayer.reserve(map_.mapSize.y*map_.mapSize.x);
            
        auto currentTile = colliderData.FirstChildNamed("data").FirstChildNamed("tile") ; 
        for(int y{0}; y<map_.mapSize.y; y++)
        {
            for(int x{0}; x<map_.mapSize.x; x++)
            {

                int tempGid{};
                currentTile.queryAttribute<int*>("gid",&tempGid);

                if(tempGid==MAGIC_COLL_NUMBER)
                {
                    FVmath::Point2Di& posColl = map_.colliderLayer.emplace_back();

                    posColl.x = x*map_.tileSize.x;
                    posColl.y = y*map_.tileSize.y;

                    //Create the grid representation of the map to use the pathfinding
                    mapRepresentation_[x][y] = 1;
                }

                currentTile = currentTile.NextSiblingNamed("tile");
            }
        }
        imprimirMapa(mapRepresentation_);
    }


    void mapManager::obtainMapInfo(XMLElem& map)
    {
        map.queryAttribute<int*>("width", &map_.mapSize.x);
        map.queryAttribute<int*>("height", &map_.mapSize.y);
        map.queryAttribute<int*>("tilewidth", &map_.tileSize.x);
        map.queryAttribute<int*>("tileheight", &map_.tileSize.y);
        map.queryAttribute<int*>("maxBaseLayer", &map_.maxBaseLayer);

    }

    void mapManager::clearMap()
    {
        map_.colliderLayer.clear();
        map_.tileMap.clear();
        SpawnersInfo_.clear();
        DoorsInfo_.clear();
        map_ = TileMap{};
    }


    int  mapManager::getActiveLayer() const
    {
        return map_.activeLayer;
    }


    void mapManager::obtainMapTexturePath(XMLElem& map)
    {
        XMLElem tsxElement = map.FirstChildNamed("tileset");

        const char* tsxPath;

        tsxElement.queryAttribute<const char**>("source",&tsxPath);

        XMLReader tempDoc{};
        std::cout << tsxPath;

        tempDoc.loadFile(tsxPath);
        xmlDoc_.printError();

        XMLElem tileSet = tempDoc.FirstChildOnDocument("tileset");

        XMLElem img = tileSet.FirstChildNamed("image");

        const char * tempFilePath{};

        img.queryAttribute<const char**>("source", &tempFilePath);

        map_.filePath = tempFilePath;

        std::cout << "img path" << map_.filePath << std::endl;

    }

    void mapManager::setActiveLayer(int newLayer)
    {
        map_.activeLayer = newLayer;
    }

    const std::string mapManager::getTexturePath() const
    {
        return map_.filePath;
    }

    const FVmath::Point2Di mapManager::getMapSize() const
    {
        return map_.mapSize;
    }
    const FVmath::Point2Di mapManager::getTileSize() const
    {
        return map_.tileSize;

    }
    const std::vector<int>& mapManager::getCurrentLayer() const
    {
        return map_.tileMap[map_.activeLayer];

    }

    const std::vector<FVmath::Point2Di>& mapManager::getColliderData() const
    {
        return map_.colliderLayer;
    }

    const int& mapManager::getMaxBaseLayer() const
    {
        return map_.maxBaseLayer;
    }

    int mapManager::getTotalLayerCount() const
    {
        return map_.tileMap.size();
    }

    //LOOK WHY THIS METHOD CANT BE CONST
    std::vector<Spawner>& mapManager::getSpawners() 
    {
        return SpawnersInfo_;
    }

    //LOOK WHY THIS METHOD CANT BE CONST
    std::vector<DoorInfo>& mapManager::getDoors() 
    {
        return DoorsInfo_;
    }

    std::vector<Room>& mapManager::getRooms() 
    {
        return RoomsInfo_;
    }

}

