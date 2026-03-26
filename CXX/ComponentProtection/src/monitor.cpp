#include "monitor.h"
#include "clock.h"


// Monitor Implementation
//Monitor::Monitor(unsigned int &time_reference, float &threshold, float &debounce_time)
//    : time_reference_(time_reference),
//      threshold_(threshold),
//      debounce_time_(debounce_time)
//{}

void Monitor::Update() {
	// Base implementation - can be overridden by subclasses if needed

	bool threshold_exceeded = IsThresholdExceeded();

	switch (state_) {
		case MonitorState::Inactive:
			if (threshold_exceeded) {
				// Transition to Debouncing state
				state_ = MonitorState::Debouncing;
				debounce_start_time_ = clock_.Now();
			}
			break;

		case MonitorState::Debouncing:
		{
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(clock_.Now() - debounce_start_time_).count();
			
			if (elapsed >= static_cast<int>(parameter_.debounce_time)) {
					// Transition to Active state
					state_ = MonitorState::Active;
					break;
			} 
			
			if (!threshold_exceeded) {
				// Return to Inactive state
				state_ = MonitorState::Inactive;
				break;
			} 
									
			break;
		}
		case MonitorState::Active:
			if (!threshold_exceeded) {
				// Return to Inactive state
				state_ = MonitorState::Inactive;
			}
			break;

		default:
			// Invalid state - reset to Inactive
			state_ = MonitorState::Inactive;
			break;
	}
}

const MonitorParameter& Monitor::GetParameter() {
	return parameter_;
} 

Monitor::MonitorState Monitor::GetState() {
	return state_;
}

Clock& Monitor::GetClock() {
	return clock_;
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