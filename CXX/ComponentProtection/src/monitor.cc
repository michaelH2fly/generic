#include "monitor.h"

// Monitor Implementation
Monitor::Monitor(float &threshold, float &debounce_time)
	: threshold_(threshold), debounce_time_(debounce_time) {}

void Monitor::Step(bool is_active, bool do_reset) {
	// Base implementation - can be overridden by subclasses if needed
	(void)is_active;  // Mark as intentionally unused
	(void)do_reset;   // Mark as intentionally unused
}

float Monitor::GetThreshold() const {
	return threshold_;
}

float Monitor::GetDebounceTime() const {
	return debounce_time_;
}

void Monitor::SetThreshold(float threshold) {
	threshold_ = threshold;
}

void Monitor::SetDebounceTime(float debounce_time) {
	debounce_time_ = debounce_time;
}

// MonitorUpperLimit Implementation
MonitorUpperLimit::MonitorUpperLimit(float &threshold, float &debounce_time)
	: Monitor(threshold, debounce_time) {}

bool MonitorUpperLimit::IsThresholdExceeded(float value) const {
	return value > threshold_;
}

// MonitorLowerLimit Implementation
MonitorLowerLimit::MonitorLowerLimit(float &threshold, float &debounce_time)
	: Monitor(threshold, debounce_time) {}

bool MonitorLowerLimit::IsThresholdExceeded(float value) const {
	return value < threshold_;
}
