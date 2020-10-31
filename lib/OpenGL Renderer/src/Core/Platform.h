#ifndef __OPENGLRENDERER_CORE_PLATFORM_H
#define __OPENGLRENDERER_CORE_PLATFORM_H

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#define __OPENGLRENDERER_WINDOWS
#else 
	#define __OPENGLRENDERER_UNIX
#endif

#endif