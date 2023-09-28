message("Main file path: ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

cmake_minimum_required(VERSION 3.10)

project(PineKey)


set(GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.dll)

# imgui paths
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui-docking)

# imgui source files
set(IMGUI_SOURCES 
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)

set(RESOURCE_FILES resources.rc)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(${PROJECT_NAME} main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/minini_13/minIni.c ${IMGUI_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ ${IMGUI_DIR} ${IMGUI_DIR}/backends)
    
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLFW_LIBRARY} opengl32.lib gdi32.lib shell32.lib)

set_target_properties(PineKey PROPERTIES WIN32_EXECUTABLE TRUE)

target_sources(PineKey PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)

