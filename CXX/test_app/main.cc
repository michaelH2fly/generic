#include <iostream>
#include "component_protection.h"

int main() {
	std::cout << "=== ComponentProtection Test Application ===" << std::endl;
	std::cout << std::endl;

	// Test 1: Create CPParameter object
	std::cout << "Test 1: Create CPParameter" << std::endl;
	CPParameter params(
	    3.0f, 2.5f,  // Caution threshold and debounce time
	    5.0f, 2.0f,  // Warning threshold and debounce time
	    6.0f, 2.0f,  // Warning2 threshold and debounce time
	    CautionAction::Void,
	    ShutdownType::NormalSD,
	    ShutdownType::FastSD,
	    AccessLevel::Tester,
	    "test protection");

	std::cout << "  Caution Threshold: " << params.caution_threshold << std::endl;
	std::cout << "  Warning Threshold: " << params.warning_threshold << std::endl;
	std::cout << "  Warning2 Threshold: " << params.warning2_threshold << std::endl;
	std::cout << "  Description: " << params.description << std::endl;
	std::cout << std::endl;

	// Test 2: Create ComponentProtection with default constructor
	std::cout << "Test 2: ComponentProtection with default constructor" << std::endl;
	ComponentProtection cp1;
	std::cout << "  Name: " << cp1.GetName() << std::endl;
	std::cout << "  Observed Signal: " << cp1.GetObservedSignal() << std::endl;
	std::cout << "  Parameters Description: " << cp1.GetParameters().description
	          << std::endl;
	std::cout << std::endl;

	// Test 3: Create ComponentProtection with full constructor using different monitor types
	std::cout << "Test 3: ComponentProtection with mixed monitor types" << std::endl;
	ComponentProtection cp2(
	    "UL_inletTemperature_recirculation_pump",
	    "testsignal",
	    TypeMonitor::UL,
	    std::make_unique<MonitorUpperLimit>(params.caution_threshold, params.caution_debounce_time),
	    std::make_unique<MonitorLowerLimit>(params.warning_threshold, params.warning_debounce_time),  // Different type!
	    std::make_unique<MonitorUpperLimit>(params.warning2_threshold, params.warning2_debounce_time),
	    params);

	std::cout << "  Name: " << cp2.GetName() << std::endl;
	std::cout << "  Observed Signal: " << cp2.GetObservedSignal() << std::endl;
	std::cout << "  Type Monitor: " << (cp2.GetTypeMonitor() == TypeMonitor::UL ? "UL" : "LL")
	          << std::endl;

	// Test monitor polymorphism
	Monitor* caution = cp2.GetCautionMonitor();
	Monitor* warning = cp2.GetWarningMonitor();
	Monitor* warning2 = cp2.GetWarning2Monitor();

	std::cout << "  Caution Threshold Exceeded (value=2.0): "
	          << (caution->IsThresholdExceeded(2.0f) ? "true" : "false") << std::endl;
	std::cout << "  Warning Threshold Exceeded (value=4.0): "
	          << (warning->IsThresholdExceeded(4.0f) ? "true" : "false") << std::endl;
	std::cout << "  Warning2 Threshold Exceeded (value=7.0): "
	          << (warning2->IsThresholdExceeded(7.0f) ? "true" : "false") << std::endl;
	std::cout << std::endl;

	// Test 4: Modify ComponentProtection using setters
	std::cout << "Test 4: Modify ComponentProtection using setters" << std::endl;
	cp1.SetName("Modified Protection");
	cp1.SetObservedSignal("modified_signal");

	CPParameter new_params(
	    10.0f, 2.0f,  // Caution
	    15.0f, 2.0f,  // Warning
	    20.0f, 2.0f,  // Warning2
	    CautionAction::Void,
	    ShutdownType::NormalSD,
	    ShutdownType::FastSD,
	    AccessLevel::Tester,
	    "Updated parameters");
	cp1.SetParameters(new_params);

	// Replace monitor with different type (using new_params members)
	cp1.SetWarningMonitor(std::make_unique<MonitorLowerLimit>(new_params.warning_threshold, new_params.warning_debounce_time));

	std::cout << "  Updated Name: " << cp1.GetName() << std::endl;
	std::cout << "  Updated Observed Signal: " << cp1.GetObservedSignal() << std::endl;
	std::cout << "  Updated Caution Threshold: "
	          << cp1.GetParameters().caution_threshold << std::endl;
	std::cout << "  Updated Description: " << cp1.GetParameters().description
	          << std::endl;
	std::cout << std::endl;

	// Test 5: Demonstrate monitor polymorphism with different types
	std::cout << "Test 5: Monitor polymorphism demonstration" << std::endl;
	CPParameter test_params(
	    100.0f, 1.0f,  // UL thresholds
	    50.0f, 1.0f,   // LL thresholds
	    75.0f, 1.0f,   // Warning2
	    CautionAction::Void,
	    ShutdownType::NormalSD,
	    ShutdownType::FastSD,
	    AccessLevel::Tester,
	    "Test parameters");
	
	auto ul_monitor = std::make_unique<MonitorUpperLimit>(test_params.caution_threshold, test_params.caution_debounce_time);
	auto ll_monitor = std::make_unique<MonitorLowerLimit>(test_params.warning_threshold, test_params.warning_debounce_time);

	std::cout << "  Upper Limit Monitor (threshold=100):" << std::endl;
	std::cout << "    Value 99: " << (ul_monitor->IsThresholdExceeded(99.0f) ? "exceeded" : "ok")
	          << std::endl;
	std::cout << "    Value 101: " << (ul_monitor->IsThresholdExceeded(101.0f) ? "exceeded" : "ok")
	          << std::endl;

	std::cout << "  Lower Limit Monitor (threshold=50):" << std::endl;
	std::cout << "    Value 49: " << (ll_monitor->IsThresholdExceeded(49.0f) ? "exceeded" : "ok")
	          << std::endl;
	std::cout << "    Value 51: " << (ll_monitor->IsThresholdExceeded(51.0f) ? "exceeded" : "ok")
	          << std::endl;
	std::cout << std::endl;

	std::cout << "=== All tests completed successfully ===" << std::endl;
	return 0;
}
