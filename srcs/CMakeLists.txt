set(SOURCE_FILES
        main.cpp
        ../include/engine/Components.hpp

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
        ../include/gfx/Renderer.hpp gfx/EventReceiver.cpp
        ../include/gfx/EventReceiver.hpp
		../include/event/Event.hpp
		../srcs/event/Event.cpp
		../include/enum/EventEnum.hpp
        settingManager/settingManager.cpp
        ../include/settingManager/settingManager.hpp ../include/gfx/Image2D.hpp
        Menu/AMenu.cpp
        ../include/menu/AMenu.hpp ../include/IScene.hpp ../include/menu/Launch.hpp
        Menu/Launch.cpp)
if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 -lIrrlicht")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

#add_custom_command(TARGET bomberman POST_BUILD
#        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
