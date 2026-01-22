import yaml
from pathlib import Path

from component import Component
from pydantic import ValidationError

file_config_generation = "config_generation.yaml"


def load_config_hal_generation():

    with open(file_config_generation, 'r') as file:

        config_generation = yaml.safe_load(file)

    return config_generation
    
def parse_components_from_definition_directory(directories) -> list:

    # init component list
    component_data = []

    # loop over fetched component definitions paths
    for directory in directories:

        # parse it to a conform path
        directory = Path(directory)

        # jump over not exisiting directories
        if not directory.is_dir():
            print(f"Warning: {directory} is not a directory, skipping.")
            continue
        
        # for different yaml endings
        for suffix in ["*.yaml", ".yml"]:
            # loop over all files in directory with the appropriate suffix
            for yaml_file in directory.rglob(suffix):
                try:
                    # open the file with reading permission
                    with yaml_file.open("r", encoding="utf-8") as f:
                        # parse the yaml content convert it to the a Component object - append it to component list
                        try:
                            raw_data = yaml.safe_load(f)
                            parsed_component = Component(**raw_data)
                            component_data.append(parsed_component)

                            print(f"Info: parsed component: {parsed_component.name}")
                        except yaml.YAMLError as e:
                            print(f"YAML parsing failed for {yaml_file}: {e}")                            
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

    config = load_config_hal_generation()
    
    paths = config["paths"]["definition_components"]

    component_data = parse_components_from_definition_directory(paths)

    print(component_data)

if __name__ == "__main__":

    

    generate_hal()

