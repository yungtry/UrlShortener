cmake_minimum_required(VERSION 3.0.0)
project(test1 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(UrlShortener src/defaults.h src/config.h src/main.cpp src/generator.cpp src/generator.hpp src/page.cpp src/page.hpp html/index.html html/shorten.html)

find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
target_include_directories(UrlShortener PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})
find_package(cpr CONFIG)
target_link_libraries(UrlShortener PRIVATE cpr)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
