set(SOURCE_FILES
        main.cpp

        engine/GameContainer.cpp
        ../include/engine/Components.hpp
        ../include/engine/GameContainer.hpp
        ../include/engine/Entity.hpp
        ../include/engine/systems/Systems.hpp
        ../include/engine/systems/MovementSystem.hpp
        ../include/engine/systems/ExplosionSystem.hpp

        ../include/engine/ai/PlayerAI.cpp
        ../include/engine/ai/PlayerAI.hpp

        world/World.cpp
        ../include/world/World.hpp

        map/Map.cpp
        ../include/map/Map.hpp

        event/EventReceiver.cpp
        ../include/event/EventReceiver.hpp
        ../include/event/Event.hpp
        ../srcs/event/Event.cpp
        gfx/Renderer.cpp
        ../include/gfx/Renderer.hpp
        ../include/gfx/Image2D.hpp

        menu/AMenu.cpp
        menu/Launch.cpp
        menu/Settings.cpp
        menu/LoadGame.cpp
        menu/Pause.cpp
        ../include/menu/AMenu.hpp
        ../include/menu/Launch.hpp
        ../include/menu/Settings.hpp
        ../include/menu/LoadGame.hpp
        ../include/menu/Pause.hpp

        ../include/music/Music.hpp
        music/Music.cpp

        settingManager/settingManager.cpp
        ../include/settingManager/settingManager.hpp

        scenes/ScenesManager.cpp
        ../include/scenes/GameScene.cpp
        ../include/scenes/GameScene.hpp
        ../include/scenes/IScene.hpp
        ../include/scenes/ScenesManager.hpp

        ../include/enum/Directions.hpp
        ../include/enum/AnimationType.hpp
        ../include/enum/EventEnum.hpp

        ../include/common/vec.hpp
        engine/systems/PlayerMovement.cpp
        ../include/engine/systems/PlayerMovement.hpp
        engine/systems/ParseInputSystem.cpp
        engine/systems/ExplosionSystem.cpp
        ../include/engine/systems/ParseInputSystem.hpp
        engine/systems/PutBombSystem.cpp
        ../include/engine/systems/PutBombSystem.hpp
        engine/systems/DespawnSystem.cpp
        ../include/engine/systems/DespawnSystem.hpp
        engine/systems/BreakDestructibleSystem.cpp
        ../include/engine/systems/BreakDestructibleSystem.hpp
        engine/Entity.cpp
        engine/systems/MovementSystem.cpp
        engine/systems/PlayerRotationSystem.cpp
        ../include/engine/systems/PlayerRotationSystem.hpp engine/systems/PowerUpRotationSystem.cpp ../include/engine/systems/PowerUpRotationSystem.hpp engine/systems/PowerUpPickupSystem.cpp ../include/engine/systems/PowerUpPickupSystem.hpp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /permissive")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor -Wfatal-errors")
endif()

add_executable(bomberman ${SOURCE_FILES})

if (WIN32)
    link_directories("../")
    target_link_libraries(bomberman "../../srcs/Irrlicht" "../../srcs/sfml-audio")
    add_custom_command(TARGET bomberman POST_BUILD
        COMMAND cmd /c "start ${CMAKE_SOURCE_DIR}/WinSetupDirectory.bat")
else ()
    target_link_libraries(bomberman Irrlicht sfml-audio)
endif()