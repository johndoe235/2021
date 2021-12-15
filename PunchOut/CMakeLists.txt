cmake_minimum_required(VERSION 3.10.2)

project(PunchOut LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)
  
  
if(UNIX)
    set(SDL_IMAGE_PKG_NAME SDL2_image)
    set(SDL_TTF_PKG_NAME SDL2_ttf)
    set(SDL_MIXER_PKG_NAME SDL2_mixer)
elseif(WIN32)
    set(SDL_IMAGE_PKG_NAME SDL2_IMAGE)
    set(SDL_TTF_PKG_NAME SDL2_TTF)
    set(SDL_MIXER_PKG_NAME SDL2_MIXER)
else()
    message("Error: Unsupported OS")
endif()
  
find_package(SDL2 REQUIRED)
find_package(${SDL_IMAGE_PKG_NAME} REQUIRED)
find_package(${SDL_TTF_PKG_NAME} REQUIRED)
find_package(${SDL_MIXER_PKG_NAME} REQUIRED)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#generate project binary

##add_executable(
  #  ${PROJECT_NAME}  
   #     ${_BASE_DIR}/main.cpp
#
 #       ${_BASE_DIR}/custom_h/Engine.h
  #      ${_BASE_DIR}/custom_h/Texture.h
   #     ${_BASE_DIR}/custom_h/SDLLoader.h 
    #    ${_BASE_DIR}/custom_h/Sound.h

     #   ${_BASE_DIR}/src/Engine.cpp
      #  ${_BASE_DIR}/src/Texture.cpp
       # ${_BASE_DIR}/src/SDLLoader.cpp
        #${_BASE_DIR}/src/Sound.cpp

#)

add_executable (
    ${PROJECT_NAME}  
        ${BASE_DIR}/main.cpp
      ${BASE_DIR}/engine/include/GameMakerEngine.h 
      ${BASE_DIR}/engine/include/Renderer.h
      ${BASE_DIR}/engine/include/SDLLoader.h 
      ${BASE_DIR}/engine/include/Timer.h 
      ${BASE_DIR}/engine/include/Window.h
      ${BASE_DIR}/engine/include/Texture.h
      ${BASE_DIR}/engine/include/Event.h
      ${BASE_DIR}/engine/include/Mouse.h
      ${BASE_DIR}/engine/include/GameObject.h
      ${BASE_DIR}/engine/include/utils/Font.h
      ${BASE_DIR}/engine/include/Text.h
      ${BASE_DIR}/engine/include/Image.h
      ${BASE_DIR}/engine/include/cnfg/WindowCnfg.h
      ${BASE_DIR}/engine/include/utils/shape/Point.h
      ${BASE_DIR}/engine/include/sound/Chunk.h

      ${BASE_DIR}/engine/include/managers/DrawManager.h
      ${BASE_DIR}/engine/include/managers/ResourceManager.h

      ${BASE_DIR}/engine/lib/managers/DrawManager.cpp
      ${BASE_DIR}/engine/lib/managers/ResourceManager.cpp

      ${BASE_DIR}/engine/lib/GameMakerEngine.cpp 
      ${BASE_DIR}/engine/lib/Renderer.cpp
      ${BASE_DIR}/engine/lib/SDLLoader.cpp
      ${BASE_DIR}/engine/lib/Window.cpp 
      ${BASE_DIR}/engine/lib/Timer.cpp
      ${BASE_DIR}/engine/lib/Texture.cpp  
      ${BASE_DIR}/engine/lib/Event.cpp 
      ${BASE_DIR}/engine/lib/Mouse.cpp
      ${BASE_DIR}/engine/lib/GameObject.cpp
      ${BASE_DIR}/engine/lib/Text.cpp
      ${BASE_DIR}/engine/lib/Image.cpp

      ${BASE_DIR}/game/include/Game.h
      ${BASE_DIR}/game/include/menu/Menu.h
      ${BASE_DIR}/game/include/menu/Button.h
      ${BASE_DIR}/game/include/timers/PunchOutTimer.h
      ${BASE_DIR}/game/include/timers/lilMacTimers.h
      ${BASE_DIR}/game/include/timers/glassJoeTimers.h
      ${BASE_DIR}/game/include/timers/RoundTimers.h
      ${BASE_DIR}/game/include/boxers/Boxer.h
      ${BASE_DIR}/game/include/boxers/lilMac.h
      ${BASE_DIR}/game/include/boxers/glassJoe.h

      ${BASE_DIR}/game/include/fight/FightManager.h
      ${BASE_DIR}/game/include/fight/Ring.h
      ${BASE_DIR}/game/include/fight/Round.h
      ${BASE_DIR}/game/include/fight/Lifebar.h
      ${BASE_DIR}/game/include/fight/Referee.h
      ${BASE_DIR}/game/include/fight/PointSystem.h

      ${BASE_DIR}/game/src/Game.cpp
      ${BASE_DIR}/game/src/Input.cpp
      ${BASE_DIR}/game/src/menu/Menu.cpp
      ${BASE_DIR}/game/src/menu/Button.cpp
      ${BASE_DIR}/game/src/timers/PunchOutTimer.cpp
      ${BASE_DIR}/game/src/timers/lilMacTimers.cpp
      ${BASE_DIR}/game/src/timers/glassJoeTimers.cpp
      ${BASE_DIR}/game/src/timers/RoundTimers.cpp
      ${BASE_DIR}/game/src/timers/RefereeTimers.cpp
      ${BASE_DIR}/game/src/boxers/Boxer.cpp
      ${BASE_DIR}/game/src/boxers/lilMac.cpp
      ${BASE_DIR}/game/src/boxers/glassJoe.cpp

      ${BASE_DIR}/game/src/fight/FightManager.cpp
      ${BASE_DIR}/game/src/fight/Ring.cpp
      ${BASE_DIR}/game/src/fight/Round.cpp
      ${BASE_DIR}/game/src/fight/Lifebar.cpp
      ${BASE_DIR}/game/src/fight/Referee.cpp
      ${BASE_DIR}/game/src/fight/PointSystem.cpp

     
)



set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE 
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            ${SDL2_LIBRARY}       # -lSDL2 flag
            ${SDL2_IMAGE_LIBRARY} # -lSDL2_image flag
            ${SDL2_TTF_LIBRARY}   # -lSDL2_ttf flag
            ${SDL2_MIXER_LIBRARY} # -lSDL2_mixer flag  
)




