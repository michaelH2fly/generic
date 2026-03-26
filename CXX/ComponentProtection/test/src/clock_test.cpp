#include <gtest/gtest.h>
#include "monitor.h"
#include "clock.h"
#include <stdint.h>


class ClockTest : public ::testing::Test {
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

};

TEST_F(ClockTest, MockClockInitialization) {
    
    Timestamp initial_time = std::chrono::steady_clock::now();

    MockClock mock_clock(initial_time);
    
    EXPECT_EQ(mock_clock.Now(), initial_time);
}

TEST_F(ClockTest, MockClockAdvance) {
    
    // init mock clock
    Timestamp initial_time = std::chrono::steady_clock::now();
    MockClock mock_clock(initial_time);
    
    // advance time
    std::chrono::milliseconds advance_duration(5000); // 5 seconds
    mock_clock.Advance(advance_duration);
    
    // verify time advanced correctly
    EXPECT_EQ(mock_clock.Now(), initial_time + advance_duration);

    // reset time to initial timestamp
    mock_clock.SetTime(initial_time);
    EXPECT_EQ(mock_clock.Now(), initial_time);

}

