set(SOURCE_FILES
        main.cpp
        ../include/engine/Components.hpp
        ../include/engine/GameContainer.hpp
        engine/GameContainer.cpp

		../include/common/vec.hpp

        ../include/enum/AnimationType.hpp
	    ../include/enum/Directions.hpp
		../include/engine/Entity.hpp
		world/World.cpp
		../include/world/World.hpp
        ../include/engine/systems/Systems.hpp
        ../include/engine/systems/MovementSystem.hpp
        ../include/engine/systems/MovementSystem.cpp

		map/Map.cpp
		../include/map/Map.hpp
        ../include/common/vec.hpp
        ../include/enum/AnimationType.hpp
        gfx/Renderer.cpp
        ../include/gfx/Renderer.hpp gfx/EventReceiver.cpp
        ../include/gfx/EventReceiver.hpp
		../include/event/Event.hpp
		../srcs/event/Event.cpp
		../include/enum/EventEnum.hpp
        settingManager/settingManager.cpp
        ../include/settingManager/settingManager.hpp
        ../include/gfx/Image2D.hpp
        ../include/scenes/IScene.hpp
        ../include/menu/AMenu.hpp
        menu/AMenu.cpp
        ../include/menu/Launch.hpp
        menu/Launch.cpp
        ../include/menu/Settings.hpp
        menu/Settings.cpp
        ../include/scenes/ScenesManager.hpp
        scenes/ScenesManager.cpp
        ../include/gfx/Image2D.hpp
        ../include/engine/systems/Systems.hpp
        ../include/engine/systems/MovementSystem.cpp
        ../include/engine/systems/MovementSystem.hpp
        ../include/engine/systems/ExplosionSystem.cpp
        ../include/engine/systems/ExplosionSystem.hpp
		../include/scenes/GameScene.cpp
		../include/scenes/GameScene.hpp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 -lIrrlicht")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

#add_custom_command(TARGET bomberman POST_BUILD
#        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
