#ifndef TIMER_H
#define TIMER_H


#include <SDL.h>

class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	//Get the timer's time in milliseconds
	Uint32 getTicks();

	//Timer is running but can be paused or unpaused
	bool isStarted();
	//Timer is running and is paused
	bool isPaused();

private:
	Uint32 startTicks;
	Uint32 pausedTicks;

	bool started;
	bool paused;
};


#endif // !TIMER_H
