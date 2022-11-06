cmake_minimum_required(VERSION 3.16)
project(ScheduleSaver)
set(CMAKE_CXX_STANDARD 17)

include($ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)
include_directories($ENV{VCPKG_DIR}/installed/x64-linux/include)
include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(app)