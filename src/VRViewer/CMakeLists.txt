add_executable(VRViewer source.cpp)

target_link_libraries(VRViewer OpenGLRendererLib)

set_target_properties(VRViewer PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")