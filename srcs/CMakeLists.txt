set(SOURCE_FILES
        main.cpp
        engine/GameContainer.cpp
        ../include/engine/GameContainer.hpp

		engine/GameEngine.cpp
		../include/engine/GameEngine.hpp

		../include/interfaces/IPlayer.hpp
		../include/interfaces/IObject.hpp
		../include/interfaces/IItem.hpp

		../include/entities/Player.hpp
		../include/entities/Item.hpp
		../include/entities/Object.hpp

		../include/common/vec.hpp

        ../include/enum/AnimationType.hpp
        ../include/enum/Directions.hpp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

add_custom_command(TARGET bomberman POST_BUILD
        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
