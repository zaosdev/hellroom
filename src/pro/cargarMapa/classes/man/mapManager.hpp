#pragma once

#include "../../include/tinyXML2/tinyxml2.h"
#include "../facade/xmlFacade.hpp"
#include <iostream>

namespace tXMLeng
{

    struct mapManager
    {

        mapManager() = default;

        mapManager (const mapManager&) = delete;
        mapManager (mapManager&&) = delete;
        mapManager& operator=(const mapManager&)= delete;
        mapManager& operator=(mapManager&&)= delete;
        
        void loadMap(const char * filePath);

        private:

        FVeng::xmlFacade<tinyxml2::XMLDocument, tinyxml2::XMLElement> t_xml_{};

    };
}