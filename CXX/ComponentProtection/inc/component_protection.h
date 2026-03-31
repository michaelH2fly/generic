#ifndef CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_
#define CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_

#include <string>
#include <memory>
#include "monitor.h"
#include "cp_parameter.h"

template <typename MonitorType>
class ComponentProtection {

    public: 
    
    enum class CpState : int8_t {
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
        InactiveWarning2 = 11,
    };

    enum class CpType : uint8_t {
        LowerLimit = 0,
        UpperLimit = 1
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
    CpState state_;
    CpType type_;
    bool is_enabled_;
    
    // constructor
    ComponentProtection(Clock& clock, float& observed_value, CpParameter& parameter)
        : state_(CpState::Implausible),
          type_(DeriveCptype()),
          is_enabled_(false),
          parameter_(parameter),   
          caution_monitor_(clock, observed_value, parameter_.caution_parameter),
          warning_monitor_(clock, observed_value, parameter_.warning_parameter),
          warning2_monitor_(clock, observed_value, parameter_.warning2_parameter) {

            if (ParametersAreValid()) {
                EntryOk(false);                
            } else {
                state_ = CpState::Implausible;
            }
        };
          
    // deconstructor
    //~ComponentProtection();
   
    // functional    
    
    void Update(bool do_enable, bool do_reset_flank) {

        // mutate the enable state
        is_enabled_ = do_enable;

        switch(state_) {
            
            case CpState::Implausible:
                if (ParametersAreValid()) {state_ = CpState::Ok;}
            break;

            case CpState::Ok:
            case CpState::InactiveOk:

                UpdateSubLevelsOk(do_enable, do_reset_flank); 

            break;

            case CpState::Caution:
            case CpState::InactiveCaution:

                UpdateSubLevelsCaution(do_enable, do_reset_flank);
                
            break;

            case CpState::Warning:
            case CpState::WarningLatched:
            case CpState::InactiveWarning:

                UpdateSubLevelsWarning(do_enable, do_reset_flank);

            break;

            case CpState::Warning2:
            case CpState::Warning2Latched:
            case CpState::InactiveWarning2:

                UpdateSubLevelsWarning2(do_enable, do_reset_flank);

            break;
           
        }
    };

    void UpdateSubLevelsOk(bool do_enable, bool do_reset_flank) {
        
        switch (state_){
            case CpState::Ok:

                // for disable set level to InactiveOk
                if (!do_enable) state_ = CpState::InactiveOk;                
                break;

            case CpState::InactiveOk:

                // enable Component Protection
                if (do_enable) state_ = CpState::Ok;
                break;

            default:
                break;

        }

        // out-ok transitions (escalating)
        // ---------------------------------------------
        if (IsActive(warning2_monitor_)) {
            EntryWarning2(do_enable);
        }

        if (IsActive(warning_monitor_)) {
            EntryWarning(do_enable);
        }

        if (IsActive(caution_monitor_)) {
            EntryCaution(do_enable);
        }
    };

    void UpdateSubLevelsCaution(bool do_enable, bool do_reset_flank) {

        switch (state_)
        {
            case CpState::Caution:

                if (!do_enable) state_ = CpState::InactiveCaution;
                break; 
            
            case CpState::InactiveCaution:

                if (do_enable) state_ = CpState::Caution;
                break;
            
            default:
                break;
        }

        // out-cautions transitions (escalating)
        // ---------------------------------------------
        if (IsActive(warning2_monitor_)) {
            EntryWarning2(do_enable);
        }

        if (IsActive(warning_monitor_)) {
            EntryWarning(do_enable);    
        }

        // out-cautions (de-escalating)
        // ---------------------------------------------
        if (IsInactive(caution_monitor_)) {
            EntryOk(do_enable);
        }


    };

    void UpdateSubLevelsWarning(bool do_enable, bool do_reset_flank) {
        
        bool do_descalate = false;

        switch (state_)
        {                       
            case CpState::InactiveWarning:

                // cp gets enabled
                if (do_enable) state_ = CpState::Warning;

                // warning monitor gets inactive
                if (IsInactive(warning_monitor_)) do_descalate = true;
                
                break;

            case CpState::Warning:

                // warning monitor gets inactive
                if (IsInactive(warning_monitor_)) state_ = CpState::WarningLatched;
                break; 

            case CpState::WarningLatched:

                if (IsActive(warning_monitor_)) {
                    state_ = CpState::Warning;
                }

                if (do_reset_flank) do_descalate = true;
                break;
            
            default:
                break;
        }

         // out-warning transitions (de-escalating)
        if (do_descalate) {
            // if caution monitor is active, de-escalate to caution, otherwise de-escalate to ok
            IsActive(caution_monitor_) ? EntryCaution(do_enable) : EntryOk(do_enable);
        }

        // out-warning transitions (escalating)
        // ---------------------------------------------
        if (IsActive(warning2_monitor_)) {
            EntryWarning2(do_enable);
        }
    };

    void UpdateSubLevelsWarning2(bool do_enable, bool do_reset_flank) {
        
        bool do_descalate = false;

        switch (state_)
        {                       
            case CpState::InactiveWarning2:

                // cp gets enabled
                if (do_enable) state_ = CpState::Warning2;

                // warning monitor gets inactive
                if (IsInactive(warning2_monitor_)) do_descalate = true;
                
                break;

            case CpState::Warning2:

                if (IsInactive(warning2_monitor_)) state_ = CpState::Warning2Latched;
                break; 

            case CpState::Warning2Latched:

                if (IsActive(warning2_monitor_)) {
                    state_ = CpState::Warning;
                }

                if (do_reset_flank) do_descalate = true;
                break;
            
            default:
                break;
        }

         // out-warning transitions (de-escalating)
        if (do_descalate) {
            // if caution monitor is active, de-escalate to caution, otherwise de-escalate to ok

            if (IsActive(warning_monitor_)) {
                EntryWarning(do_enable);
            } else if (IsActive(caution_monitor_)) {
                EntryCaution(do_enable);
            } else {
                EntryOk(do_enable);
            }
        }

        // out-warning transitions (escalating)
        // ---------------------------------------------
        if (IsActive(warning2_monitor_)) {
            EntryWarning2(do_enable);
        }
                

    };

    void EntryOk(bool do_enable) {
        if (do_enable) {
            state_ = CpState::Ok;
        } else {
            state_ = CpState::InactiveOk;
        }
    };

    void EntryCaution(bool do_enable) {
        if (do_enable) {
            state_ = CpState::Caution;
        } else {
            state_ = CpState::InactiveCaution;
        }
    };

    void EntryWarning(bool do_enable) {
        if (do_enable) {
            state_ = CpState::Warning;
        } else {
            state_ = CpState::InactiveWarning;
        }
    }

    void EntryWarning2(bool do_enable) {
        if (do_enable) {
            state_ = CpState::Warning2;
        } else {
            state_ = CpState::InactiveWarning2;
        }
    };


    // getters
    CpType GetType(void) { return type_; };
    CpState GetState(){ return state_;};
    
    // for testing purposes, could be moved to mock class for component protection
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

    CpState DetermineCpState() {

        
    }

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
