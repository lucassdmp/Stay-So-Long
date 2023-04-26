cmake_minimum_required(VERSION 3.1)

project(Stay-So-Long)

set(CMAKE_CXX_STANDARD 11)

# Find SFML and OpenGL libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES
  src/main.cpp
  src/Core/Game.cpp
  src/Util/Shapes.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} 
  ${SOURCES}
)

# Link SFML and OpenGL libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system OpenGL::GL)
