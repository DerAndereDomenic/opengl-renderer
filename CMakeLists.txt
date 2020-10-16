cmake_minimum_required(VERSION "3.10")

project(OpenGLRenderer LANGUAGES CXX VERSION 1.0)

option(BUILD_TESTSCENE "Build the test scene for this renderer" ON)

add_subdirectory(src)
