#include <gtest/gtest.h>
#include "component_protection.h"
#include "mock_monitor.h"

using namespace testing;

class ComponentProtectionTest : public ::testing::Test {
	protected:
	// Set up test fixtures
	//void SetUp() override {
	//	threshold = 10.0f;
	//	debounce_time = 1.0f;
	//}

    MockClock mock_clock_;
    float observed_value_ = 0.0f;
    CpParameter parameter_;

    ComponentProtectionTest()
        : mock_clock_(Timestamp{}) {};
	// Tear down - clean up after tests
	void TearDown() override {
		// Clean up if needed
	}

    public:

    ComponentProtection<MockMonitor<MonitorUpperLimit>> InitCpUpperLimit() {
        return ComponentProtection<MockMonitor<MonitorUpperLimit>>(mock_clock_, observed_value_, parameter_);
    };
};

TEST_F(ComponentProtectionTest, abc) {

    ComponentProtection<MockMonitor<MonitorUpperLimit>> monitor = InitCpUpperLimit();
}