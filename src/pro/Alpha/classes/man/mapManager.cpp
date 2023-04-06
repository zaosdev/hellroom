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

            GenerateSpawners(mapElement);

        } 
        else 
        {
            xmlDoc_.printError();
        }
    }


    void mapManager::GenerateSpawners(XMLElem& map)
    {
        XMLElem spawners = map.FirstChildNamed("objectgroup").FirstChildNamed("object");

        while(spawners.isEmpty())
        {
            Spawner& spawner = SpawnerInfo_.emplace_back();

            assignSpawnInfo(spawner,spawners);

            spawners = spawners.NextSiblingNamed("object");
        }
    }

    void mapManager::assignSpawnInfo(Spawner& spawner,XMLElem& spawners )
    {

        spawners.queryAttribute<int*>("x", &spawner.SpawnOrigin.x);
        spawners.queryAttribute<int*>("y", &spawner.SpawnOrigin.y);
        spawners.queryAttribute<int*>("width", &spawner.SpawnRange.x);
        spawners.queryAttribute<int*>("height", &spawner.SpawnRange.y);

        int tempType{};
        
        auto Spawner_Type = spawners.FirstChildNamed("properties").FirstChildNamed("property"); 

        Spawner_Type.queryAttribute<int*>("value", &tempType);
        spawner.type = SpawnerType{tempType};

    }

    void mapManager::loadMap(XMLElem& map)
    {
            
            XMLElem layer = map.FirstChildNamed("group").FirstChildNamed("layer");

            while(layer.isEmpty())
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
                        std::cout << map_.tileMap[map_.numLayers].back() << "|";
                        std::cout << gid << "|";

                        currentTile = currentTile.NextSiblingNamed("tile");
                    }
                    std::cout << "" << std::endl;
                }
                map_.numLayers++;
                layer = layer.NextSiblingNamed("layer");
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

        img.queryAttribute<const char**>("source", &map_.filePath);
    }

    void mapManager::setActiveLayer(int newLayer)
    {
        map_.activeLayer = newLayer;
    }

    const char * mapManager::getTexturePath() const
    {
        return map_.filePath;
    }

    const FVmath::Point2Di mapManager::getMapSize() const
    {
        return map_.mapSize;
    }
    const FVmath::Point2Di mapManager::getTileSizePath() const
    {
        return map_.tileSize;

    }
    const std::vector<int>& mapManager::getCurrentLayer() const
    {
        return map_.tileMap[map_.activeLayer];

    }

    const int& mapManager::getMaxBaseLayer() const
    {
        return map_.maxBaseLayer;
    }

    int mapManager::getTotalLayerCount() const
    {
        return map_.tileMap.size();
    }

    std::vector<Spawner>& mapManager::getSpawners()
    {
        return SpawnerInfo_;
    }

}

