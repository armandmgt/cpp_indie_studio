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
    set(CMAKE_CXX_FLAGS "/W4 /permissive")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor -Wfatal-errors")
endif()

add_executable(bomberman ${SOURCE_FILES})
	
if (WIN32)
   LINK_DIRECTORIES("../")
   target_link_libraries(bomberman "../../srcs/Irrlicht")
	add_custom_command(TARGET bomberman POST_BUILD
	COMMAND cmd /c "start ${CMAKE_SOURCE_DIR}/WinSetupDirectory.bat")
endif()