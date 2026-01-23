#ifndef CXX_CLOCK_INC_CLOCK_H_
#define CXX_CLOCK_INC_CLOCK_H_

#include <chrono>
#include <cstdint>

using Timestamp = std::chrono::steady_clock::time_point;

class Clock {

    public:

    Clock() = default;
    virtual ~Clock() = default;
    virtual Timestamp Now() const = 0;

};

class SteadyClock : public Clock {
    public:
    SteadyClock() = default;
    ~SteadyClock() override = default;
    Timestamp Now() const override {
        return std::chrono::steady_clock::now();
    }
};

class MockClock : public Clock {
    public:
    MockClock() : current_time_(std::chrono::steady_clock::now()) {}
    ~MockClock() override = default;
    Timestamp Now() const override {
        return current_time_;
    }
    void Advance(std::chrono::milliseconds duration) {
        current_time_ += duration;
    }
    void SetTime(Timestamp new_time) {
        current_time_ = new_time;
    }

    private:
    Timestamp current_time_;
};




#endif  // CXX_CLOCK_INC_CLOCK_H_

