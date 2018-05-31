set(SOURCE_FILES
        main.cpp
        ../include/common/vec.hpp
        ../include/enum/AnimationType.hpp
        gfx/Renderer.cpp
        ../include/gfx/Renderer.hpp gfx/EventReceiver.cpp
        ../include/gfx/EventReceiver.hpp
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

add_custom_command(TARGET bomberman POST_BUILD
        COMMAND cp bomberman ${CMAKE_SOURCE_DIR})
