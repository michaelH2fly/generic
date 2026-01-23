#include <gtest/gtest.h>
#include "monitor.h"
#include "clock.h"

unsigned int time_reference= (unsigned int)0;

MockClock mock_clock;

// Test fixture for Monitor tests
class MonitorTest : public ::testing::Test {
	protected:
	// Set up test fixtures
	//void SetUp() override {
	//	threshold = 10.0f;
	//	debounce_time = 1.0f;
	//}

	// Tear down - clean up after tests
	void TearDown() override {
		// Clean up if needed
	}

	MonitorParameter parameter{10, 1};	

};

// Test infrastructure: Verify MonitorUpperLimit can be instantiated
TEST_F(MonitorTest, MonitorUpperLimitInstantiation) {
	MonitorUpperLimit monitor(mock_clock, parameter);
	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, 10.0f);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, 1.0f);
}

TEST_F(MonitorTest, MonitorLowerLimitInstantiation) {
	
	MonitorLowerLimit monitor(mock_clock, parameter);
	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, 10.0f);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, 1.0f);
}

