//CORE.Time.h
///////////////////////////////////////////////////////

#pragma once

#ifndef _CORE_TIME_H_
#define _CORE_TIME_H_

namespace CORE {
	namespace Time {
		extern unsigned long GlobalTime;
		extern unsigned long PreviousTime;
		extern unsigned long DeltaTicks;
		extern float DeltaTime;
		void Update();
	}
}

#endif