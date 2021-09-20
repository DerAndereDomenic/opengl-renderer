add_executable(TestScene source.cpp)

target_link_libraries(TestScene OpenGLRendererLib)

set_target_properties(TestScene PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")