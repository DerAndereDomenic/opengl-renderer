#include <DLogger/Logger.h>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <DLogger/Platform.h>

#ifdef __DLOGGER_WINDOWS
#include <windows.h>
#undef ERROR 

#define __WHITE 15
#define __RED 12
#define __GREEN 10
#define __PINK 13
#define __YELLOW 14

#endif

namespace __dlogger_Detail
{
	std::string project_name;												/**< The name of the project to log */
	std::string version;													/**< The version of the project to log */
	
	bool initialized = false;												/**< If the Logger was initialized */
	bool should_file_log = false;											/**< If the logger should log to the console */
	bool should_console_log = true;											/**< If the logger should log to the log file */
	LoggerLevel minConsoleLevel = LoggerLevel::DEBUG;						/**< The minimum log level for the console */
	LoggerLevel minFileLevel = LoggerLevel::DEBUG;							/**< The minimum log level for the log file */
	
	std::fstream out_file;													/**< The log file */
	const std::string prefix[4] =											/**< The prefixes for the logger messages */
	{
		"[  Debug  ] ",
		"[  Info   ] ",
		"[ Warning ] ",
		"[  Error  ] "
	};
	uint32_t status[4] = {0,0,0,0};											/**< The number of messages logged */
	
#ifdef __DLOGGER_WINDOWS
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);						/**< The handle to the console */
	const uint8_t colors[4] = {__PINK, __GREEN, __YELLOW, __RED};			/**< The console color array */
#endif
	
	/**
	*	@brief Displays a Logger header
	*/
	void loggerHeader();
	
	/**
	*	@brief Displays a Logger footer
	*/
	void loggerFooter();
	
	/**
	*	@brief Writes a log message.
	*	@param log The log message
	*/
	void writeLog(const std::string& log);
	
	/**
	*	@brief Writes a leveled log message .
	*	@param level The priority level of the message
	*	@param log The log message
	*/
	void writeLogLevel(const LoggerLevel& level, const std::string& log);
}

void 
LOGGER::setProject(const std::string& name,
				   const std::string& version)
{
	__dlogger_Detail::project_name = name;
	__dlogger_Detail::version = version;
}
					
void 
LOGGER::setFileLogging(const bool& should_file_log,
					   const std::string& path)
{
	__dlogger_Detail::should_file_log = should_file_log;
	__dlogger_Detail::out_file = std::fstream(path, std::ios::out);
}
						
void 
LOGGER::setConsoleLogging(const bool& should_console_log)
{
	__dlogger_Detail::should_console_log = should_console_log;
}
	
void 
LOGGER::start()
{
	__dlogger_Detail::initialized = true;
	__dlogger_Detail::loggerHeader();
}
	
void 
LOGGER::end()
{
	__dlogger_Detail::loggerFooter();
	__dlogger_Detail::out_file.close();
	__dlogger_Detail::initialized = false;
}

void 
LOGGER::setMinConsoleLevel(const LoggerLevel& level)
{
	__dlogger_Detail::minConsoleLevel = level;
}

void 
LOGGER::setMinFileLevel(const LoggerLevel& level)
{
	__dlogger_Detail::minFileLevel = level;
}

void 
LOGGER::DEBUG(const std::string& log)
{
	__dlogger_Detail::writeLogLevel(LoggerLevel::DEBUG, log);
}

void 
LOGGER::INFO(const std::string& log)
{
	__dlogger_Detail::writeLogLevel(LoggerLevel::INFO, log);
}

void 
LOGGER::WARNING(const std::string& log)
{
	__dlogger_Detail::writeLogLevel(LoggerLevel::WARNING, log);
}
	
void 
LOGGER::ERROR(const std::string& log)
{
	__dlogger_Detail::writeLogLevel(LoggerLevel::ERROR, log);
}

void 
__dlogger_Detail::loggerHeader()
{
	uint32_t white_space = 80;
	uint32_t name_ver_size = project_name.size() + version.size() + 1;
	uint32_t rem_white_space = (white_space - name_ver_size)/2;
	
	std::stringstream ss;
	
	ss << "#" << std::string(white_space, '-') << "#" << std::endl;
	writeLog(ss.str());
	
	ss.str(std::string());
	ss << "#" << std::string(rem_white_space, ' ') << project_name << " " << version << std::string(rem_white_space, ' ') << "#" <<std::endl;
	writeLog(ss.str());
	
	ss.str(std::string());
	ss << "#" << std::string(white_space, '-') << "#" << std::endl;
	writeLog(ss.str());
}

void
__dlogger_Detail::loggerFooter()
{
	uint32_t white_space = 80;
	uint32_t rem_white_space;
	
	std::stringstream ss;
	
	ss << "#" << std::string(white_space, '-') << "#" << std::endl;
	writeLog(ss.str());
	
	ss.str(std::string());
	ss << "#" << " Warnings: " << status[2];
	rem_white_space = white_space - ss.str().size() + 1;
	ss << std::string(rem_white_space, ' ') << "#" << std::endl;
	writeLog(ss.str());
	
	ss.str(std::string());
	ss << "#" << " Errors: " << status[3];
	rem_white_space = white_space - ss.str().size() + 1;
	ss << std::string(rem_white_space, ' ') << "#" << std::endl;
	writeLog(ss.str());
	
	ss.str(std::string());
	ss << "#" << std::string(white_space, '-') << "#" << std::endl;
	writeLog(ss.str());
}

void 
__dlogger_Detail::writeLog(const std::string& log)
{
	if(!initialized) return;
	
	if(should_console_log)
	{
		std::cout << log;
	}
	
	if(should_file_log)
	{
		out_file << log;
	}
}

void 
__dlogger_Detail::writeLogLevel(const LoggerLevel& level, const std::string& log)
{
	if(!initialized) return;
	
	if(should_console_log && level >= minConsoleLevel)
	{
#ifdef __DLOGGER_WINDOWS
		SetConsoleTextAttribute(hConsole, colors[static_cast<int32_t>(level)]);
		std::cout << prefix[static_cast<int32_t>(level)];
		SetConsoleTextAttribute(hConsole, __WHITE);
		std::cout << log;
#else
		std::cout << prefix[static_cast<int32_t>(level)];
		std::cout << log;
#endif
	}
	
	if(should_file_log && level >= minFileLevel)
	{
		out_file << prefix[static_cast<int32_t>(level)] << log;
	}
	
	++status[static_cast<int32_t>(level)];
}