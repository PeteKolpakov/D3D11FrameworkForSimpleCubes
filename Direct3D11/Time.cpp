#include "Time.h"
#include <string>

using namespace std;

INT Time::init()
{
	_lastTimeStamp = high_resolution_clock::now();

	return 0;
}

void Time::update()
{
	TIME_POINT now = high_resolution_clock::now();
	DURATION diff = now - _lastTimeStamp;
	_deltaTime = diff.count();
	_totalTime += _deltaTime;
	_lastTimeStamp = now;

#if _DEBUG
	// print delta time
#if UNICODE
	wstring output = to_wstring(_deltaTime);
#else // UNICODE
	string output = to_string(_deltaTime);
#endif // UNICODE
	output = TEXT("deltaTime: ") + output + TEXT("s\n");
	OutputDebugString(output.c_str());

	// print fps extrapolated
#if UNICODE
	output = to_wstring(1.0f / _deltaTime);
#else // UNICODE
	output = to_string(1.0f / _deltaTime);
#endif // UNICODE
	output = TEXT("fps (extrapolated): ") + output + TEXT("\n");
	OutputDebugString(output.c_str());

	//print fps commulated
	_fps++;
	_fpsTime += _deltaTime;

	if (_fpsTime >= 1.0f)
	{
		_lastFPS = _fps;
		_fps = 0;
		_fpsTime -= 1.0f;
	}
#if UNICODE
	output = to_wstring(_lastFPS);
#else // UNICODE
	output = to_string(_lastFPS);
#endif // UNICODE
	output = TEXT("fps (commulated): ") + output + TEXT("\n");
	OutputDebugString(output.c_str());


#endif // _DEBUG
}

void Time::deInit()
{
}
