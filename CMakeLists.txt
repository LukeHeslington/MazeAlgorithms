cmake_minimum_required(VERSION 3.0)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add executable target
file(GLOB SOURCES "src/*.cpp")
add_executable(MazeSolver ${SOURCES})

# Set optimization flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MazeSolver PRIVATE -O3)  # Optimization level 3
elseif(MSVC)
    target_compile_options(MazeSolver PRIVATE /O2)  # Optimization level 2
endif()

# Link against SFML libraries
target_link_libraries(MazeSolver PRIVATE sfml-graphics sfml-window sfml-system)

# Add include directories
target_include_directories(MazeSolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
