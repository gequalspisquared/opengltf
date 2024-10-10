# ----------------------------------------------------------------------------
# glm, glfw, & tinygltf
# ----------------------------------------------------------------------------
add_subdirectory(fmt)
add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(tinygltf)

# ----------------------------------------------------------------------------
# stb & glad
# ----------------------------------------------------------------------------

add_library(stb STATIC)

target_sources(stb PRIVATE
    stb/include/stb/stb_image.h
    stb/src/stb_image.cpp
)

target_include_directories(stb PUBLIC "stb/include")

add_library(glad STATIC)

target_sources(glad PRIVATE
    glad/include/glad/glad.h
    glad/src/glad.c
)

target_include_directories(glad PUBLIC "glad/include")

# ----------------------------------------------------------------------------
# ImGUI
# ----------------------------------------------------------------------------

add_library(imgui STATIC)

target_sources(imgui PRIVATE 
    imgui/imgui.h
    imgui/imgui.cpp

    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC imgui)
target_link_libraries(imgui PRIVATE glfw)