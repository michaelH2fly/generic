#ifndef CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
#define CXX_COMPONENT_PROTECTION_INC_MONITOR_H_

#include <chrono>
#include <cstdint>
#include <clock.h>
#include <cp_parameter.h>

// Monitor base class and derived monitor types for component protection.

// monitor state enum


// Monitor configuration with threshold and debounce time.
class Monitor {
	public:

	enum class MonitorState : uint8_t {
		Inactive = 1,
		Debouncing = 2,
		Active = 3
	};

	
	// Virtual destructor for proper cleanup in derived classes.
	virtual ~Monitor() = default;

	// Constructor with default values.
	Monitor(Clock& clock, float& observed_value, MonitorParameter& parameter)
	    : clock_(clock),
	      parameter_(parameter),
		  observed_value_(observed_value) {};

	// Virtual step function (cyclic execution).
	void Update();
	virtual bool IsThresholdExceeded() = 0;

	// Getters - normal functions (same behavior for all subclasses).	
	const MonitorParameter& GetParameter();
	MonitorState GetState(); 
	Clock& GetClock();

	// Setters - normal functions (same behavior for all subclasses).

	
	// Check if value exceeds threshold (must be implemented by derived classes).

	private:	
	Clock& clock_;

	protected:
	MonitorParameter& parameter_;
	MonitorState state_ = MonitorState::Inactive;	
	std::chrono::time_point<std::chrono::steady_clock> debounce_start_time_;
	float& observed_value_;

};

// Upper limit monitor - triggers when value exceeds threshold.
class MonitorUpperLimit : public Monitor {
public:
	MonitorUpperLimit(Clock& clock, float& observed_value, MonitorParameter& parameter);
	
	bool IsThresholdExceeded() override;
};

class MonitorLowerLimit : public Monitor {
public:
    MonitorLowerLimit(Clock& clock, float& observed_value, MonitorParameter& parameter);
	bool IsThresholdExceeded() override;
};

#endif  // CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
