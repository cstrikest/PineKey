message("Main file path: ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

cmake_minimum_required(VERSION 3.10)

project(PineKey)

# SDL2 paths
set(SDL2_INCLUDE_DIR C:/Pine/Prog/PineKey/include/SDL2)
set(SDL2_LIBRARY C:/Pine/Prog/PineKey/bin/SDL2.dll)

# imgui paths
set(IMGUI_DIR C:/Pine/Prog/PineKey/imgui-master)

# imgui source files
set(IMGUI_SOURCES 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(${PROJECT_NAME} main.cpp KeyHook.cpp ${IMGUI_SOURCES})

include_directories(${SDL2_INCLUDE_DIR} ${IMGUI_DIR} ${IMGUI_DIR}/backends)
    
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} opengl32.lib)

# TODO: Additional setup if needed
