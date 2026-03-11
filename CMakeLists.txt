cmake_minimum_required(VERSION 3.2)

project(calculator)

include(FetchContent)

FetchContent_Declare(
	mathlib
	GIT_REPOSITORY https://github.com/AndreyTimush/headerOnlyMathLib.git
	GIT_TAG master
)

option(ENABLE_CLANG_TIDY "Enable clang-tidy analysis" ON)

FetchContent_MakeAvailable(mathlib)

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE clang-tidy)

    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
        message(STATUS "clang-tidy enabled: ${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy not found - static analysis disabled")
    endif()
endif()

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