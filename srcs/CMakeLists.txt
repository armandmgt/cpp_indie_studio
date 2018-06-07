set(SOURCE_FILES
        main.cpp
        ../include/engine/Components.hpp

		../include/interfaces/IPlayer.hpp
		../include/interfaces/IObject.hpp
		../include/interfaces/IItem.hpp

		../include/common/vec.hpp

        ../include/enum/AnimationType.hpp
	    ../include/enum/Directions.hpp
		../include/engine/Entity.hpp
		world/World.cpp
		../include/world/World.hpp

		map/Map.cpp
		../include/map/Map.hpp
        ../include/common/vec.hpp
        ../include/enum/AnimationType.hpp
        gfx/Renderer.cpp
        ../include/gfx/Renderer.hpp event/EventReceiver.cpp
        ../include/event/EventReceiver.hpp
        ../include/enum/EventEnum.hpp
        settingManager/settingManager.cpp
        ../include/settingManager/settingManager.hpp
        ../include/gfx/Image2D.hpp ../include/engine/systems/Systems.hpp ../include/engine/systems/MovementSystem.cpp ../include/engine/systems/MovementSystem.hpp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 -lIrrlicht")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

#add_custom_command(TARGET bomberman POST_BUILD
#        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
