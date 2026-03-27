//#include "ComponentProtection/inc/monitor.h"
#ifndef COMPONENT_PROTECTION_TEST_INC_MOCK_MONITOR_H_
#define COMPONENT_PROTECTION_TEST_INC_MOCK_MONITOR_H_

#include "monitor.h"

namespace testing {

template <typename BaseMonitor>
class MockMonitor : public BaseMonitor {

    public:

    static inline MonitorParameter kDefaultMonitorParameters = {
        .threshold = 2.0f, 
        .debounce_time = 2000};

    explicit MockMonitor(Clock &clock, float& observed_value, MonitorParameter parameter)
        : BaseMonitor(  clock, 
                        observed_value, 
                        kDefaultMonitorParameters) {}
    
    void SetState(Monitor::MonitorState state) {this->state_ = state;};

};

} // namespace testing

#endif