#ifndef __DLOGGER_LOGGER_H
#define __DLOGGER_LOGGER_H

#include <string>
#include <DLogger/LoggerLevels.h>

/**
*	@brief This namespace capsules all Logger functions
*	To use the logger a project name and version is to be specified. This will be used
*	in the header of the logger.
*	Console logging is turned on by default.
*		To disable it call setConsoleLogging(false);
*	File logging is turned off by default
*		To enable it call setFileLogging(true, PATH_TO_LOG_FILE);
*	
*	Logging starts when calling
*		LOGGER::start();
*	Logging ends when calling
*		LOGGER::end();
*/
namespace LOGGER
{
	/**
	*	@brief Set project name and version.
	*	This function has to be called before start otherwise the header will be empty
	*	@param name The name of the project to log 
	*	@param version The version of the project to log 
	*/
	void setProject(const std::string& name,
					const std::string& version);
					
	/**
	*	@brief Enables file logging.
	*	File logging is turned off by default. To enable file logging call this with should_file_log=true 
	*	and a valid file path
	*	@param should_file_log If file logging should be enabled 
	*	@param path The path to the output log file 
	*/
	void setFileLogging(const bool& should_file_log,
						const std::string& path);
	
	/**
	*	@brief Enables console logging.
	*	Console logging is turned on by default. To disable console logging call this with should_console_log=true
	*	@param should_console_log If console logging should be enabled
	*/
	void setConsoleLogging(const bool& should_console_log);
	
	/**
	*	@brief Starts logging.
	*	After calling start() the logging functions are available and log messages
	*/
	void start();
	
	/**
	*	@brief Ends logging.
	*	After calling end() logging is no longer possible and the logging file will be closed if 
	*	should_file_log=true
	*/
	void end();
	
	/**
	*	@brief Sets the minimum priority needed for a message to be logged to the console.
	*	Default is priority DEBUG = 0
	*	@param level The minimum logging level for the console 
	*/
	void setMinConsoleLevel(const LoggerLevel& level = LoggerLevel::DEBUG);
	
	/**
	*	@brief Sets the minimum priority needed for a message to be logged to the log file.
	*	Default is priority DEBUG = 0
	*	@param level The minimum logging level for the log file
	*/
	void setMinFileLevel(const LoggerLevel& level = LoggerLevel::DEBUG);
	
	/**
	*	@brief Logs a debug message.
	*	@param log The message to log.
	*/
	void DEBUG(const std::string& log);
	
	/**
	*	@brief Logs an info message.
	*	@param log The message to log.
	*/
	void INFO(const std::string& log);
	
	/**
	*	@param Logs a warning message.
	*	@param log The message to log.
	*/
	void WARNING(const std::string& log);
	
	/**
	*	@param Logs an error message.
	*	@param The message to log.
	*/
	void ERROR(const std::string& log);
}

#endif