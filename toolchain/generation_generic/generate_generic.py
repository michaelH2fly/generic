import yaml
from generic_function import GenericFunction
from pathlib import Path
from pydantic import ValidationError

path_generation_config = "config_generation.yaml"

def load_generation_config():

    with open(path_generation_config, 'r') as file:

        config_generation = yaml.safe_load(file)

    return config_generation


def parse_data_from_generic_function_files(
        config
        ) -> list:

    # init generic function list
    generic_functions_data = []

    # extract relevant paths from config
    generic_function_def_paths = config["paths"]["definition_generic_functions"]

    # loop over generic function definition paths
    for generic_function_def_path in generic_function_def_paths:

        # convert it to pathlib path
        generic_function_def_path = Path(generic_function_def_path)

        # jump over not existing directories
        if not generic_function_def_path.is_dir():
            continue

        # for different yml endings
        for suffix in ["*.yaml", "*.yml"]:

            # loop over all files in directory with the appropriate suffix
            for yaml_file in comp_def_path.rglob(suffix):
                try:
                    # open the file with reading permission
                    with yaml_file.open("r", encoding="utf-8") as f:
                        # parse the yaml content convert it to the a Component object - append it to component list
                        try:
                            raw_data = yaml.safe_load(f)
                            parsed_generic_function = GenericFunction(**raw_data)
                            generic_functions_data.append(parsed_generic_function)

                            print(f"Info: parsed component", parsed_generic_function.name)
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
        
    return generic_functions_data



def generate_generic():

    config = load_generation_config()

    generic_function_data = parse_data_from_generic_function_files(config)

    print(generic_function_data)

if __name__ == "__main__":

    generate_generic()
