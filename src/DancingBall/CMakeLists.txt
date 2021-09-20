add_executable(DancingBall source.cpp)

target_link_libraries(DancingBall OpenGLRendererLib)

set_target_properties(DancingBall PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")