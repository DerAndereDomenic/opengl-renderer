add_executable(DeferredRenderer source.cpp)

target_link_libraries(DeferredRenderer OpenGLRendererLib)

set_target_properties(DeferredRenderer PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")