#include <gtest/gtest.h>
#include "monitor.h"
#include "clock.h"

unsigned int time_reference= (unsigned int)0;

MockClock mock_clock;

// Test fixture for Monitor tests
class MonitorTest : public::testing::Test {
	protected:

	MockClock mock_clock_;
	MonitorParameter parameter_{10, 2000};	
	float observed_value_ = 0.0f;

	// constructor
	MonitorTest() 
		: mock_clock_(Timestamp{}) {};

	// Tear down - clean up after tests
	void TearDown() override {
		// Clean up if needed
	}

	public:
	
	MonitorUpperLimit InitUpperLimitMonitor() {		
		return MonitorUpperLimit(mock_clock_, observed_value_, parameter_);
	}
	MonitorLowerLimit InitLowerLimitMonitor() {		
		return MonitorLowerLimit(mock_clock_, observed_value_, parameter_);
	}
};

// Test infrastructure: Verify MonitorUpperLimit can be instantiated
TEST_F(MonitorTest, MonitorUpperLimitInstantiation) {

	MonitorUpperLimit monitor = InitUpperLimitMonitor();

	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, 10.0f);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, 2000.0f);
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);
}

TEST_F(MonitorTest, MonitorLowerLimitInstantiation) {

	MonitorLowerLimit monitor = InitLowerLimitMonitor();

	EXPECT_FLOAT_EQ(monitor.GetParameter().threshold, 10.0f);
	EXPECT_FLOAT_EQ(monitor.GetParameter().debounce_time, 2000.0f);
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);
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

TEST_F(MonitorTest, MonitorLLGoesActive) {

	MonitorLowerLimit monitor = InitLowerLimitMonitor();
	
	// reminder: threshold is 10.0f
	observed_value_ = 15.0f;
	
	// execute state machine
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);

	// exceed threshold
	observed_value_ = 5.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);
	
	// advance time within debounce time	
	mock_clock_.Advance(std::chrono::milliseconds(1900));
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);

	// advance time to exceed debounce time
	mock_clock_.Advance(std::chrono::milliseconds(200));
	monitor.Update();

	auto now = monitor.GetClock().Now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();	

	std::cout << "Current State: " << static_cast<int>(monitor.GetState()) << std::endl;
	std::cout << "Current Clock (ms): " << ms << std::endl;

	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Active);

	// drop below threshold again
	observed_value_ = 15.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);

}

TEST_F(MonitorTest, MonitorLLGoesInactiveAfterDebounce) {

	MonitorLowerLimit monitor = InitLowerLimitMonitor();
	
	// reminder: threshold is 10.0f
	observed_value_ = 15.0f;
		
	// execute state machine
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);

	// exceed threshold
	observed_value_ = 5.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);
	
	// advance time within debounce time	
	mock_clock_.Advance(std::chrono::milliseconds(1900));
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);

	// drop below threshold again
	observed_value_ = 15.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);
}

TEST_F(MonitorTest, MonitorULGoesActive) {

	MonitorUpperLimit monitor = InitUpperLimitMonitor();
	
	// reminder: threshold is 10.0f
	observed_value_ = 5.0f;
		
	// execute state machine
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);

	// exceed threshold
	observed_value_ = 15.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);
	
	// advance time within debounce time	
	mock_clock_.Advance(std::chrono::milliseconds(1900));
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);

	// advance time to exceed debounce time
	mock_clock_.Advance(std::chrono::milliseconds(200));
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Active);

	// drop below threshold again
	observed_value_ = 5.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);
}

TEST_F(MonitorTest, MonitorULGoesInactiveAfterDebounce) {

	MonitorUpperLimit monitor = InitUpperLimitMonitor();
	
	// reminder: threshold is 10.0f
	observed_value_ = 5.0f;
		
	// execute state machine
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);

	// exceed threshold
	observed_value_ = 15.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);
	
	// advance time within debounce time	
	mock_clock_.Advance(std::chrono::milliseconds(1900));
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Debouncing);

	// advance time to exceed debounce time
	mock_clock_.Advance(std::chrono::milliseconds(200));
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Active);

	// drop below threshold again
	observed_value_ = 5.0f;
	monitor.Update();
	EXPECT_EQ(monitor.GetState(), Monitor::MonitorState::Inactive);
}