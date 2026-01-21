from pydantic import BaseModel
from enum import Enum
from component_protection import ComponentProtection


class Subsystem(str, Enum):
    ANODE       = "ANODE"
    CATHODE     = "CATHODE"
    THERMAL     = "THERMAL"
    ELECTRICAL  = "ELECTRICAL"
    HOUSING     = "HOUSING"

class CtrlSubsystem(str, Enum):
    AP  = "AP"
    AX  = "AX"


class Component(BaseModel):
    name: str 
    component_type: str 
    subsystem: Subsystem
    ctrl_subsystem: CtrlSubsystem
    component_protections: list[ComponentProtection]
    
if __name__ == "__main__":

    import yaml
    from pydantic import ValidationError

    yaml_content = """
    
    Component:
        name: Busch Hydrogen Recirculation Pump
        component_type: Recirculation Pump
        subsystem: ANODE
        ctrl_subsystem: AX
        component_protections:
          - name: UL_inletTemperature_recirculation_pump
            observed_signal: testsignal
            type_monitor: UL
            caution_monitor:
                threshold: 3
                debounce_time: 2.5
            caution_action: VOID
            warning_monitor:
                threshold: 5
                debounce_time: 2
            warning_sd_type: NORMAL_SD
            is_active_warning2: true
            warning2_monitor:
                threshold: 6
                debounce_time: 2
            warning2_sd_type: FAST_SD
            access_level: TESTER
            description: test

          - name: LL_inletPressure_recirculation_pump
            observed_signal: testsignal
            type_monitor: LL
            caution_monitor:
                threshold: 0.9
                debounce_time: 2.5
            caution_action: VOID
            warning_monitor:
                threshold: 0.8
                debounce_time: 2
            warning_sd_type: NORMAL_SD
            is_active_warning2: true
            warning2_monitor:
                threshold: 0.7
                debounce_time: 2
            warning2_sd_type: FAST_SD
            access_level: TESTER
            description: test

    """

    component_yaml_data = yaml.safe_load(yaml_content)

    try: 
        component_data = Component(**component_yaml_data["Component"])
        print("Parsing component data was successfull")
        print(component_data.model_dump())
    except KeyError as e:
        print(f"Missing configuration section: {e}")
    except ValidationError as e:
        print("Configuration validation failed:")
        print(e)
