#include <gtest/gtest.h>
#include "component_protection.h"

// Test ComponentProtection class
class ComponentProtectionTest : public ::testing::Test {
	protected:
	ComponentProtectionTest() = default;

	// Helper function to create a sample ComponentProtection
	ComponentProtection CreateSampleProtection() {
	  MonitorUpperLimit caution(3.0f, 2.5f);
	  MonitorUpperLimit warning(5.0f, 2.0f);
	  MonitorUpperLimit warning2(6.0f, 2.0f);

	  return ComponentProtection(
	      "UL_inletTemperature_recirculation_pump", "testsignal",
	      TypeMonitor::UL, caution, CautionAction::Void, warning,
	      ShutdownType::NormalSD, true, warning2, ShutdownType::FastSD,
	      AccessLevel::Tester, "test description");
	}
};

// Test ComponentProtection default construction
TEST_F(ComponentProtectionTest, DefaultConstruction) {
	ComponentProtection cp;
	EXPECT_EQ(cp.GetName(), "");
	EXPECT_EQ(cp.GetObservedSignal(), "");
	EXPECT_EQ(cp.GetDescription(), "");
	EXPECT_FALSE(cp.GetIsActiveWarning2());
}

// Test ComponentProtection full construction
TEST_F(ComponentProtectionTest, FullConstruction) {
	ComponentProtection cp = CreateSampleProtection();
	EXPECT_EQ(cp.GetName(), "UL_inletTemperature_recirculation_pump");
	EXPECT_EQ(cp.GetObservedSignal(), "testsignal");
	EXPECT_EQ(cp.GetTypeMonitor(), TypeMonitor::UL);
	EXPECT_EQ(cp.GetCautionAction(), CautionAction::Void);
	EXPECT_EQ(cp.GetWarningSDType(), ShutdownType::NormalSD);
	EXPECT_TRUE(cp.GetIsActiveWarning2());
	EXPECT_EQ(cp.GetWarning2SDType(), ShutdownType::FastSD);
	EXPECT_EQ(cp.GetAccessLevel(), AccessLevel::Tester);
	EXPECT_EQ(cp.GetDescription(), "test description");
}

// Test ComponentProtection GetName and SetName
TEST_F(ComponentProtectionTest, GetSetName) {
	ComponentProtection cp;
	cp.SetName("test_protection");
	EXPECT_EQ(cp.GetName(), "test_protection");
}

// Test ComponentProtection GetObservedSignal and SetObservedSignal
TEST_F(ComponentProtectionTest, GetSetObservedSignal) {
	ComponentProtection cp;
	cp.SetObservedSignal("signal_1");
	EXPECT_EQ(cp.GetObservedSignal(), "signal_1");
}

// Test ComponentProtection GetTypeMonitor and SetTypeMonitor
TEST_F(ComponentProtectionTest, GetSetTypeMonitor) {
	ComponentProtection cp;
	cp.SetTypeMonitor(TypeMonitor::LL);
	EXPECT_EQ(cp.GetTypeMonitor(), TypeMonitor::LL);
}

// Test ComponentProtection GetDescription and SetDescription
TEST_F(ComponentProtectionTest, GetSetDescription) {
	ComponentProtection cp;
	cp.SetDescription("This is a test");
	EXPECT_EQ(cp.GetDescription(), "This is a test");
}

// Test ComponentProtection GetIsActiveWarning2 and SetIsActiveWarning2
TEST_F(ComponentProtectionTest, GetSetIsActiveWarning2) {
	ComponentProtection cp;
	EXPECT_FALSE(cp.GetIsActiveWarning2());
	cp.SetIsActiveWarning2(true);
	EXPECT_TRUE(cp.GetIsActiveWarning2());
}

// Test ComponentProtection GetCautionMonitor and SetCautionMonitor
TEST_F(ComponentProtectionTest, GetSetCautionMonitor) {
	ComponentProtection cp;
	MonitorLowerLimit monitor(25.0f, 1.5f);
	cp.SetCautionMonitor(monitor);
	EXPECT_FLOAT_EQ(cp.GetCautionMonitor().GetThreshold(), 25.0f);
	EXPECT_FLOAT_EQ(cp.GetCautionMonitor().GetDebounceTime(), 1.5f);
}

// Test ComponentProtection GetWarningMonitor and SetWarningMonitor
TEST_F(ComponentProtectionTest, GetSetWarningMonitor) {
	ComponentProtection cp;
	MonitorUpperLimit monitor(50.0f, 2.0f);
	cp.SetWarningMonitor(monitor);
	EXPECT_FLOAT_EQ(cp.GetWarningMonitor().GetThreshold(), 50.0f);
	EXPECT_FLOAT_EQ(cp.GetWarningMonitor().GetDebounceTime(), 2.0f);
}

// Test ComponentProtection GetWarning2Monitor and SetWarning2Monitor
TEST_F(ComponentProtectionTest, GetSetWarning2Monitor) {
	ComponentProtection cp;
	MonitorLowerLimit monitor(10.0f, 0.5f);
	cp.SetWarning2Monitor(monitor);
	EXPECT_FLOAT_EQ(cp.GetWarning2Monitor().GetThreshold(), 10.0f);
	EXPECT_FLOAT_EQ(cp.GetWarning2Monitor().GetDebounceTime(), 0.5f);
}

// Test ComponentProtection GetCautionAction and SetCautionAction
TEST_F(ComponentProtectionTest, GetSetCautionAction) {
	ComponentProtection cp;
	cp.SetCautionAction(CautionAction::Void);
	EXPECT_EQ(cp.GetCautionAction(), CautionAction::Void);
}

// Test ComponentProtection GetWarningSDType and SetWarningSDType
TEST_F(ComponentProtectionTest, GetSetWarningSDType) {
	ComponentProtection cp;
	cp.SetWarningSDType(ShutdownType::FastSD);
	EXPECT_EQ(cp.GetWarningSDType(), ShutdownType::FastSD);
}

// Test ComponentProtection GetWarning2SDType and SetWarning2SDType
TEST_F(ComponentProtectionTest, GetSetWarning2SDType) {
	ComponentProtection cp;
	cp.SetWarning2SDType(ShutdownType::HardSD);
	EXPECT_EQ(cp.GetWarning2SDType(), ShutdownType::HardSD);
}

// Test ComponentProtection GetAccessLevel and SetAccessLevel
TEST_F(ComponentProtectionTest, GetSetAccessLevel) {
	ComponentProtection cp;
	cp.SetAccessLevel(AccessLevel::Tester);
	EXPECT_EQ(cp.GetAccessLevel(), AccessLevel::Tester);
}

// Test ComponentProtection with different monitor types
TEST_F(ComponentProtectionTest, DifferentMonitorTypes) {
	MonitorLowerLimit caution(5.0f, 1.0f);
	MonitorUpperLimit warning(10.0f, 1.5f);
	MonitorLowerLimit warning2(2.0f, 0.5f);

	ComponentProtection cp(
	    "mixed_protection", "mixed_signal", TypeMonitor::UL, caution,
	    CautionAction::Void, warning, ShutdownType::NormalSD, true, warning2,
	    ShutdownType::FastSD, AccessLevel::Tester, "mixed monitors");

	EXPECT_EQ(cp.GetName(), "mixed_protection");
	EXPECT_FLOAT_EQ(cp.GetCautionMonitor().GetThreshold(), 5.0f);
	EXPECT_FLOAT_EQ(cp.GetWarningMonitor().GetThreshold(), 10.0f);
	EXPECT_FLOAT_EQ(cp.GetWarning2Monitor().GetThreshold(), 2.0f);
}
