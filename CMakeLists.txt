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

find_program(CLANG_FORMAT_EXE clang-format)
get_target_property(target_sources calculator SOURCES)
if(CLANG_FORMAT_EXE) 
  add_custom_target(format 
    COMMENT "Formatting files with clang-format..." 
    COMMAND ${CLANG_FORMAT_EXE} -i ${target_sources} 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  ) 
  message(STATUS "Added 'format' target") 
else() 
  message(WARNING
    "clang-format not found - format target unavailable") 
endif()
