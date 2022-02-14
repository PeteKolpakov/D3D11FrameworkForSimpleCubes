#pragma once
#include <Windows.h>
#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock::time_point TIME_POINT;
typedef duration<float> DURATION;

class Time
{
public:
	INT init();
	void update();
	void deInit();

	FLOAT getDeltaTime() { return _deltaTime; }

private:
	TIME_POINT _lastTimeStamp = {};
	FLOAT _deltaTime = 0.0f;
	FLOAT _totalTime = 0.0f;	// time since app start
	UINT _fps = 0;				// frames since last fps update
	UINT _lastFPS = 0;
	FLOAT _fpsTime = 0.0f;		// time since last fpas update
};

