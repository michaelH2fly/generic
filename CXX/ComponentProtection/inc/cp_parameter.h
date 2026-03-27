#ifndef CXX_COMPONENT_PROTECTION_INC_CP_PARAMETER_H_
#define CXX_COMPONENT_PROTECTION_INC_CP_PARAMETER_H_

#include <string>

enum class CautionAction {
	Void
};

enum class ShutdownType {
	NormalSD,  // Normal shutdown
	FastSD,    // Fast shutdown
	HardSD     // Hard shutdown
};

enum class AccessLevel {
	Tester
};

// Component Protection Parameters - struct-like class with public members.
// Contains all configuration parameters for component protection thresholds,
// actions, and access levels.

struct MonitorParameter {
	float threshold;
	float debounce_time;
};


struct CpParameter {
	// Monitor thresholds and debounce times
	MonitorParameter caution_parameter;
	MonitorParameter warning_parameter;
	MonitorParameter warning2_parameter;

	// Action and shutdown configuration
	CautionAction caution_action = CautionAction::Void;
	ShutdownType warning_sd_type = ShutdownType::NormalSD;
	ShutdownType warning2_sd_type = ShutdownType::NormalSD;

};

#endif  // CXX_COMPONENT_PROTECTION_INC_CP_PARAMETER_H_
