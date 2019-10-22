add_library(Engine STATIC
            src/Shader.cpp
            src/Texture.cpp
            src/Mesh.cpp
            src/Model.cpp
            src/Camera.cpp)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

target_link_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(
    Engine
    opengl32
    glfw3
    glad
    assimp
)