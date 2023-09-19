message("Main file path: ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

cmake_minimum_required(VERSION 3.10)

project(PineKey)

set(GLFW_LIBRARY C:/Pine/Prog/PineKey/lib/glfw3.dll)

# imgui paths
set(IMGUI_DIR C:/Pine/Prog/PineKey/imgui-docking)

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

add_executable(${PROJECT_NAME} main.cpp KeyHook.cpp ${IMGUI_SOURCES} C:/Pine/Prog/PineKey/resources.rc)

include_directories(C:/Pine/Prog/PineKey/include/ ${IMGUI_DIR} ${IMGUI_DIR}/backends)
    
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY} opengl32.lib gdi32.lib shell32.lib)

set_target_properties(PineKey PROPERTIES WIN32_EXECUTABLE TRUE)

#target_sources(PineKey PUBLIC C:/Pine/Prog/PineKey/resources.rc)

# TODO: Additional setup if needed
