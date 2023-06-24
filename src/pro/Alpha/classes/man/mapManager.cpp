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
        GenerateSpawners(spawners);
        XMLElem doors = map.FindFirstChildwithName("objectgroup","door");
        assert(not doors.isEmpty() && "There must be a door object group even if empty");
        GenerateDoors(doors);
    }

    void mapManager::GenerateSpawners(XMLElem& spawners)
    {
        XMLElem spawner = spawners.FirstChildNamed("object");

        while(!spawner.isEmpty())
        {
            Spawner& spawnerInfo = SpawnersInfo_.emplace_back();

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
        
        auto spawner_type = spawner_properties.FirstChildNamed("property"); 

        spawner_type.queryAttribute<int*>("value", &tempType);
        spawner.type = object_type{1 << tempType};

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
    

    void mapManager::loadColliders(XMLElem& map)
    {
            
        XMLElem groups = map.FirstChildNamed("group");
        XMLElem colliderData = groups.NextSiblingNamed("group").FirstChildNamed("layer");
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
                }

                currentTile = currentTile.NextSiblingNamed("tile");
            }
        }
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

}

