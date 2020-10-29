cmake_minimum_required(VERSION "3.10")

project(DLogger VERSION 1.0 LANGUAGES CXX)
add_executable(DLoggerTest src/source.cpp)

add_library(DLogger src/DLogger/Logger.cpp)
target_include_directories(DLogger PRIVATE include)


target_include_directories(DLoggerTest PRIVATE include)
target_link_libraries(DLoggerTest PRIVATE DLogger)

#####################################################
#					INSTALL							#
#####################################################

#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

install(TARGETS DLogger CONFIGURATIONS Debug DESTINATION bin/Debug)
install(TARGETS DLogger CONFIGURATIONS Release DESTINATION bin/Release)