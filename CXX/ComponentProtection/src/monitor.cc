#include "monitor.h"



// Monitor Implementation
//Monitor::Monitor(unsigned int &time_reference, float &threshold, float &debounce_time)
//    : time_reference_(time_reference),
//      threshold_(threshold),
//      debounce_time_(debounce_time)
//{}

void Monitor::Step(bool is_active, bool do_reset) {
	// Base implementation - can be overridden by subclasses if needed
	(void)is_active;  // Mark as intentionally unused
	(void)do_reset;   // Mark as intentionally unused
}

const MonitorParameter& Monitor::GetParameter() const {
	return parameter_;
}

void Monitor::SetParameter(MonitorParameter& parameter) {
	parameter_ = parameter;
}

// MonitorUpperLimit Implementation
MonitorUpperLimit::MonitorUpperLimit(unsigned int &time_reference, MonitorParameter& parameter)
	: Monitor(time_reference, parameter) {}

void MonitorUpperLimit::Step(bool is_active, bool do_reset) {

	(void)is_active;
	(void)do_reset;
}


// MonitorLowerLimit Implementation
MonitorLowerLimit::MonitorLowerLimit(unsigned int &time_reference, MonitorParameter& parameter)
	: Monitor(time_reference, parameter) {}

void MonitorLowerLimit::Step(bool is_active, bool do_reset) {
	(void)is_active;
    (void)do_reset;
}