//CORE.Time.cpp
///////////////////////////////////////////////////////

#include "main.h"
#include <time.h>

namespace CORE {
	namespace Time {
		unsigned long GlobalTime, PreviousTime, NextFrameTime, DeltaTicks;
		float DeltaTime;

		void Update(){
			PreviousTime = GlobalTime;

			clock_t t = clock();

			GlobalTime = t;
			DeltaTicks = GlobalTime - PreviousTime;
			DeltaTime = DeltaTicks / 1000.0f;
		}
	}
}