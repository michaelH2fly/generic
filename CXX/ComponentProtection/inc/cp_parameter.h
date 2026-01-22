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
class CPParameter {
	public:
	// Monitor thresholds and debounce times
	float caution_threshold = 0.0f;
	float caution_debounce_time = 0.0f;
	float warning_threshold = 0.0f;
	float warning_debounce_time = 0.0f;
	float warning2_threshold = 0.0f;
	float warning2_debounce_time = 0.0f;

	// Action and shutdown configuration
	CautionAction caution_action = CautionAction::Void;
	ShutdownType warning_sd_type = ShutdownType::NormalSD;
	ShutdownType warning2_sd_type = ShutdownType::NormalSD;

	// Access level
	AccessLevel access_level = AccessLevel::Tester;

	// Optional description
	std::string description = "";

	// Default constructor
	CPParameter() = default;

	// Constructor with all parameters
	CPParameter(
	    float caution_threshold,
	    float caution_debounce_time,
	    float warning_threshold,
	    float warning_debounce_time,
	    float warning2_threshold,
	    float warning2_debounce_time,
	    CautionAction caution_action,
	    ShutdownType warning_sd_type,
	    ShutdownType warning2_sd_type,
	    AccessLevel access_level,
	    const std::string& description = "")
	    : caution_threshold(caution_threshold),
	      caution_debounce_time(caution_debounce_time),
	      warning_threshold(warning_threshold),
	      warning_debounce_time(warning_debounce_time),
	      warning2_threshold(warning2_threshold),
	      warning2_debounce_time(warning2_debounce_time),
	      caution_action(caution_action),
	      warning_sd_type(warning_sd_type),
	      warning2_sd_type(warning2_sd_type),
	      access_level(access_level),
	      description(description) {}
};

#endif  // CXX_COMPONENT_PROTECTION_INC_CP_PARAMETER_H_
