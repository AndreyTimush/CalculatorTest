cmake_minimum_required(VERSION 3.2)

project(calculator)

include(FetchContent)

FetchContent_Declare(
	mathlib
	GIT_REPOSITORY https://github.com/AndreyTimush/headerOnlyMathLib.git
	GIT_TAG master
)

FetchContent_MakeAvailable(mathlib)

add_executable(calculator main.cpp)

target_link_libraries(calculator PRIVATE mathlib)

install(TARGETS calculator DESTINATION bin)
