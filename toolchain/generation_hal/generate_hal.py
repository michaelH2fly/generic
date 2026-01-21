import yaml
from pathlib import Path

from component import Component
from pydantic import ValidationError

file_config_hal_generation = "config_hal_generation.yaml"


def load_config_hal_generation():

    with open(file_config_hal_generation, 'r') as file:

        config_hal_generation = yaml.safe_load(file)

    return config_hal_generation
    
def parse_data_from_component_definition_files(
        config
        ) -> list:

    # fetch the paths from definition components
    component_definition_paths = config["paths"]["definition_components"]

    # init component list
    component_data = []

    # loop over fetched component definitions paths
    for comp_def_path in component_definition_paths:

        # parse it to a conform path
        comp_def_path = Path(comp_def_path)

        # jump over not exisiting directories
        if not comp_def_path.is_dir():
            print(f"Warning: {comp_def_path} is not a directory, skipping.")
            continue
        
        # for different yaml endings
        for suffix in ["*.yaml", ".yml"]:
            # loop over all files in directory with the appropriate suffix
            for yaml_file in comp_def_path.rglob(suffix):
                try:
                    # open the file with reading permission
                    with yaml_file.open("r", encoding="utf-8") as f:
                        # parse the yaml content convert it to the a Component object - append it to component list
                        try:
                            raw_data = yaml.safe_load(f)
                            parsed_component = Component(**raw_data)
                            component_data.append(parsed_component)
                            
                            print(f"Info: parsed component", parsed_component.name)
                        except yaml.YAMLError as e:
                            print(f"YAML parsing failed for %s: %s", yaml_file, e)
                            expect
                        except KeyError as e:
                            print(f"Missing configuration section: {e}")
                        except ValidationError as e:
                            print(f"Configuration validation failed: {e}")
                        except Exception as e:
                            print(f"Unexpected error reading %s", {e})
                    
                except Exception as e:
                    print(f"Failed to parse {yaml_file}: {e}")
        
    return component_data

def generate_hal():

    # load the configuration for the hal generation
    config = load_config_hal_generation()

    component_data = parse_data_from_component_definition_files(config)

if __name__ == "__main__":

    

    generate_hal()

