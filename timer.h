#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <thread>
#include <chrono>
#include <functional>
#include <utility>

class Timer {
    std::thread Thread;
    bool Alive = false; // if timer is running
    long CallNumber = -1L; // how many times we would like to run a function
    long repeat_count = -1L; //counts how many times function has been called
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);

    std::function<void(void)> func = nullptr; // can contain functions

    void SleepAndRun() {
        std::this_thread::sleep_for(interval);

        if (Alive) {
            Function()(); // callback
        }
    }

    void ThreadFunc() {
        if (CallNumber == Infinite) {
            while (Alive) {
                SleepAndRun();
            }
        } else {
            while (repeat_count--) {
                SleepAndRun();
            }

        }
    }

public:
    static const long Infinite = -1L;

    Timer() = default;

    explicit Timer(std::function<void(void)> f) : func(std::move(f)) {}

    Timer(std::function<void(void)> f,
          const unsigned long &i,
          const long repeat = Timer::Infinite) : func(std::move(f)),
                                                 interval(std::chrono::milliseconds(i)),
                                                 CallNumber(repeat) {}

    //starts the timer
    void Start(bool Async = true) {
        if (IsAlive()) {
            return;
        }
        Alive = true;
        repeat_count = CallNumber;
        if (Async) {
            Thread = std::thread(ThreadFunc, this);
        } else {
            this->ThreadFunc();
        }
    }

    void Stop() {
        Alive = false;
        Thread.join();

    }

    //sets the function to be executed
    void SetFunction(const std::function<void(void)> &f) {
        func = f;
    }

    //is the timer running or not?
    bool IsAlive() const { return Alive; }

    //sets how many times it is going to repeat
    void RepeatCount(const long r) {
        if (Alive) {
            return;
        }
        CallNumber = r;
    }

    //returns how many iterations are left
    long GetLeftCount() const { return repeat_count; }

    //returns how many iterations we had originally requested
    long RepeatCount() const { return CallNumber; }

    void SetInterval(const unsigned long &i) {
        if (Alive) {
            return;
        }
        interval = std::chrono::milliseconds(i);
    }

    //.count() converts from chrono milliseconds to long
    unsigned long Interval() const { return interval.count(); }


    const std::function<void(void)> &Function() const {
        return func;
    }
};

#endif // TIMER_H_INCLUDED