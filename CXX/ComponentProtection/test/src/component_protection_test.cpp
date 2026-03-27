#include <gtest/gtest.h>
#include "component_protection.h"
#include "mock_monitor.h"

using namespace testing;

using MockCpUpperLimit = ComponentProtection<MockMonitor<MonitorUpperLimit>>;
using MockCpLowerLimit = ComponentProtection<MockMonitor<MonitorLowerLimit>>;

class ComponentProtectionTest : public ::testing::Test {
	protected:
	// Set up test fixtures
	//void SetUp() override {
	//	threshold = 10.0f;
	//	debounce_time = 1.0f;
	//}

    MockClock mock_clock_;
    float observed_value_ = 0.0f;
    CpParameter ul_parameter_ = {
        .caution_parameter = { .threshold = 2.0f, .debounce_time = 1000 },
        .warning_parameter = { .threshold = 3.0f, .debounce_time = 1000 },
        .warning2_parameter = { .threshold = 4.0f, .debounce_time = 1000 },
        .caution_action = CautionAction::Void,
        .warning_sd_type = ShutdownType::NormalSD
    };

    CpParameter ll_parameter_ = {
    .caution_parameter = { .threshold = 4.0f, .debounce_time = 1000 },
    .warning_parameter = { .threshold = 3.0f, .debounce_time = 1000 },
    .warning2_parameter = { .threshold = 2.0f, .debounce_time = 1000 },
    .caution_action = CautionAction::Void,
    .warning_sd_type = ShutdownType::NormalSD
};


    ComponentProtectionTest()
        : mock_clock_(Timestamp{}) {};
	// Tear down - clean up after tests
	void TearDown() override {
		// Clean up if needed
	}

    public:

    MockCpUpperLimit InitCpUpperLimit() {
        return MockCpUpperLimit(mock_clock_, observed_value_, ul_parameter_);
    };

    MockCpLowerLimit InitCpLowerLimit() {
        return MockCpLowerLimit(mock_clock_, observed_value_, ll_parameter_);
    };
};

TEST_F(ComponentProtectionTest, Parameter_Valid_UpperLimit) {

    MockCpUpperLimit cp_ul = InitCpUpperLimit();

    //EXPECT_EQ(cp.GetLevel(), MockCpUpperLimit::CpLevel::Implausible);

    EXPECT_EQ(cp_ul.ParametersAreValid(), true);


}

TEST_F(ComponentProtectionTest, Parameter_Valid_LowerLimit) {

    MockCpLowerLimit cp_ll = InitCpLowerLimit();

    EXPECT_EQ(cp_ll.ParametersAreValid(), true);
}