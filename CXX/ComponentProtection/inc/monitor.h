#ifndef CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
#define CXX_COMPONENT_PROTECTION_INC_MONITOR_H_

#include <chrono>
#include <cstdint>
#include <clock.h>

// Monitor base class and derived monitor types for component protection.

// monitor state enum
enum class MonitorState {
	Inactive = 1,
	Debouncing = 2,
	Active = 3
};

struct MonitorParameter {
	float threshold;
	float debounce_time;
};

// Monitor configuration with threshold and debounce time.
class Monitor {
	public:
	// Virtual destructor for proper cleanup in derived classes.
	virtual ~Monitor() = default;

	// Constructor with default values.
	Monitor(Clock& clock, MonitorParameter& parameter)
	    : clock_(clock),
	      parameter_(parameter) {};


	// Virtual step function (cyclic execution).
	void Step(bool is_active, bool do_reset);
	virtual bool IsThresholdExceeded() = 0;

	// Getters - normal functions (same behavior for all subclasses).
	const MonitorParameter& GetParameter() const;
	// Setters - normal functions (same behavior for all subclasses).
	void SetParameter(MonitorParameter& parameter);

	// Check if value exceeds threshold (must be implemented by derived classes).

	private:	
	Clock& clock_;

	protected:
	MonitorParameter& parameter_;
	MonitorState state_ = MonitorState::Inactive;

	std::chrono::time_point<std::chrono::steady_clock> debounce_start_time_;

};

// Upper limit monitor - triggers when value exceeds threshold.
class MonitorUpperLimit : public Monitor {
public:
    MonitorUpperLimit(Clock& clock, MonitorParameter& parameter);	
	bool IsThresholdExceeded() override;
};

class MonitorLowerLimit : public Monitor {
public:
    MonitorLowerLimit(Clock& clock, MonitorParameter& parameter);
	bool IsThresholdExceeded() override;
};

#endif  // CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
