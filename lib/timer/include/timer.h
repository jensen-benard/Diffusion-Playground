#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
    public:
        virtual ~Timer() = default;

        virtual void start() = 0;
        virtual void tick() = 0;
        virtual bool isDue() = 0;
};


class FixedTimer : public Timer {
    public:
        FixedTimer(double targetDeltaTime) : targetDeltaTime(targetDeltaTime), accumulator(0), lastUpdateTime(std::chrono::steady_clock::now()) {};

        void start() override;
        void tick() override;
        bool isDue() override;

    private:
        double targetDeltaTime;
        std::chrono::steady_clock::time_point lastUpdateTime;

        double accumulator;
    
};


class VariableTimer : public Timer {
    public:
        VariableTimer(double targetDeltaTime) : targetDeltaTime(targetDeltaTime), lastUpdateTime(std::chrono::steady_clock::now()) {};

        void start() override;
        void tick() override {};
        bool isDue() override;

    private:
        double targetDeltaTime;
        std::chrono::steady_clock::time_point lastUpdateTime;
};

#endif