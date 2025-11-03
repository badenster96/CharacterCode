#pragma once

#include<time.h>

class Timer
{
    public:
        Timer();
        virtual ~Timer();

        clock_t startAt;
        clock_t pauseAt;

        bool started;
        bool paused;

        bool isStarted();
        bool isStoped();
        bool isSpaused();

        void pause();
        void resume();
        void start();
        void stop();
        void reset();

        clock_t getTicks();


    protected:

    private:
};