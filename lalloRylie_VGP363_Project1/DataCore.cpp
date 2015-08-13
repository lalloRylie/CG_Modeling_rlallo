//DataCore.cpp
///////////////////////////////////////////////////////

#include "DataCore.h"

namespace DATACORE {
	EGLDisplay mDisplay = 0;
	EGLNativeWindowType mNativeWindow = 0;
	EGLNativeDisplayType mNativeDisplay = 0;
	bool mAppRunning = true;
	
	EGLConfig mConfig = 0;
	EGLSurface mSurface = 0;
	EGLContext mContext = 0;
	EGLint mConfigCount = 0;

	int wndWidth = 1024;
	int wndHeight = 768;

	bool _KEYBOARD_LEFT  = false;
	bool _KEYBOARD_RIGHT = false;
	bool _KEYBOARD_UP	 = false;
	bool _KEYBOARD_DOWN	 = false;
}