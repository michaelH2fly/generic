#ifndef CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_
#define CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_

#include <string>
#include <memory>
#include "monitor.h"
#include "cp_parameter.h"

template <typename MonitorType>
class ComponentProtection {

    public: 
    
    enum class CpLevel : int8_t {
        Implausible = -1, 
        Ok = 1,
        Caution = 2,
        Warning = 3,
        WarningLatched = 4,
        Warning2 = 5,
        Warning2Latched = 6,
        InactiveOk = 7,
        InactiveCaution = 8,
        InactiveWarning = 9,
        InactiveWarningLatched = 10,
        InactiveWarning2 = 11,
        InactiveWarning2Latched = 12,
    };

    enum class CpType : uint8_t {
        LowerLimit = 0,
        UpperLimit = 1
    };

    enum class CpState : int8_t {
        Implausible = -1, 
        Ok = 1,
        Caution = 2,
        Warning = 3,
        WarningLatched = 4,
        Warning2 = 5,
        Warning2Latched = 6        
    };

    static_assert(std::is_base_of<Monitor, MonitorType>::value,
                "MonitorType must inherit from MonitorBase");

    // determine type at compile time
    static constexpr CpType DeriveCptype() {
        if constexpr (std::is_base_of<MonitorLowerLimit, MonitorType>::value) {
            return CpType::LowerLimit;
        } else {
            return CpType::UpperLimit;
        }
    }

    

    // class members
    CpLevel level_;
    CpType type_;
    bool is_enabled_;
    
    // constructor
    ComponentProtection(Clock& clock, float& observed_value, CpParameter& parameter)
        : level_(CpLevel::Implausible),
          type_(DeriveCptype()),
          is_enabled_(false),
          parameter_(parameter),   
          caution_monitor_(clock, observed_value, parameter_.caution_parameter),
          warning_monitor_(clock, observed_value, parameter_.warning_parameter),
          warning2_monitor_(clock, observed_value, parameter_.warning2_parameter) {

            if (ParametersAreValid()) {
                level_ = CpLevel::Ok;
            } else {
                level_ = CpLevel::Implausible;
            }
          };
          
    // deconstructor
    //~ComponentProtection();
   
    // functional
    void Update(bool do_enable, bool do_reset);
    
    // getters
    CpType GetType(void) { return type_; };
    CpState GetState();
    CpLevel GetLevel() { return level_;};
    CpParameter& GetParameter() { return parameter_; };
    MonitorType& GetCautionMonitor() { return caution_monitor_; };
    MonitorType& GetWarningMonitor() { return warning_monitor_; };
    MonitorType& GetWarning2Monitor() { return warning2_monitor_; };

    bool ParametersAreValid() {
        
        if (type_ == CpType::UpperLimit) {

            if (parameter_.caution_parameter.threshold > parameter_.warning_parameter.threshold) {
                return false;
            }
            if (parameter_.warning_parameter.threshold > parameter_.warning2_parameter.threshold) {
                return false;
            }            
        } else {
            if (parameter_.caution_parameter.threshold < parameter_.warning_parameter.threshold) {
                return false;
            }
            if (parameter_.warning_parameter.threshold < parameter_.warning2_parameter.threshold) {
                return false;
            }
        }
        return true;
    };

    private:

    CpParameter& parameter_;
    MonitorType caution_monitor_;
    MonitorType warning_monitor_;
    MonitorType warning2_monitor_; 

    bool IsActive(MonitorType monitor) {
        if (monitor.GetState() == Monitor::MonitorState::Active) {
            return true; 
        } else {
            return false;
        }
    };

    bool IsInactive(MonitorType monitor){
        if (monitor.GetState() == Monitor::MonitorState::Inactive) {
            return true;
        } else {
            return false;
        }
    };
    
    
};


#endif  // CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_
