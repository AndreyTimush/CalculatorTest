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
	URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.2.tar.gz
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(mathlib nlohmann_json googletest)

add_executable(calculator main.cpp)

target_include_directories(calculator PUBLIC
    "${PROJECT_SOURCE_DIR}" 
)

target_link_libraries(calculator PRIVATE mathlib nlohmann_json)

install(TARGETS calculator DESTINATION bin)
