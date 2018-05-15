set(SOURCE_FILES
        main.cpp
        engine/GameContainer.cpp
        ../include/engine/GameContainer.hpp
        engine/GameEngine.cpp
        ../include/engine/GameEngine.hpp
        ../include/common/vec.hpp
        ../include/enum/AnimationType.hpp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4")
else()
    set(CMAKE_CXX_FLAGS "-W -Wall")
endif()

add_executable(bomberman ${SOURCE_FILES})

target_link_libraries(bomberman Irrlicht)

add_custom_command(TARGET bomberman POST_BUILD
        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
