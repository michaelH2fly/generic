#ifndef CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_
#define CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_

#include <string>
#include <memory>
#include "monitor.h"
#include "cp_parameter.h"

// Type of monitoring for component protection (Upper Limit or Lower Limit).
//enum class TypeMonitor {
//	UL,  // Upper Limit
//	LL   // Lower Limit
//};
//
//// Component protection monitoring configuration.
//class ComponentProtection {
//	public:
//        // Default constructor.
//        ComponentProtection();
//
//        // Full parameter constructor with unique_ptr monitors (subclass independent).
//        ComponentProtection(
//            const std::string& name,
//            const std::string& observed_signal,
//            TypeMonitor type_monitor,
//            std::unique_ptr<Monitor> caution_monitor,
//            std::unique_ptr<Monitor> warning_monitor,
//            std::unique_ptr<Monitor> warning2_monitor,
//            const CPParameter& parameters);
//
//        // Cyclic step function (to be called periodically).
//        //void Step(float observed_value, bool is_active, bool do_reset);
//
//        // Getters for basic properties
//        const std::string& GetName() const;
//        const std::string& GetObservedSignal() const;
//        TypeMonitor GetTypeMonitor() const;
//
//        // Getters for monitors (return base class pointers)
//        Monitor* GetCautionMonitor() const;
//        Monitor* GetWarningMonitor() const;
//        Monitor* GetWarning2Monitor() const;
//
//        // Getter for parameters
//        const CPParameter& GetParameters() const;
//
//        // Setters for basic properties
//        void SetName(const std::string& name);
//        void SetObservedSignal(const std::string& observed_signal);
//        void SetTypeMonitor(TypeMonitor type_monitor);
//
//        // Setters for monitors
//        void SetCautionMonitor(std::unique_ptr<Monitor> caution_monitor);
//        void SetWarningMonitor(std::unique_ptr<Monitor> warning_monitor);
//        void SetWarning2Monitor(std::unique_ptr<Monitor> warning2_monitor);
//
//        // Setter for parameters
//        void SetParameters(const CPParameter& parameters);
//
//	private:
//        std::string name_;
//        std::string observed_signal_;
//        TypeMonitor type_monitor_;
//        CPParameter parameters_;
//        std::unique_ptr<Monitor> caution_monitor_;
//        std::unique_ptr<Monitor> warning_monitor_;
//        std::unique_ptr<Monitor> warning2_monitor_;
//};
//

#endif  // CXX_COMPONENT_PROTECTION_INC_COMPONENT_PROTECTION_H_
