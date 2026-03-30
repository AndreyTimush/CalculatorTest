cmake_minimum_required(VERSION 3.2)

project(calculator)

include(FetchContent)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")

FetchContent_Declare(
	mathlib
	GIT_REPOSITORY https://github.com/AndreyTimush/headerOnlyMathLib.git
	GIT_TAG master
)

FetchContent_Declare(
	nlohmann_json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(mathlib nlohmann_json)

add_executable(calculator main.cpp)

target_include_directories(calculator PUBLIC
    "${PROJECT_SOURCE_DIR}" 
)

target_link_libraries(calculator PRIVATE mathlib nlohmann_json::nlohmann_json)

install(TARGETS calculator DESTINATION bin)
