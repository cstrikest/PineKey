message("Main file path: ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

cmake_minimum_required(VERSION 3.10)

project(PineKey)

set(SDL_LIB 
${CMAKE_CURRENT_SOURCE_DIR}/bin/SDL2.dll
${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2main.a
${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2.dll.a
${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2.a
${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2_test.a
)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui-docking)

set(MININI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/minini_13/minIni.c)

set(IMGUI_SOURCES 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

set(RESOURCE_FILES resources.rc)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(${PROJECT_NAME} main.cpp ${MININI_SOURCES} ${IMGUI_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR}/include/SDL2/ ${IMGUI_DIR} ${IMGUI_DIR}/backends)
    
target_link_libraries(${PROJECT_NAME} ${SDL_LIB} shell32.lib opengl32.lib gdi32.lib)

set_target_properties(PineKey PROPERTIES WIN32_EXECUTABLE TRUE)

target_sources(PineKey PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)

