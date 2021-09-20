add_executable(DumpProject source.cpp)

target_link_libraries(DumpProject OpenGLRendererLib)

set_target_properties(DumpProject PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")