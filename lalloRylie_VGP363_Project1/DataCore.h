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

	extern int wndWidth;
	extern int wndHeight;

	extern bool _KEYBOARD_LEFT; 
	extern bool _KEYBOARD_RIGHT;
	extern bool _KEYBOARD_UP;	
	extern bool _KEYBOARD_DOWN;	
	extern bool _KEYBOARD_W;
	extern bool _KEYBOARD_A;
	extern bool _KEYBOARD_S;
	extern bool _KEYBOARD_D;
	extern bool _KEYBOARD_SHIFT;
	extern bool _KEYBOARD_SPACE;

	extern float player_runSpeed; 
	extern float player_lookSpeed;
	extern float player_jumpVelocity;
	extern float player_gravity;
	extern int   player_STATE;

	class Vector {
	public:
		Vector(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		float x, y, z, w;
	};
}