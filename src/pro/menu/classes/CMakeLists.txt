#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/renderSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/inputSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/physicsSys.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/SpriteManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/GameManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/man/Menu.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

