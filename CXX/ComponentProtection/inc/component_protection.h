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
        if constexpr (std::is_same_v<MonitorType, MonitorLowerLimit>) {
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
        : parameter_(parameter),          
          type_(DeriveCptype()),
          level_(CpLevel::Implausible),
          is_enabled_(false),
          caution_monitor_(clock, observed_value, parameter.caution_parameter),
          warning_monitor_(clock, observed_value, parameter.warning_parameter),
          warning2_monitor_(clock, observed_value, parameter.warning2_parameter) {

            if (ParametersAreValid()) {
                level_ = CpLevel::Ok;
            } else {
                level_ = CpLevel::Implausible;
            }
          };
          
    // deconstructor
    //~ComponentProtection();
   
    // functional
    void Update(bool do_enable, bool do_reset) {

        // mutate the enable state
        is_enabled_ = do_enable;

        switch(level_) {
            
            case CpLevel::Implausible:
                if (ParametersAreValid()) {level_ = CpLevel::Ok;}
            break;
            case CpLevel::Ok:

                // check warning2 monitor
                if (IsActive(warning2_monitor_)) level_ = CpLevel::Warning2;
                // check warning monitor
                if (IsActive(warning_monitor_)) level_ = CpLevel::Warning;
                // check caution monitor
                if (IsActive(caution_monitor_)) level_ = CpLevel::Caution;   

            break;

            case CpLevel::Caution:

                // check warning2 monitor
                if (IsActive(warning2_monitor_)) level_ = CpLevel::Warning2;
                // check warning monitor
                if (IsActive(warning_monitor_)) level_ = CpLevel::Warning;
                // check caution monitor
                if (IsInactive(caution_monitor_)) level_ = CpLevel::Ok;   
                
            break;

            case CpLevel::Warning:

                // check warning2 monitor
                if (IsActive(warning2_monitor_)) level_ = CpLevel::Warning2;
                // check warning monitor
                if (IsInactive(warning_monitor_)) level_ = CpLevel::WarningLatched;

            break;

            case CpLevel::WarningLatched:

            break;
            case CpLevel::Warning2:
            break;
            case CpLevel::Warning2Latched:
            break;
            case CpLevel::InactiveOk:
            break;
            case CpLevel::InactiveCaution:
            break;
            case CpLevel::InactiveWarning:
            break;
            case CpLevel::InactiveWarningLatched:
            break;
            case CpLevel::InactiveWarning2:
            break;
            case CpLevel::InactiveWarning2Latched:
            break;

        }
        

    }
    // getters
    CpType GetType();
    CpState GetState();
       

    private:

    CpParameter parameter_;
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
    
    bool ParametersAreValid() {
        
        if (type_ == CpType::LowerLimit) {

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
};


#endif  // CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_
