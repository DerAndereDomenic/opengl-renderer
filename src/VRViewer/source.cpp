#include <iostream>
#include <Renderer/VRRenderer.h>
#include <DLogger/Logger.h>

int main()
{
	LOGGER::setProject("VR Viewer", "1.0");
	LOGGER::start();
	VRRenderer renderer = VRRenderer::createObject();

	LOGGER::end();
	return 0;
}