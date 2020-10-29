#ifndef __DLOGGER_PLATFORM_H
#define __DLOGGER_PLATFORM_H

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#define __DLOGGER_WINDOWS
#else 
	#define __DLOGGER_UNIX
#endif

#endif