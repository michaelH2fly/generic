#ifndef CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
#define CXX_COMPONENT_PROTECTION_INC_MONITOR_H_

// Monitor base class and derived monitor types for component protection.

// monitor state enum
enum class MonitorState {
	Inactive = 1,
	Debouncing = 2,
	Active = 3
};

// Monitor configuration with threshold and debounce time.
class Monitor {
	public:
	// Virtual destructor for proper cleanup in derived classes.
	virtual ~Monitor() = default;

	// Constructor with default values.
	Monitor(float &threshold, float &debounce_time);


	// Virtual step function (cyclic execution).
	virtual void Step(bool is_active, bool do_reset);

	// Getters - normal functions (same behavior for all subclasses).
	float GetThreshold() const;
	float GetDebounceTime() const;

	// Setters - normal functions (same behavior for all subclasses).
	void SetThreshold(float threshold);
	void SetDebounceTime(float debounce_time);

	// Check if value exceeds threshold (must be implemented by derived classes).
	virtual bool IsThresholdExceeded(float value) const = 0;

	private:
	MonitorState state_ = MonitorState::Inactive;

	protected:
	float& threshold_;
	float& debounce_time_;
};

// Upper limit monitor - triggers when value exceeds threshold.
class MonitorUpperLimit : public Monitor {
	public:
	MonitorUpperLimit(float &threshold, float &debounce_time);
	bool IsThresholdExceeded(float value) const override;
};

// Lower limit monitor - triggers when value falls below threshold.
class MonitorLowerLimit : public Monitor {
	public:
	MonitorLowerLimit(float &threshold, float &debounce_time);
	bool IsThresholdExceeded(float value) const override;
};

#endif  // CXX_COMPONENT_PROTECTION_INC_MONITOR_H_
