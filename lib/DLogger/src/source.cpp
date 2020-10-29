#include <iostream>
#include <DLogger/Logger.h>

int main()
{
	LOGGER::setProject("DLogger Test", "1.0");
	LOGGER::setFileLogging(true, "Log.txt");
	LOGGER::start();
	
	LOGGER::DEBUG("This is a debug message\n");
	LOGGER::INFO("This is an info message\n");
	LOGGER::WARNING("This is a warning message\n");
	LOGGER::ERROR("This is an error message\n");
	
	LOGGER::end();
	return 0;
}