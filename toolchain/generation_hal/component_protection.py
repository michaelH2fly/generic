from pydantic import BaseModel
from enum import Enum

class TypeMonitor(str, Enum):
    UL = "UL"
    LL = "LL"

class CautionAction(str, Enum):
    VOID = "VOID"

class ShutdownType(str, Enum):
    NORMAL_SD    = "NORMAL_SD"
    FAST_SD      = "FAST_SD"
    HARD_SD      = "HARD_SD"

class AccessLevel(str, Enum):
    TESTER = "TESTER"

class Monitor(BaseModel):
    threshold: float    
    debounce_time: float

class ComponentProtection(BaseModel):
    name: str 
    observed_signal: str 
    type_monitor: TypeMonitor
    caution_monitor: Monitor
    caution_action: CautionAction
    warning_monitor: Monitor
    warning_sd_type: ShutdownType
    is_active_warning2: bool
    warning2_monitor: Monitor
    warning2_sd_type: ShutdownType
    access_level: AccessLevel
    description: str = ""

if __name__ == "__main__":

    import yaml
    from pydantic import ValidationError

    yaml_content = """
    
    ComponentProtection:
        name: UL_inletTemperature_recirculation_pump
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

    """

    component_protection_yaml_data = yaml.safe_load(yaml_content)

    try: 
        component_protection_data = ComponentProtection(**component_protection_yaml_data["ComponentProtection"])
        print("Parsing component data was successfull")
        print(component_protection_data.model_dump())
    except KeyError as e:
        print(f"Missing configuration section: {e}")
    except ValidationError as e:
        print("Configuration validation failed:")
        print(e)

    




