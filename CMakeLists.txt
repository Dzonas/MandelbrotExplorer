cmake_minimum_required(VERSION 3.13)
project(MandelbrotExplorer)

set(CMAKE_CXX_STANDARD 17)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(src)

# GLFW3 Library
set(GLFW_DIR ${LIB_DIR}/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})
target_link_libraries(MandelbrotExplorer PRIVATE glfw)

# GLAD OpenGL Loader
set(GLAD_DIR ${LIB_DIR}/glad)
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(MandelbrotExplorer PRIVATE ${GLAD_DIR}/include)
target_link_libraries(MandelbrotExplorer PRIVATE glad)

# GLM Library
set(GLM_DIR ${LIB_DIR}/glm)
add_subdirectory(${GLM_DIR})
target_link_libraries(MandelbrotExplorer PRIVATE glm::glm)

# CXXopts Library
set(CXXOPTS_DIR ${LIB_DIR}/cxxopts)
add_subdirectory(${CXXOPTS_DIR})
target_link_libraries(MandelbrotExplorer PRIVATE cxxopts)
