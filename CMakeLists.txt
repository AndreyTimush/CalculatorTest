cmake_minimum_required(VERSION 3.2)

project(calculator)

include(FetchContent)
enable_testing()

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")

find_package(PostgreSQL REQUIRED)

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

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(mathlib nlohmann_json googletest spdlog)

add_library(calculator_core OBJECT main.cpp
    src/calculator.cpp
    src/checker.cpp
    src/data.cpp
    src/logger.cpp
    src/parser.cpp
    src/printer.cpp
    src/runner.cpp
    src/database.cpp)
target_compile_definitions(calculator_core PRIVATE main=calculator_entrypoint)
target_include_directories(calculator_core PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)
target_link_libraries(calculator_core PUBLIC mathlib nlohmann_json spdlog)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/app_main.cpp"
"int calculator_entrypoint(int argc, char** argv);\n"
"int main(int argc, char** argv) { return calculator_entrypoint(argc, argv); }\n"
)

add_executable(calculator "${CMAKE_CURRENT_BINARY_DIR}/app_main.cpp")
target_link_libraries(calculator PRIVATE calculator_core)

target_include_directories(calculator PUBLIC
    "${PROJECT_SOURCE_DIR}" 
)

target_include_directories(calculator PRIVATE
    ${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(calculator PRIVATE mathlib nlohmann_json spdlog PostgreSQL::PostgreSQL)

file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_executable(calculator_tests ${TEST_SOURCES})

target_include_directories(calculator_tests PUBLIC
    "${PROJECT_SOURCE_DIR}"
)

target_link_libraries(calculator_tests PRIVATE
    gtest
    calculator_core
)

add_test(NAME calculator_tests COMMAND calculator_tests)
