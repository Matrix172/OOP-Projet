cmake_minimum_required(VERSION 3.10)
project(myproject VERSION 1.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(myproject main.cpp)

# Plateaudejeu library
file(GLOB PLATEAU_SOURCES "Plateaudejeu/Plateaudejeu.cpp")
file(GLOB PLATEAU_HEADERS "Plateaudejeu/Plateaudejeu.hpp")
add_library(Plateaudejeu ${PLATEAU_SOURCES} ${PLATEAU_HEADERS})

# Entity library
file(GLOB ENTITY_SOURCES "Entity/Entity.cpp")
file(GLOB ENTITY_HEADERS "Entity/Entity.hpp")
add_library(Entity ${ENTITY_SOURCES} ${ENTITY_HEADERS})

# Player library
# file(GLOB PLAYER_SOURCES "Entity/Player/Player.cpp")
# file(GLOB PLAYER_HEADERS "Entity/Player/Player.hpp")
# add_library(Player ${PLAYER_SOURCES} ${PLAYER_HEADERS})

# # Ghost library
# file(GLOB GHOST_SOURCES "Entity/Ghost/Ghost.cpp")
# file(GLOB GHOST_HEADERS "Entity/Ghost/Ghost.hpp")
# add_library(Ghost ${GHOST_SOURCES} ${GHOST_HEADERS})

# # Ghost library
# file(GLOB GAME_SOURCES "Game/Game.cpp")
# file(GLOB GAME_HEADERS "Game/Game.hpp")
# add_library(Game ${GAME_SOURCES} ${GAME_HEADERS})


# Link libraries with the executable
target_link_libraries(myproject PRIVATE Plateaudejeu Entity)

# specify any libraries the executable depends on
#target_link_libraries(myproject PRIVATE pthread)

# specify where the executable should be installed
#install(TARGETS myproject DESTINATION bin)
