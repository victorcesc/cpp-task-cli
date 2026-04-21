cmake_minimum_required(VERSION 3.16)
project(learn-modern-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(APP_SOURCES
    src/main.cpp
    src/Task.cpp
    src/ReplLogic.cpp
)

add_executable(learn-modern-cpp ${APP_SOURCES})
target_include_directories(learn-modern-cpp PRIVATE src)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(unit-tests
        tests/test_task.cpp
        tests/test_repl.cpp
    )
    target_link_libraries(unit-tests PRIVATE Catch2::Catch2WithMain)
    target_include_directories(unit-tests PRIVATE src)
    target_sources(unit-tests PRIVATE src/Task.cpp src/ReplLogic.cpp)
    target_compile_options(unit-tests PRIVATE -Wall -Wextra -Wpedantic)
    # Catch2 uses __COUNTER__; Clang 22+ warns under -Wpedantic without this.
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
        target_compile_options(unit-tests PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wno-c2y-extensions>)
    endif()

    add_test(NAME unit-tests COMMAND unit-tests)
endif()
