//main.cpp
///////////////////////////////////////////////////////

#include "APP.Main.h"
#include "main.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "libEGL.lib")
#pragma comment(lib, "libGLESv2.lib")
#pragma comment(lib, "preprocessor.lib")
#pragma comment(lib, "translator_lib.lib")


using namespace CORE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if(message == WM_CLOSE) {
		mAppRunning = false;
	}
	return DefWindowProcA(hWnd, message, wParam, lParam);
}

// Week 2 
void GL_Initialize() {
	EGLint configAttribute[] = {
		EGL_RED_SIZE,
		8,
		EGL_GREEN_SIZE,
		8,
		EGL_BLUE_SIZE,
		8,
		EGL_ALPHA_SIZE,
		8,
		EGL_DEPTH_SIZE,
		24,
		EGL_STENCIL_SIZE,
		8,
		EGL_SAMPLE_BUFFERS,
		EGL_DONT_CARE,
		EGL_NONE
	};

	if(!eglChooseConfig(mDisplay, configAttribute, &mConfig, 1, &mConfigCount) || mConfigCount != 1){
		DebugLog("3D Hardware Accelerator configuration could no be queried. \n");
		//TODO: exit app, return false
	}

	EGLint surfaceAttributes[] = {
		EGL_POST_SUB_BUFFER_SUPPORTED_NV,
		EGL_TRUE,
		EGL_NONE,
		EGL_NONE
	};

	mSurface = eglCreateWindowSurface(mDisplay, mConfig, mNativeWindow, surfaceAttributes);

	if(mSurface == EGL_NO_SURFACE || eglGetError() != EGL_SUCCESS){
		DebugLog("3D Hardware Accelerator could not be bound to the specified window as configured. \n");
	}

	EGLint contextAttributes[] = {
		EGL_CONTEXT_CLIENT_VERSION,
		2,
		EGL_NONE
	};

	mContext = eglCreateContext(mDisplay, mConfig, 0, contextAttributes);

	if(eglGetError() != EGL_SUCCESS) {
		DebugLog("OpenGL|ES context could not be created with the version specified. \n");
		//TODO: exit app, return false
	}

	eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);

	if(eglGetError() != EGL_SUCCESS) {
		DebugLog("Specified EGL rendering context could not be activated on the specified rendering surface and display. \n");
	}
}

// Week 2 Extra
void GL_Uninitialize() {
	if(mSurface != 0) {
		eglDestroySurface(mDisplay, mSurface);
		mSurface = 0;
	}

	if(mContext != 0) {
		eglDestroyContext(mDisplay, mSurface);
		mContext = 0;
	}
}

void OnDestroyInstance() {
	GL_Uninitialize();

	if(mDisplay != EGL_NO_DISPLAY) {
		eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglTerminate(mDisplay);
		mDisplay = EGL_NO_DISPLAY;
	}

	if(mNativeDisplay != 0) {
		ReleaseDC(mNativeWindow, mNativeDisplay);
		mNativeDisplay = 0;
	}

	if(mNativeWindow != 0) {
		DestroyWindow(mNativeWindow);
		mNativeWindow = 0;
	}

	UnregisterClassA("VGP363ProjectWndClass", NULL);

	DebugLog("Unitialization succeeded. \n");
}


////////////////////////////////////

bool OnInitInstance() {
	WNDCLASSEXA windowClass;
	memset(&windowClass, 0, sizeof(WNDCLASSEXA)); 

	windowClass.cbSize = sizeof(WNDCLASSEXA);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass. cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = 0;
	windowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "VGP363ProjectWndClass";

	if(!RegisterClassExA(&windowClass)) {
		DebugLog("Window registration failed. \n");
		return false;
	}

	//RECT windowSize;
	//memset(&windowSize, 0, sizeof(RECT));
	//windowSize.right = 720;
	//windowSize.bottom = 532;

	DWORD style = WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU;
	DWORD extendedStyle = WS_EX_APPWINDOW;

	//AdjustWindowRectEx(&windowSize, style, false, extendedStyle);

	mNativeWindow = CreateWindowExA(extendedStyle, "VGP363ProjectWndClass", "lalloRylie_VGP363_Project1", style, CW_USEDEFAULT, CW_USEDEFAULT, 720, 532, 0, 0, GetModuleHandle(NULL), 0);

	ShowWindow(mNativeWindow, SW_SHOW);

	mNativeDisplay = GetDC(mNativeWindow);
						
	if(mNativeDisplay == 0){
		DebugLog("Basic windows graphical device context couldn't be created for the window. \n");
		return false;
	}

	mDisplay = eglGetDisplay(mNativeDisplay);

	if(mDisplay == EGL_NO_DISPLAY){
		DebugLog("OpenGL|ES context could not be created. \n");
		return false;
	}

	EGLint minorVersion = 0;
	EGLint majorVersion = 0;

	if(!eglInitialize(mDisplay, &majorVersion, &minorVersion)) {
		DebugLog("OpenGL|ES context could not be created. \n");
		return false;
	}

	eglBindAPI(EGL_OPENGL_ES_API);

	if(eglGetError() != EGL_SUCCESS) {
		DebugLog("OpenGL|ES context could not be created. \n");
		return false;
	}

	GL_Initialize();

	DebugLog("Initialization succeeded. \n");
	return true;
}

////for returning error code, parameters tell code how to run; required in C
//int main(int argc, char** argv) {
//
//}

void main() {
	if(!OnInitInstance()) {
		exit(0);
	}
	
	mAppRunning = true;
	OnInitialize();

	while(mAppRunning) {
		MSG message;

		if(Time::DeltaTicks < 30) Sleep(30 - Time::DeltaTicks);

		OnFrame();
		eglSwapBuffers(mDisplay, mSurface);

		while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		}	
	}
	OnDestroyInstance();
}