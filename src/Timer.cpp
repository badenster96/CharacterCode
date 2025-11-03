#include "Timer.h"

Timer::Timer()
{
    //ctor
    startAt =0;
    pauseAt =0;
    paused =false;
    started =false;
}

Timer::~Timer()
{
    //dtor
}
bool Timer::isStarted()
{
    return started;
}

bool Timer::isStoped()
{
    return !started;
}

bool Timer::isSpaused()
{
    return paused;
}

void Timer::pause()
{
    if(paused || !started)
        return;
    paused = true;
    pauseAt= clock();

}

void Timer::resume()
{
    if(!paused)return;
    paused = false;
    startAt +=clock()-pauseAt;
}

void Timer::start()
{
    if(started)return;
    started= true;
    paused = false;
    startAt= clock();

}

void Timer::stop()
{
    started = false;
}

void Timer::reset()
{
    paused = false;
    startAt = clock();
}

clock_t Timer::getTicks()
{
    if(!started)return 0;
    if(paused)return pauseAt - startAt;
    return clock()-startAt;
}
