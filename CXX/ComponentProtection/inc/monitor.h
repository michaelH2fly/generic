#ifndef CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
#define CXX_COMPONENT_PROTECTION_INC_MONITOR_H_

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
	Monitor(unsigned int &time_reference, MonitorParameter& parameter)
	    : time_reference_(time_reference),
	      parameter_(parameter) {};


	// Virtual step function (cyclic execution).
	virtual void Step(bool is_active, bool do_reset);

	// Getters - normal functions (same behavior for all subclasses).
	const MonitorParameter& GetParameter() const;
	// Setters - normal functions (same behavior for all subclasses).
	void SetParameter(MonitorParameter& parameter);

	// Check if value exceeds threshold (must be implemented by derived classes).

	private:	
	unsigned int& time_reference_;

	protected:
	MonitorParameter& parameter_;
	MonitorState state_ = MonitorState::Inactive;
};

// Upper limit monitor - triggers when value exceeds threshold.
class MonitorUpperLimit : public Monitor {
public:
    MonitorUpperLimit(unsigned int &time_reference, MonitorParameter& parameter);
	void Step(bool is_active, bool do_reset) override;
};

class MonitorLowerLimit : public Monitor {
public:
    MonitorLowerLimit(unsigned int &time_reference, MonitorParameter& parameter);
	void Step(bool is_active, bool do_reset) override;
};

#endif  // CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
