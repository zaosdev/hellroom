#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/renderSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/inputSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/physicsSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/SpriteManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/mapManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/GameManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/inputManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/facade/inputFacade.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/achievementSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/soundSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/savingSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/AISys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/spawnSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/weaponSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/AI.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/circularIterator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/linearIterator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/gameData.cpp"    
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/healthSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/rewardSys.cpp"   
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/HUDSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/collisionSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/stateManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/petSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/shieldSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/effectSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/cofreSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/roomSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/animationSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/trapSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/leverSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/dialogueSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/bossSys.cpp"


)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

