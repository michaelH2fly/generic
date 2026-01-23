#include "monitor.h"
#include "clock.h"


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
MonitorUpperLimit::MonitorUpperLimit(Clock& clock, float& observed_value, MonitorParameter& parameter)
	: Monitor(clock, observed_value, parameter) {}

bool MonitorUpperLimit::IsThresholdExceeded() {

	if (observed_value_ > parameter_.threshold) {
		return true;
	} else {
		return false;
	}
		
}

// MonitorLowerLimit Implementation
MonitorLowerLimit::MonitorLowerLimit(Clock& clock, float& observed_value, MonitorParameter& parameter)
	: Monitor(clock, observed_value, parameter) {}

bool MonitorLowerLimit::IsThresholdExceeded() {
	if (observed_value_ < parameter_.threshold) {
		return true;
	} else {
		return false;
	}	
}