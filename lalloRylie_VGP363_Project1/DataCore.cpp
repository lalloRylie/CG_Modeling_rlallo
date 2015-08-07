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
}