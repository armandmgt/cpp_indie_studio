set(SOURCE_FILES
        main.cpp

        engine/GameContainer.cpp
        ../include/engine/Components.hpp
        ../include/engine/GameContainer.hpp
        ../include/engine/Entity.hpp
        ../include/engine/systems/Systems.hpp
        ../include/engine/systems/MovementSystem.hpp
        ../include/engine/systems/MovementSystem.cpp
        ../include/engine/systems/ExplosionSystem.cpp
        ../include/engine/systems/ExplosionSystem.hpp

        world/World.cpp
        ../include/world/World.hpp

        map/Map.cpp
        ../include/map/Map.hpp

        gfx/EventReceiver.cpp
        ../include/gfx/EventReceiver.hpp
        ../include/event/Event.hpp
        ../srcs/event/Event.cpp
        gfx/Renderer.cpp
        ../include/gfx/Renderer.hpp
        ../include/gfx/Image2D.hpp

        menu/AMenu.cpp
        menu/Launch.cpp
        menu/Settings.cpp
        ../include/menu/AMenu.hpp
        ../include/menu/Launch.hpp
        ../include/menu/Settings.hpp

        settingManager/settingManager.cpp
        ../include/settingManager/settingManager.hpp

        scenes/ScenesManager.cpp
        ../include/scenes/IScene.hpp
        ../include/scenes/ScenesManager.hpp

        ../include/enum/Directions.hpp
        ../include/enum/AnimationType.hpp
        ../include/enum/EventEnum.hpp

        ../include/common/vec.hpp
        )

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 -lIrrlicht")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

#add_custom_command(TARGET bomberman POST_BUILD
#        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
