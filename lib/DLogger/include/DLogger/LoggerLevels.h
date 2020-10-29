#ifndef __DLOGGER_LOGGERLEVELS_H
#define __DLOGGER_LOGGERLEVELS_H

#include <cstdint>

/**
*	@brief Defines the levels of the logger.
*	Each message has a level according to its importance.
*	The lowest level are DEBUG messages while the highest priority is given to
*	ERROR messages.
*/
enum class LoggerLevel
{
	DEBUG = 0,		/**< The DEBUG level */
	INFO = 1,		/**< The INFO level */
	WARNING = 2,	/**< The WARNING level */
	ERROR = 3		/**< The ERROR level */
};

#endif