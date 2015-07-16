//Utility.cpp
///////////////////////////////////////////////////////

#include <stdio.h>
#include <Windows.h>

void ConsoleLog(char* consoleMessage) {
	printf(consoleMessage);
}

void DebugLog(char* debugMessage) {
	OutputDebugString(debugMessage);
	ConsoleLog(debugMessage);
}