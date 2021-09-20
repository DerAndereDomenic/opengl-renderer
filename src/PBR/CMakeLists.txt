add_executable(PBR source.cpp)

target_link_libraries(PBR OpenGLRendererLib)

set_target_properties(PBR PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")