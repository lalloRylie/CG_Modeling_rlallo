//DataCore.h
///////////////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

namespace DATACORE{
	extern EGLDisplay mDisplay;
	extern EGLNativeWindowType mNativeWindow;
	extern EGLNativeDisplayType mNativeDisplay;
	extern bool mAppRunning;
	
	extern EGLConfig mConfig;
	extern EGLSurface mSurface;
	extern EGLContext mContext;
	extern EGLint mConfigCount;
}