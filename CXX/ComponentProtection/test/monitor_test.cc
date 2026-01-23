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

	MonitorParameter parameter_{10, 1};	
	float observed_value_ = 0.0f;

	public:

	

	MonitorUpperLimit InitUpperLimitMonitor() {		
		MockClock mock_clock(std::chrono::steady_clock::now());
		return MonitorUpperLimit(mock_clock, observed_value_, parameter_);
	}
	MonitorLowerLimit InitLowerLimitMonitor() {		
		MockClock mock_clock(std::chrono::steady_clock::now());
		return MonitorLowerLimit(mock_clock, observed_value_, parameter_);
	}

};

// Test infrastructure: Verify MonitorUpperLimit can be instantiated
TEST_F(MonitorTest, MonitorUpperLimitInstantiation) {

	MonitorUpperLimit monitor = InitUpperLimitMonitor();

	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, 10.0f);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, 1.0f);
}

TEST_F(MonitorTest, MonitorLowerLimitInstantiation) {

	MonitorLowerLimit monitor = InitLowerLimitMonitor();

	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, 10.0f);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, 1.0f);
}

TEST_F(MonitorTest, MonitorParameterChange) {

	// this test checks the parameter change functionality via reference

	MonitorLowerLimit monitor = InitLowerLimitMonitor();
	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, parameter_.threshold);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, parameter_.debounce_time);

	// change the parameter on the reference
	parameter_.threshold = 20.0f;
	parameter_.debounce_time = 2.0f;

	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, parameter_.threshold);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, parameter_.debounce_time);

}

TEST_F(MonitorTest, MonitorUpperLimitThresholdCheck) {

	MonitorUpperLimit monitor = InitUpperLimitMonitor();
	
	// reminder: threshold is 10.0f
	observed_value_ = 5.0f;
	bool exceeded = monitor.IsThresholdExceeded();
	EXPECT_FALSE(exceeded); 
	observed_value_ = 15.0f;
	exceeded = monitor.IsThresholdExceeded();
	EXPECT_TRUE(exceeded);
}

TEST_F(MonitorTest, MonitorLowerLimitThresholdCheck) {

	MonitorLowerLimit monitor = InitLowerLimitMonitor();
	
	// reminder: threshold is 10.0f
	observed_value_ = 15.0f;
	bool exceeded = monitor.IsThresholdExceeded();
	EXPECT_FALSE(exceeded); 
	observed_value_ = 5.0f;
	exceeded = monitor.IsThresholdExceeded();
	EXPECT_TRUE(exceeded);
}

