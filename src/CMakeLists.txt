if(BUILD_TESTSCENE)
	add_subdirectory(TestScene)
endif()

if(BUILD_DANCINGBALL)
	add_subdirectory(DancingBall)
endif()

if(BUILD_VR_VIEWER)
	add_subdirectory(VRViewer)
endif()

if(BUILD_WATERSCENE)
	add_subdirectory(WaterScene)
endif()

if(BUILD_GEOMETRYPROCESSING)
    add_subdirectory(GeometryProcessing)
endif()
