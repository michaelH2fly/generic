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
        .caution_parameter = { .threshold = 2.1f, .debounce_time = 1000 },
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

TEST_F(ComponentProtectionTest, ComponentProtectionTest_Initialization) {

    MockCpUpperLimit cp_ul = InitCpUpperLimit();
    MockCpLowerLimit cp_ll = InitCpLowerLimit();
    
    // checks for upper limits CP
    EXPECT_EQ(cp_ul.ParametersAreValid(), true);
    EXPECT_EQ(cp_ul.GetLevel(), MockCpUpperLimit::CpLevel::Ok);
    EXPECT_EQ(cp_ul.GetType(), MockCpUpperLimit::CpType::UpperLimit);

    // checks for lower limits CP
    EXPECT_EQ(cp_ll.ParametersAreValid(), true);
    EXPECT_EQ(cp_ll.GetLevel(),MockCpLowerLimit::CpLevel::Ok);
    EXPECT_EQ(cp_ll.GetType(), MockCpLowerLimit::CpType::LowerLimit);

    // Manipulation of parameter via reference
    ul_parameter_.caution_parameter.threshold = 5.0f;

    // check if change via reference is working
    EXPECT_FLOAT_EQ(ul_parameter_.caution_parameter.threshold, cp_ul.GetParameter().caution_parameter.threshold);

    // check if parameter check fails after updating the cp object
    cp_ul.Update(false, false);
    EXPECT_EQ(cp_ul.ParametersAreValid(), false);
    //EXPECT_EQ(cp_ul.GetLevel(), MockCpUpperLimit::CpLevel::Implausible);


}

TEST_F(ComponentProtectionTest, Check_Caution_Functionality) {

    MockCpUpperLimit cp_ul = InitCpUpperLimit();

    // expect cp-level to be OK after initialization
    EXPECT_EQ(cp_ul.GetLevel(), MockCpUpperLimit::CpLevel::Ok);
    
    // provoke a caution level by mocking the state of the cuaution monitor
    cp_ul.GetCautionMonitor().SetState(Monitor::MonitorState::Active);
    cp_ul.Update(true, false);
    EXPECT_EQ(cp_ul.GetLevel(), MockCpUpperLimit::CpLevel::Caution);

    // set back the caution monitor to inactive and check if level goes back to OK
    cp_ul.GetCautionMonitor().SetState(Monitor::MonitorState::Inactive);
    cp_ul.Update(true, false);
    EXPECT_EQ(cp_ul.GetLevel(), MockCpUpperLimit::CpLevel::Ok);

   
}