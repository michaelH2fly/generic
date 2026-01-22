#include "component_protection.h"

// ComponentProtection Implementation
ComponentProtection::ComponentProtection()
	  : name_(""),
	    observed_signal_(""),
	    type_monitor_(TypeMonitor::UL),
	    parameters_(CPParameter()),
	    caution_monitor_(std::make_unique<MonitorUpperLimit>(parameters_.caution_threshold, parameters_.caution_debounce_time)),
	    warning_monitor_(std::make_unique<MonitorUpperLimit>(parameters_.warning_threshold, parameters_.warning_debounce_time)),
	    warning2_monitor_(std::make_unique<MonitorUpperLimit>(parameters_.warning2_threshold, parameters_.warning2_debounce_time)) {}

ComponentProtection::ComponentProtection(
	  const std::string& name,
	  const std::string& observed_signal,
	  TypeMonitor type_monitor,
	  std::unique_ptr<Monitor> caution_monitor,
	  std::unique_ptr<Monitor> warning_monitor,
	  std::unique_ptr<Monitor> warning2_monitor,
	  const CPParameter& parameters)
	  : name_(name),
	    observed_signal_(observed_signal),
	    type_monitor_(type_monitor),
	    parameters_(parameters),
	    caution_monitor_(std::move(caution_monitor)),
	    warning_monitor_(std::move(warning_monitor)),
	    warning2_monitor_(std::move(warning2_monitor)) {}

// Getters for basic properties
const std::string& ComponentProtection::GetName() const {
	return name_;
}

const std::string& ComponentProtection::GetObservedSignal() const {
	return observed_signal_;
}

TypeMonitor ComponentProtection::GetTypeMonitor() const {
	return type_monitor_;
}

// Getters for monitors
Monitor* ComponentProtection::GetCautionMonitor() const {
	return caution_monitor_.get();
}

Monitor* ComponentProtection::GetWarningMonitor() const {
	return warning_monitor_.get();
}

Monitor* ComponentProtection::GetWarning2Monitor() const {
	return warning2_monitor_.get();
}

// Getter for parameters
const CPParameter& ComponentProtection::GetParameters() const {
	return parameters_;
}

// Setters for basic properties
void ComponentProtection::SetName(const std::string& name) {
	name_ = name;
}

void ComponentProtection::SetObservedSignal(const std::string& observed_signal) {
	observed_signal_ = observed_signal;
}

void ComponentProtection::SetTypeMonitor(TypeMonitor type_monitor) {
	type_monitor_ = type_monitor;
}

// Setters for monitors
void ComponentProtection::SetCautionMonitor(std::unique_ptr<Monitor> caution_monitor) {
	caution_monitor_ = std::move(caution_monitor);
}

void ComponentProtection::SetWarningMonitor(std::unique_ptr<Monitor> warning_monitor) {
	warning_monitor_ = std::move(warning_monitor);
}

void ComponentProtection::SetWarning2Monitor(std::unique_ptr<Monitor> warning2_monitor) {
	warning2_monitor_ = std::move(warning2_monitor);
}

// Setter for parameters
void ComponentProtection::SetParameters(const CPParameter& parameters) {
	parameters_ = parameters;
}
