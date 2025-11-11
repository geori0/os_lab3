cmake_minimum_required(VERSION 3.10)
project(OS_Lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message("Build for Linux")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message("Build for Windows")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /WX /Zi")
endif ()

add_executable(lab3
    src/parent.cpp
    src/child.cpp
    src/linux_os.cpp
    src/prime.cpp
)

target_include_directories(lab3 PUBLIC ${PROJECT_SOURCE_DIR}/include)