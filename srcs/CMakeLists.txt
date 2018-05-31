set(SOURCE_FILES
        main.cpp
		../include/engine/GameContainer.hpp
		../include/engine/Components.hpp

		../include/interfaces/IPlayer.hpp
		../include/interfaces/IObject.hpp
		../include/interfaces/IItem.hpp

		../include/common/vec.hpp

	        ../include/enum/AnimationType.hpp
	        ../include/enum/Directions.hpp
		../include/engine/Entity.hpp
		world/World.cpp
		../include/world/World.hpp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

add_custom_command(TARGET bomberman POST_BUILD
        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
