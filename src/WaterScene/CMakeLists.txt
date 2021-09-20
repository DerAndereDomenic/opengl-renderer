add_executable(WaterScene source.cpp)

target_link_libraries(WaterScene OpenGLRendererLib)

set_target_properties(WaterScene PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")