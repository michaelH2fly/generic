#include <gtest/gtest.h>
#include "monitor.h"

// Test Monitor base class instantiation through derived classes
class MonitorTest : public ::testing::Test {
	protected:
	MonitorTest() = default;
};

// Test MonitorUpperLimit construction
TEST_F(MonitorTest, MonitorUpperLimitConstruction) {
	MonitorUpperLimit monitor(100.0f, 2.5f);
	EXPECT_FLOAT_EQ(monitor.GetThreshold(), 100.0f);
	EXPECT_FLOAT_EQ(monitor.GetDebounceTime(), 2.5f);
}

// Test MonitorLowerLimit construction
TEST_F(MonitorTest, MonitorLowerLimitConstruction) {
	MonitorLowerLimit monitor(50.0f, 1.5f);
	EXPECT_FLOAT_EQ(monitor.GetThreshold(), 50.0f);
	EXPECT_FLOAT_EQ(monitor.GetDebounceTime(), 1.5f);
}

// Test MonitorUpperLimit default construction
TEST_F(MonitorTest, MonitorUpperLimitDefaultConstruction) {
	MonitorUpperLimit monitor;
	EXPECT_FLOAT_EQ(monitor.GetThreshold(), 0.0f);
	EXPECT_FLOAT_EQ(monitor.GetDebounceTime(), 0.0f);
}

// Test MonitorUpperLimit threshold exceeded detection
TEST_F(MonitorTest, MonitorUpperLimitThresholdExceeded) {
	MonitorUpperLimit monitor(100.0f, 2.5f);
	EXPECT_FALSE(monitor.IsThresholdExceeded(99.0f));
	EXPECT_FALSE(monitor.IsThresholdExceeded(100.0f));
	EXPECT_TRUE(monitor.IsThresholdExceeded(101.0f));
}

// Test MonitorLowerLimit threshold exceeded detection
TEST_F(MonitorTest, MonitorLowerLimitThresholdExceeded) {
	MonitorLowerLimit monitor(50.0f, 1.5f);
	EXPECT_TRUE(monitor.IsThresholdExceeded(49.0f));
	EXPECT_FALSE(monitor.IsThresholdExceeded(50.0f));
	EXPECT_FALSE(monitor.IsThresholdExceeded(51.0f));
}

// Test Monitor threshold setter
TEST_F(MonitorTest, MonitorSetThreshold) {
	MonitorUpperLimit monitor(100.0f, 2.5f);
	monitor.SetThreshold(150.0f);
	EXPECT_FLOAT_EQ(monitor.GetThreshold(), 150.0f);
}

// Test Monitor debounce time setter
TEST_F(MonitorTest, MonitorSetDebounceTime) {
	MonitorLowerLimit monitor(50.0f, 1.5f);
	monitor.SetDebounceTime(3.0f);
	EXPECT_FLOAT_EQ(monitor.GetDebounceTime(), 3.0f);
}

// Test Monitor boundary condition at threshold
TEST_F(MonitorTest, MonitorUpperLimitBoundary) {
	MonitorUpperLimit monitor(100.0f, 2.5f);
	EXPECT_FALSE(monitor.IsThresholdExceeded(100.0f));
	EXPECT_TRUE(monitor.IsThresholdExceeded(100.0001f));
}

// Test Monitor boundary condition at threshold for lower limit
TEST_F(MonitorTest, MonitorLowerLimitBoundary) {
	MonitorLowerLimit monitor(50.0f, 1.5f);
	EXPECT_FALSE(monitor.IsThresholdExceeded(50.0f));
	EXPECT_TRUE(monitor.IsThresholdExceeded(49.9999f));
}
