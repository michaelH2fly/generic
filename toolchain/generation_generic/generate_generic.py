import yaml
from generic_function import GenericFunction, GenericFunctionList
from pathlib import Path
from pydantic import ValidationError

path_generation_config = "config_generation.yaml"

def load_generation_config():

    with open(path_generation_config, 'r') as file:

        config_generation = yaml.safe_load(file)

    return config_generation


def parse_generic_functions_from_definition_files(file_paths: Path) -> list:

    # init generic function list
    generic_functions_data = []

    # loop over generic function definition paths
    for yaml_file_path in file_paths:

        # convert it to pathlib path
        yaml_file_path = Path(yaml_file_path)

        # jump over not existing directories
        if not yaml_file_path.exists():
            print(f"Warning: The file {yaml_file_path} does not exist.")
            continue

        try:
            # open the file with reading permission
            with yaml_file_path.open("r", encoding="utf-8") as f:
                # parse the yaml content convert it to the a Component object - append it to component list
                try:
                    raw_data = yaml.safe_load(f)

                    parsed_generic_functions = GenericFunctionList(**raw_data)

                    for generic_function in parsed_generic_functions.generic_functions:
                        
                        generic_functions_data.append(generic_function)

                except yaml.YAMLError as e:
                    print(f"YAML parsing failed for %s: %s", yaml_file_path, e)                
                except KeyError as e:
                    print(f"Missing configuration section: {e}")
                except ValidationError as e:
                    print(f"Configuration validation failed: {e}")
                except Exception as e:
                    print(f"Unexpected error reading %s", {e})
            
        except Exception as e:
            print(f"Failed to parse {yaml_file_path}: {e}")
        
    return generic_functions_data

def generate_generic():

    config = load_generation_config()
    def_file_paths = config["paths"]["definition_generic_functions"]

    generic_function_data = parse_generic_functions_from_definition_files(def_file_paths)

if __name__ == "__main__":

    generate_generic()
