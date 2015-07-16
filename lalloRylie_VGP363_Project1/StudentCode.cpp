//StudentCode.cpp
///////////////////////////////////////////////////////

#include "DataCore.h"
#include "Utility.h"

void OnInitialize() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OnFrame() {
	eglSwapBuffers(mDisplay, mSurface);
}

